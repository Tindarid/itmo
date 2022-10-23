package ru.itmo.webmail.web.page;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

public class IndexPage extends Page {
    private void action() {
        // No operations.
    }

    private void newsAdded(Map<String, Object> view) {
        view.put("message", "Your news have been added");
    }

    private void registrationDone(Map<String, Object> view) {
        view.put("message", "You have been registered");
    }

    private void loginSuccess(Map<String, Object> view) {
        view.put("message", "Logged in successfully");
    }

    private void logoutSuccess(Map<String, Object> view) {
        view.put("message", "See you soon");
    }
}

