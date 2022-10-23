package ru.itmo.webmail.web.page;

import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.exception.ValidationException;
import ru.itmo.webmail.model.service.UserService;
import ru.itmo.webmail.web.exception.RedirectException;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

public class RegisterPage extends Page {
    private void register(HttpServletRequest request, Map<String, Object> view) {
        User user = new User();
        user.setLogin(request.getParameter("login"));
        String password = request.getParameter("password");
        String passwordConfirmation = request.getParameter("passwordConfirmation");
        String email = request.getParameter("email");

        try {
            userService.validateRegistration(user, password, passwordConfirmation, email);
        } catch (ValidationException e) {
            view.put("login", user.getLogin());
            view.put("password", password);
            view.put("passwordConfirmation", passwordConfirmation);
            view.put("email", email);
            view.put("error", e.getMessage());
            return;
        }

        userService.register(user, password, email);
        throw new RedirectException("/index", "registrationDone");
    }

    private void action() {
        // No operations.
    }
}
