package ru.itmo.webmail.model.repository;

import ru.itmo.webmail.model.domain.EmailConfirmation;

public class EmailConfirmationRepository extends Repository<EmailConfirmation> {
    public EmailConfirmationRepository() {
        type = EmailConfirmation.class;
    }

    public void save(EmailConfirmation emailConfirmation, String secret) {
        String sql = "INSERT INTO EmailConfirmation (userId, secret, creationTime) VALUES (?, ?, NOW())";
        saveHelper(emailConfirmation, sql, new Object[] {emailConfirmation.getUserId(), secret});
    }

    public EmailConfirmation findBySecret(String secret) {
        String sql = "SELECT * FROM EmailConfirmation WHERE secret=?";
        return performRequest(sql, new Object[] {secret});
    }
}
