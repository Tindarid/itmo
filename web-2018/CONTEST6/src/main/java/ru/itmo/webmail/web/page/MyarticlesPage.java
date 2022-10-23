package ru.itmo.webmail.web.page;

import ru.itmo.webmail.model.domain.Article;
import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.web.exception.RedirectException;

import javax.servlet.http.HttpServletRequest;
import java.util.List;
import java.util.Map;

public class MyarticlesPage extends Page{
    @Override
    public void before(HttpServletRequest request, Map<String, Object> view) {
        super.before(request, view);

        if (getUser() == null) {
            throw new RedirectException("/index");
        }
    }

    private List<Article> find(HttpServletRequest request, Map<String, Object> view) {
        return getArticleService().findAllFrom((Long)request.getSession().getAttribute(USER_ID_SESSION_KEY));
    }

    private Map<String, Object> switchHidden(HttpServletRequest request, Map<String, Object> view) {
        long userId = (Long)request.getSession().getAttribute(USER_ID_SESSION_KEY);
        long requestedId = Long.parseLong(request.getParameter("articleid"));
        Article req = getArticleService().find(requestedId);
        if (req.getUserId() == userId) {
            getArticleService().switchHidden(requestedId, !req.isHidden());
            view.put("success", true);
        } else {
            view.put("success", false);
        }
        return view;
    }

    private void action(HttpServletRequest request, Map<String, Object> view) {
        // No operations.
    }
}
