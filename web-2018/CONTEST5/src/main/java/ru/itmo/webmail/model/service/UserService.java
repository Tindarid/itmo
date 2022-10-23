package ru.itmo.webmail.model.service;

import com.google.common.hash.Hashing;
import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.exception.ValidationException;
import ru.itmo.webmail.model.repository.UserRepository;

import java.nio.charset.StandardCharsets;
import java.util.List;

@SuppressWarnings("UnstableApiUsage")
public class UserService {
    private static final String USER_PASSWORD_SALT = "dc3475f2b301851b";

    private UserRepository userRepository = new UserRepository();

    public User findByLoginOrEmail(String loginOrEmail) {
        return userRepository.findByLoginOrEmail(loginOrEmail);
    }
    public void validateRegistration(User user, String password) throws ValidationException {
        checkLogin(user.getLogin());
        checkEmail(user.getEmail());
        checkPassword(password);
    }

    public void register(User user, String password) {
        String passwordSha = getPasswordSha(password);
        userRepository.save(user, passwordSha);
    }

    public List<User> findAll() {
        return userRepository.findAll();
    }

    public void validateEnter(String loginOrEmail, String password) throws ValidationException {
        checkPassword(password);
        if (userRepository.findByLoginOrEmailAndPasswordSha(loginOrEmail, getPasswordSha(password)) == null) {
            throw new ValidationException("Invalid login or password");
        }
    }

    private void checkLogin(String login) throws ValidationException {
        if(userRepository.findByLogin(login) != null) {
            throw new ValidationException("Login is already in use");
        }
        if (login == null || login.isEmpty()) {
            throw new ValidationException("Login is required");
        }
        if (!login.matches("[a-z]+")) {
            throw new ValidationException("Login can contain only lowercase Latin letters");
        }
        if (login.length() > 8) {
            throw new ValidationException("Login can't be longer than 8");
        }
    }

    private void checkPassword(String password) throws ValidationException {
        if (password == null || password.isEmpty()) {
            throw new ValidationException("Password is required");
        }
        if (password.length() < 4) {
            throw new ValidationException("Password can't be shorter than 4");
        }
        if (password.length() > 32) {
            throw new ValidationException("Password can't be longer than 32");
        }
    }

    private void checkEmail(String email) throws ValidationException {
        if (userRepository.findByEmail(email) != null) {
            throw new ValidationException("Email is already in use");
        }
        if (!email.matches("^[_A-Za-z0-9-\\+]+(\\.[_A-Za-z0-9-]+)*@[A-Za-z0-9-]+(\\.[A-Za-z0-9]+)*(\\.[A-Za-z]{2,})$")) {
            throw new ValidationException("Email is incorrect");
        }
    }

    private String getPasswordSha(String password) {
        return Hashing.sha256().hashString(USER_PASSWORD_SALT + password,
                StandardCharsets.UTF_8).toString();
    }

    public User authorize(String loginOrEmail, String password) {
        return userRepository.findByLoginOrEmailAndPasswordSha(loginOrEmail, getPasswordSha(password));
    }

    public User find(long userId) {
        return userRepository.find(userId);
    }

    public void updateUserConfirmation(long id, boolean status) {
        userRepository.updateUserConfirmation(id, status);
    }
}
