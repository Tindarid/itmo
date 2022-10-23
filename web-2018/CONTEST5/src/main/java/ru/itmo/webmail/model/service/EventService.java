package ru.itmo.webmail.model.service;

import ru.itmo.webmail.model.domain.Event;
import ru.itmo.webmail.model.repository.EventRepository;

public class EventService {
    private EventRepository eventRepository = new EventRepository();

    public void save(Event event) {
        eventRepository.save(event);
    }
}
