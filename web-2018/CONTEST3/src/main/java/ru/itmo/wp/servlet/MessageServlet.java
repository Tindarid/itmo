package ru.itmo.wp.servlet;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import com.google.gson.Gson;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class MessageServlet extends HttpServlet {
    List messages;

    private class Pair {
        private String user;
        private String text;

        Pair(String a, String b) {
            user = a;
            text = b;
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String uri = request.getRequestURI();
        HttpSession session = request.getSession();
        if (messages == null) {
            messages = new ArrayList<Pair>();
        }
        if (uri.equals("/message/auth")) {
            String user = request.getParameter("user");
            if (user != null) {
                session.setAttribute("user", user);
            }
            writeJson(user, response);
        } else if (uri.equals("/message/findAll")) {
            writeJson(messages, response);
        } else if (uri.equals("/message/add")) {
            messages.add(new Pair((String)session.getAttribute("user"), request.getParameter("text")));
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST);
        }
        response.setContentType("application/json");
    }

    private void writeJson(Object objectToWrite, HttpServletResponse response) throws IOException {
        String json = new Gson().toJson(objectToWrite);
        response.getWriter().print(json);
        response.getWriter().flush();
    }
}

