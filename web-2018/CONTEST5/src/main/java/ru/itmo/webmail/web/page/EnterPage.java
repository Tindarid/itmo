package ru.itmo.webmail.web.page;

import ru.itmo.webmail.model.domain.Event;
import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.exception.ValidationException;
import ru.itmo.webmail.model.service.UserService;
import ru.itmo.webmail.web.exception.RedirectException;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

public class EnterPage extends Page {
    private void enter(HttpServletRequest request, Map<String, Object> view) {
        String login = request.getParameter("login");
        String password = request.getParameter("password");

        try {
            getUserService().validateEnter(login, password);
        } catch (ValidationException e) {
            view.put("login", login);
            view.put("password", password);
            view.put("error", e.getMessage());
            return;
        }

        User user = getUserService().authorize(login, password);

        if (!user.isConfirmed()) {
            view.put("error", "Your registration is not confirmed");
            return;
        }

        Event event = new Event();
        event.setType(Event.Type.ENTER);
        event.setUserId(user.getId());
        getEventService().save(event);

        request.getSession(true).setAttribute(USER_ID_SESSION_KEY, user.getId());

        throw new RedirectException("/index");
    }

    private void action(HttpServletRequest request, Map<String, Object> view) {
        // No operations.
    }
}
