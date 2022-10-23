package ru.itmo.wp.servlet;

import javax.servlet.FilterChain;
import javax.servlet.ServletException;
import javax.servlet.http.HttpFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import ru.itmo.wp.util.ImageUtils;
import java.util.Random;
import java.io.OutputStream;
import java.util.Base64;

public class CaptchaFilter extends HttpFilter {
    @Override
    protected void doFilter(HttpServletRequest request, HttpServletResponse response, FilterChain chain) throws IOException, ServletException {
        String method = request.getMethod();
        HttpSession session = request.getSession();
        if ("GET".equals(method)) {
            if (request.getRequestURI().endsWith(".ico")) {
                chain.doFilter(request, response);
                return;
            }
            String isPassed = (String)session.getAttribute("captcha");
            if (isPassed == null || !isPassed.equals("passed")) {
                writeNewCaptcha(request, response);
                session.setAttribute("last-request", request.getRequestURI());
            } else {
                chain.doFilter(request, response);
            }
        } else if ("POST".equals(method) && "/captcha".equals(request.getRequestURI())) {
            if (request.getParameter("number").equals(session.getAttribute("number"))) {
                session.setAttribute("captcha", "passed");
                response.sendRedirect((String)session.getAttribute("last-request"));
            } else {
                writeNewCaptcha(request, response);
            }
        } else {
            chain.doFilter(request, response);
        }
    }

    private void writeNewCaptcha(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession();
        byte[] encodedImage = generateCaptcha(session);
        OutputStream stream = response.getOutputStream();
        writeCaptcha(stream, encodedImage);
        writeForm(stream);
    }
    private byte[] generateCaptcha(HttpSession session) {
        Integer number = (new Random()).nextInt(900) + 100;
        session.setAttribute("number", number.toString());
        session.setAttribute("captcha", "processed");
        byte[] image = ImageUtils.toPng(Integer.toString(number));
        return Base64.getEncoder().encode(image);
    }

    private void writeCaptcha(OutputStream outputStream, byte[] img) throws IOException {
        outputStream.write("<div><img src=\"data:image/png;base64, ".getBytes());
        outputStream.write(img);
        outputStream.write("\"></div>\n".getBytes());
        outputStream.flush();
    }

    private void writeForm(OutputStream outputStream) throws IOException {
        outputStream.write(("<div class=\"captcha-form\">" +
                           "    <form action=\"captcha\" method=\"post\">" +
                           "        <input name=\"number\" id=\"captcha_id\">" +
                           "    </form>" +
                           "</div>").getBytes());
    }
}

