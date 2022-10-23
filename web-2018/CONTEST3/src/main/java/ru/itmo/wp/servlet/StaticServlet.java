package ru.itmo.wp.servlet;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.File;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.file.Files;

public class StaticServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String mainUri = request.getRequestURI();
        String[] uris = mainUri.split("\\+");
        String MIME = "";
        OutputStream outputStream = response.getOutputStream();
        for (String uri : uris) {
            File file = new File("./src/main/webapp/static/" + uri);
            if (!file.isFile()) {
                file = new File(getServletContext().getRealPath("/static/" + uri));
            }
            if (file.isFile()) {
                if (MIME.isEmpty()) {
                    MIME = getContentTypeFromName(uri);
                }
                Files.copy(file.toPath(), outputStream);
                outputStream.flush();
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND);
            }
        }
        response.setContentType(MIME);
    }

    private String getContentTypeFromName(String name) {
        name = name.toLowerCase();

        if (name.endsWith(".png")) {
            return "image/png";
        }

        if (name.endsWith(".jpg")) {
            return "image/jpeg";
        }

        if (name.endsWith(".html")) {
            return "text/html";
        }

        if (name.endsWith(".css")) {
            return "text/css";
        }

        if (name.endsWith(".js")) {
            return "application/javascript";
        }

        throw new IllegalArgumentException("Can't find content type for '" + name + "'.");
    }
}
