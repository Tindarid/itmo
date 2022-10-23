package ru.itmo.wm4.form;

import javax.validation.constraints.NotEmpty;

public class NoticeCredentials {
    @NotEmpty
    private String content;

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }
}
