package ru.itmo.webmail.model.service;

import ru.itmo.webmail.model.domain.News;
import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.exception.ValidationException;
import ru.itmo.webmail.model.repository.NewsRepository;
import ru.itmo.webmail.model.repository.impl.NewsRepositoryImpl;

import java.util.List;

public class NewsService {
    private NewsRepository newsRepository = new NewsRepositoryImpl();

    public void validate(User user, String text) throws ValidationException {
        if (user == null) {
            throw new ValidationException("You should be logged in");
        }
        if (text.isEmpty()) {
            throw new ValidationException("News must contain text");
        }
    }

    public void save(News news) {
        newsRepository.save(news);
    }

    public List<News> findAll() {
        return newsRepository.findAll();
    }
}

