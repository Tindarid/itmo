package ru.itmo.webmail.web.page;

import ru.itmo.webmail.model.domain.Article;
import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.exception.ValidationException;
import ru.itmo.webmail.web.exception.RedirectException;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

public class ArticlePage extends Page {
    @Override
    public void before(HttpServletRequest request, Map<String, Object> view) {
        super.before(request, view);

        if (getUser() == null) {
            throw new RedirectException("/index");
        }
    }

    private void action(HttpServletRequest request, Map<String, Object> view) {
        // No operations.
    }

    private Map<String, Object> submitarticle(HttpServletRequest request, Map<String, Object> view) {
        Article article = new Article();
        article.setText(request.getParameter("articletext"));
        article.setTitle(request.getParameter("title"));
        article.setHidden(Boolean.parseBoolean(request.getParameter("ishidden")));
        article.setUserId((Long)request.getSession().getAttribute(USER_ID_SESSION_KEY));

        try {
            getArticleService().validate(article);
        } catch (ValidationException e) {
            view.put("success", false);
            view.put("error", e.getMessage());
            return view;
        }

        getArticleService().save(article);
        view.put("success", true);
        return view;
    }
}
