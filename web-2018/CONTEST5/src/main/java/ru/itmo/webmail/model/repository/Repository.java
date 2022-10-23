package ru.itmo.webmail.model.repository;

import ru.itmo.webmail.model.database.DatabaseUtils;
import ru.itmo.webmail.model.exception.RepositoryException;

import javax.sql.DataSource;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.sql.*;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class Repository<T> {
    private static final DataSource DATA_SOURCE = DatabaseUtils.getDataSource();
    protected Class<T> type;

    protected List<T> performRequestList(String sqlStatement, Object[] values) {
        List<T> result = new ArrayList<>();
        try (Connection connection = DATA_SOURCE.getConnection()) {
            try (PreparedStatement statement = connection.prepareStatement(sqlStatement)) {
                for (int i = 0; i < values.length; ++i) {
                    statement.setObject(i + 1, values[i]);
                }
                try (ResultSet resultSet = statement.executeQuery()) {
                    while (resultSet.next()) {
                        result.add(transform(statement.getMetaData(), resultSet));
                    }
                }
            }
        } catch (SQLException e) {
            throw new RepositoryException("Can't perform request: " + sqlStatement, e);
        }
        return result;
    }

    protected T performRequest(String sqlStatement, Object[] values) {
        try (Connection connection = DATA_SOURCE.getConnection()) {
            try (PreparedStatement statement = connection.prepareStatement(sqlStatement)) {
                for (int i = 0; i < values.length; ++i) {
                    statement.setObject(i + 1, values[i]);
                }
                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        return transform(statement.getMetaData(), resultSet);
                    } else {
                        return null;
                    }
                }
            }
        } catch (SQLException e) {
            throw new RepositoryException("Can't perform request: " + sqlStatement, e);
        }
    }

    @SuppressWarnings("StatementWithEmptyBody")
    private T transform(ResultSetMetaData metaData, ResultSet resultSet) throws SQLException {
        try {
            T result = type.newInstance();
            for (int i = 1; i <= metaData.getColumnCount(); i++) {
                String columnName = metaData.getColumnName(i);
                try {
                    Field field = type.getDeclaredField(columnName);
                    field.setAccessible(true);
                    field.set(result, resultSet.getObject(i));
                } catch (NoSuchFieldException e) {
                    if (!columnName.equals("passwordSha")) {
                        throw new RepositoryException("Unexpected column '" + type.getSimpleName() + "." + columnName + "'.");
                    }
                }
            }
            return result;
        } catch (InstantiationException | IllegalAccessException e) {
            return null;
        }
    }

    private Date findCreationTime(long id) {
        try (Connection connection = DATA_SOURCE.getConnection()) {
            try (PreparedStatement statement = connection.prepareStatement(
                    "SELECT creationTime FROM " + type.getSimpleName() + " WHERE id=?")) {
                statement.setLong(1, id);
                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        return resultSet.getTimestamp(1);
                    }
                }
                throw new RepositoryException("Can't find creationTime by id.");
            }
        } catch (SQLException e) {
            throw new RepositoryException("Can't find creationTime by id.", e);
        }
    }

    public T find(long id) {
        String sql = "SELECT * FROM " + type.getSimpleName() + " WHERE id=?";
        return performRequest(sql, new Object[] {id});
    }

    public List<T> findAll() {
        String sql = "SELECT * FROM " + type.getSimpleName() + " ORDER BY id";
        return performRequestList(sql, new Object[0]);
    }

    protected void saveHelper(T obj, String sqlStatement, Object[] values) {
        try (Connection connection = DATA_SOURCE.getConnection()) {
            try (PreparedStatement statement = connection.prepareStatement(sqlStatement,
                    Statement.RETURN_GENERATED_KEYS)) {
                for (int i = 0; i < values.length; ++i) {
                    statement.setObject(i + 1, values[i]);
                }
                if (statement.executeUpdate() == 1) {
                    ResultSet generatedIdResultSet = statement.getGeneratedKeys();
                    if (generatedIdResultSet.next()) {
                        try {
                            Field idField = type.getDeclaredField("id");
                            Field timeField = type.getDeclaredField("creationTime");
                            idField.setAccessible(true);
                            timeField.setAccessible(true);
                            idField.set(obj, generatedIdResultSet.getLong(1));
                            timeField.set(obj, findCreationTime(generatedIdResultSet.getLong(1)));
                        } catch (NoSuchFieldException | IllegalAccessException e) {
                           //
                        }
                    } else {
                        throw new RepositoryException("Can't find id of saved.");
                    }
                } else {
                    throw new RepositoryException("Can't save.");
                }
            }
        } catch (SQLException e) {
            throw new RepositoryException("Can't save.", e);
        }
    }
}
