package ru.itmo.webmail.model.repository;

import ru.itmo.webmail.model.domain.Talk;

import java.util.List;

public class TalkRepository extends Repository<Talk> {
    public TalkRepository() {
        type = Talk.class;
    }

    public void save(Talk talk) {
        String sql = "INSERT INTO Talk (sourceUserId, targetUserId, text, creationTime) VALUES (?, ?, ?, NOW())";
        saveHelper(talk, sql, new Object[] {talk.getSourceUserId(), talk.getTargetUserId(), talk.getText()});
    }

    public List<Talk> findAllFromId(long userId) {
        String sql = "SELECT * FROM Talk WHERE sourceUserId=? OR targetUserId=?";
        return performRequestList(sql, new Object[] {userId, userId});
    }
}

