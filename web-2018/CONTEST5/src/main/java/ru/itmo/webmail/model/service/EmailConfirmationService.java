package ru.itmo.webmail.model.service;

import com.google.common.hash.Hashing;
import ru.itmo.webmail.model.domain.EmailConfirmation;
import ru.itmo.webmail.model.repository.EmailConfirmationRepository;

import java.nio.charset.StandardCharsets;

public class EmailConfirmationService {
    private EmailConfirmationRepository emailConfirmationRepository = new EmailConfirmationRepository();
    private static final String EMAIL_CONFIRM_SALT = "dc3475f2b301851b";

    public void save(EmailConfirmation confirmation, String secret) {
        emailConfirmationRepository.save(confirmation, getConfirmationSha(secret));
    }

    private String getConfirmationSha(String secret) {
        return Hashing.sha256().hashString(EMAIL_CONFIRM_SALT + secret,
                StandardCharsets.UTF_8).toString();
    }

    public EmailConfirmation findBySecret(String secret) {
        return emailConfirmationRepository.findBySecret(secret);
    }
}
