package ru.itmo.webmail.model.service;

import ru.itmo.webmail.model.domain.Article;
import ru.itmo.webmail.model.exception.ValidationException;
import ru.itmo.webmail.model.repository.ArticleRepository;
import ru.itmo.webmail.model.repository.impl.ArticleRepositoryImpl;

import java.util.List;

public class ArticleService {
    private ArticleRepository articleRepository = new ArticleRepositoryImpl();

    public void save(Article article) {
        articleRepository.save(article);
    }

    public List<Article> findAll() {
        return articleRepository.findAll();
    }

    public List<Article> findAllFrom(long userId) {
        return articleRepository.findAllFrom(userId);
    }

    public Article find(long id) {
        return articleRepository.find(id);
    }

    public void switchHidden(long id, boolean newHidden) {
        articleRepository.switchHidden(id, newHidden);
    }

    public void validate(Article article) throws ValidationException {
        if (article.getText().isEmpty()) {
            throw new ValidationException("Article cannot be with empty text");
        }
        if (article.getTitle().isEmpty()) {
            throw new ValidationException("Article cannot be with empty title");
        }
        if (article.getTitle().length() > 255) {
            throw new ValidationException("Title is too long");
        }
    }
}
