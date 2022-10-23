package ru.itmo.webmail.model.repository;

import ru.itmo.webmail.model.domain.User;

public class UserRepository extends Repository<User> {
    public UserRepository() {
        type = User.class;
    }

    public User findByLogin(String login) {
        String sql = "SELECT * FROM User WHERE login=?";
        return performRequest(sql, new Object[] {login});
    }

    public User findByEmail(String email) {
        String sql = "SELECT * FROM User WHERE email=?";
        return performRequest(sql, new Object[] {email});
    }

    public User findByLoginOrEmailAndPasswordSha(String loginOrEmail, String passwordSha) {
        String sql = "SELECT * FROM User WHERE email=? OR login=? AND passwordSha=? ";
        return performRequest(sql, new Object[] {loginOrEmail, loginOrEmail, passwordSha});
    }

    public User findByLoginOrEmail(String loginOrEmail) {
        String sql = "SELECT * FROM User WHERE email=? OR login=?";
        return performRequest(sql, new Object[] {loginOrEmail, loginOrEmail});
    }

    public void save(User user, String passwordSha) {
        String sql = "INSERT INTO User (login, email, passwordSha, confirmed, creationTime) VALUES (?, ?, ?, ?, NOW())";
        saveHelper(user, sql, new Object[] {user.getLogin(), user.getEmail(), passwordSha, user.isConfirmed()});
    }

    public void updateUserConfirmation(long id, boolean status) {
        String sql = "UPDATE User SET confirmed = ? WHERE id = ?";
        performRequest(sql, new Object[] {status, id});
    }
}
