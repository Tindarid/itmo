package ru.itmo.webmail.model.repository;

import ru.itmo.webmail.model.domain.Event;

public class EventRepository extends Repository<Event> {
    public EventRepository() {
        type = Event.class;
    }

    public void save(Event event) {
        String sql = "INSERT INTO Event (userId, type, creationTime) VALUES (?, ?, NOW())";
        saveHelper(event, sql, new Object[] {event.getUserId(), event.getType().toString()});
    }
}
