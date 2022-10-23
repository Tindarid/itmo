package ru.itmo.webmail.web.page;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

public class IndexPage extends Page {
    private void action(HttpServletRequest request, Map<String, Object> view) {
        // No operations.
    }

    private void registrationDone(HttpServletRequest request, Map<String, Object> view) {
        view.put("message", "You have been registered, confirmation has been sent to your email");
    }

    private void confirmationDone(HttpServletRequest request, Map<String, Object> view) {
        view.put("message", "Thanks for confirmation");
    }

    private void messageSent(HttpServletRequest request, Map<String, Object> view) {
        view.put("message", "Your message has been sent");
    }
}
