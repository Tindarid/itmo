package ru.itmo.webmail.model.service;

import ru.itmo.webmail.model.domain.Talk;
import ru.itmo.webmail.model.exception.ValidationException;
import ru.itmo.webmail.model.repository.TalkRepository;

import java.util.List;

public class TalkService {
    private TalkRepository talkRepository = new TalkRepository();

    public void save(Talk talk) {
        talkRepository.save(talk);
    }

    public List<Talk> findAllFromId(long userId) {
        return talkRepository.findAllFromId(userId);
    }

    public void validate(String text) throws ValidationException {
        if (text.isEmpty()) {
            throw new ValidationException("Your message cannot be empty");
        }
    }
}
