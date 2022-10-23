package ru.itmo.webmail.web.page;

import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.service.UserService;
import ru.itmo.webmail.web.exception.RedirectException;

import javax.servlet.http.HttpServletRequest;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class UsersPage extends Page{
    @Override
    public void before(HttpServletRequest request, Map<String, Object> view) {
        super.before(request, view);

        if (getUser() == null) {
            throw new RedirectException("/index");
        }
    }

    private List<User> find(HttpServletRequest request, Map<String, Object> view) {
        return getUserService().findAll();
    }

    private boolean isAdmin(HttpServletRequest request, Map<String, Object> view) {
        User user = getUserService().find((Long)request.getSession().getAttribute(USER_ID_SESSION_KEY));
        return user.isAdmin();
    }

    private void action(HttpServletRequest request, Map<String, Object> view) {
        // No operations.
    }

    private Map<String, Object> switchAdmin(HttpServletRequest request, Map<String, Object> view) {
        if (!isAdmin(request, view)) {
            view.put("success", false);
            return view;
        }
        Long updateId = Long.parseLong(request.getParameter("updateid"));
        Boolean newAdmin = !Boolean.parseBoolean(request.getParameter("oldadmin"));
        getUserService().switchAdmin(updateId, newAdmin);
        view.put("success", true);
        if (updateId.equals((Long)request.getSession().getAttribute(USER_ID_SESSION_KEY))) {
            view.put("reload", true);
        } else {
            view.put("reload", false);
        }
        return view;
    }
}
