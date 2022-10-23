package ru.itmo.webmail.model.repository;

import ru.itmo.webmail.model.domain.News;

import java.util.List;

public interface NewsRepository {
    void save(News news);
    List<News> findAll();
}
