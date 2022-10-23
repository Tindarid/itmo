package ru.itmo.webmail.web.page;

import ru.itmo.webmail.model.domain.Talk;
import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.exception.ValidationException;
import ru.itmo.webmail.web.exception.RedirectException;

import javax.servlet.http.HttpServletRequest;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class TalksPage extends Page{
    @Override
    public void before(HttpServletRequest request, Map<String, Object> view) {
        super.before(request, view);

        if (getUser() == null) {
            throw new RedirectException("/index");
        }
    }

    private void sendmessage(HttpServletRequest request, Map<String, Object> view) {
        String adr = request.getParameter("adress");
        String text = request.getParameter("messagetext");
        long sourceId = (Long)request.getSession().getAttribute(USER_ID_SESSION_KEY);
        long targetId;
        User user;
        try {
            getTalkService().validate(text);
            user = getUserService().findByLoginOrEmail(adr);
            if (user == null) {
                throw new ValidationException("No such username in database");
            }
            targetId = user.getId();
            if (targetId == sourceId) {
                throw new ValidationException("Can't send message to yourself");
            }
        } catch (ValidationException e) {
            action(request, view);
            view.put("adress", adr);
            view.put("messagetext", text);
            view.put("error", e.getMessage());
            return;
        }
        Talk talk = new Talk();
        talk.setSourceUserId(sourceId);
        talk.setTargetUserId(targetId);
        talk.setText(text);
        getTalkService().save(talk);
        throw new RedirectException("/index", "messageSent");
    }

    private void action(HttpServletRequest request, Map<String, Object> view) {
        long userId = (Long)request.getSession().getAttribute(USER_ID_SESSION_KEY);
        List<Talk> talks = getTalkService().findAllFromId(userId);
        List<TalkView> talkViews = new ArrayList<>();
        for (Talk t : talks) {
            talkViews.add(new TalkView(userId, t));
        }
        view.put("talks", talkViews);
    }

    public class TalkView {
        private String adr;
        private String text;
        private String time;

        public TalkView(long userId, Talk t) {
            text = t.getText();
            time = t.getCreationTime().toString();
            long sourceId = t.getSourceUserId();
            long targetId = t.getTargetUserId();
            if (sourceId == userId) {
                adr = "To: " + getUserService().find(targetId).getLogin();
            } else {
                adr = "From: " + getUserService().find(sourceId).getLogin();
            }
        }

        public String getAdr() {
            return adr;
        }

        public void setAdr(String adr) {
            this.adr = adr;
        }

        public String getText() {
            return text;
        }

        public void setText(String text) {
            this.text = text;
        }

        public String getTime() {
            return time;
        }

        public void setTime(String time) {
            this.time = time;
        }
    }
}
