package ru.itmo.webmail.web.page;

import ru.itmo.webmail.model.domain.Event;
import ru.itmo.webmail.web.exception.RedirectException;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

public class LogoutPage extends Page {
    private void action(HttpServletRequest request, Map<String, Object> view) {
        Event event = new Event();
        event.setType(Event.Type.LOGOUT);
        event.setUserId((Long)request.getSession().getAttribute(USER_ID_SESSION_KEY));
        getEventService().save(event);

        request.getSession().removeAttribute(USER_ID_SESSION_KEY);
        throw new RedirectException("/index");
    }
}
