package ru.itmo.webmail.web.page;

import ru.itmo.webmail.model.domain.News;
import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.service.NewsService;
import ru.itmo.webmail.model.service.UserService;

import javax.servlet.http.HttpServletRequest;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class Page {
    protected UserService userService = new UserService();
    protected NewsService newsService = new NewsService();

    protected void before(HttpServletRequest request, Map<String, Object> view) {
        User user = (User)request.getSession().getAttribute("user");
        if (user != null) {
            view.put("username", user.getLogin());
        }
    }

    protected void after(HttpServletRequest request, Map<String, Object> view) {
        view.put("userCount", userService.findCount());
        List<NewsWithNames> allNews = new ArrayList<>();
        for (News n : newsService.findAll()) {
            allNews.add(new NewsWithNames(userService.find(n.getId()), n.getText()));
        }
        if (!allNews.isEmpty()) {
            view.put("allNews", allNews);
        }
    }

    public class NewsWithNames extends News {
        private String user;
        public NewsWithNames(String username, String text) {
            super(text);
            user = username;
        }
        public String getUser() {
            return user;
        }
    }

}
