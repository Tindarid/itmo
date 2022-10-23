package ru.itmo.webmail.web.page;

import ru.itmo.webmail.model.domain.EmailConfirmation;
import ru.itmo.webmail.web.exception.RedirectException;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

public class ConfirmPage extends Page {
    private void action(HttpServletRequest request, Map<String, Object> view) {
        String secret = (String)request.getParameter("secret");
        EmailConfirmation confirmation = getEmailConfirmationService().findBySecret(secret);
        if (confirmation == null) {
            throw new RedirectException("/index");
        }
        if (getUserService().find(confirmation.getUserId()).isConfirmed()) {
            throw new RedirectException("/index");
        }
        getUserService().updateUserConfirmation(confirmation.getUserId(), true);
        throw new RedirectException("/index", "confirmationDone");
    }
}
