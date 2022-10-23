package ru.itmo.webmail.model.repository;

import ru.itmo.webmail.model.domain.Article;

import java.util.List;

public interface ArticleRepository {
    Article find(long id);
    List<Article> findAll();
    List<Article> findAllFrom(long userId);
    void save(Article article);
    void switchHidden(long id, boolean newHidden);
}
