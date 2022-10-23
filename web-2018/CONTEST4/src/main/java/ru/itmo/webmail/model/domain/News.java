package ru.itmo.webmail.model.domain;

import java.io.Serializable;

public class News implements Serializable {
    protected long id;
    protected String text;

    public News(String text) {
        this.text = text;
    }
    public News(long id, String text) {
        this.id = id;
        this.text = text;
    }

    public long getId() {
        return id;
    }

    public String getText() {
        return text;
    }
}
