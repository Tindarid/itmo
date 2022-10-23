package ru.itmo.webmail.web;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;
import freemarker.template.TemplateExceptionHandler;
import ru.itmo.webmail.web.exception.RedirectException;
import ru.itmo.webmail.web.page.IndexPage;
import ru.itmo.webmail.web.page.NotFoundPage;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.*;

public class FrontServlet extends HttpServlet {
    private static final String BASE_PAGE_NAME = FrontServlet.class.getName().substring(0,
            FrontServlet.class.getName().length() - FrontServlet.class.getSimpleName().length()) + "page";
    private Configuration sourceFreemarkerConfiguration;
    private Configuration targetFreemarkerConfiguration;

    private Configuration newConfiguration(File templateDirectory) throws ServletException {
        Configuration freemarkerConfiguration = new Configuration(Configuration.VERSION_2_3_28);
        try {
            freemarkerConfiguration.setDirectoryForTemplateLoading(templateDirectory);
        } catch (IOException e) {
            throw new ServletException(e);
        }
        freemarkerConfiguration.setDefaultEncoding("UTF-8");
        freemarkerConfiguration.setTemplateExceptionHandler(TemplateExceptionHandler.RETHROW_HANDLER);
        freemarkerConfiguration.setLogTemplateExceptions(false);
        freemarkerConfiguration.setWrapUncheckedExceptions(true);
        return freemarkerConfiguration;
    }

    @Override
    public void init(ServletConfig config) throws ServletException {
        sourceFreemarkerConfiguration = newConfiguration(new File(config.getServletContext().getRealPath("."),
                "../../src/main/webapp/WEB-INF/templates"));
        targetFreemarkerConfiguration = newConfiguration(new File(config.getServletContext().getRealPath("WEB-INF/templates")));
    }

    private Template newTemplate(String templateName) throws ServletException {
        Template template = null;
        try {
            template = sourceFreemarkerConfiguration.getTemplate(templateName);
        } catch (IOException ignored) {
            // No operations.
        }
        if (template == null) {
            try {
                template = targetFreemarkerConfiguration.getTemplate(templateName);
            } catch (IOException e) {
                throw new ServletException(e);
            }
        }
        return template;
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        process(request, response);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        process(request, response);
    }

    private void process(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Route route = findRoute(request);

        try {
            processRoute(route, request, response);
        } catch (NotFoundException e) {
            try {
                processRoute(Route.getNotFoundPageRoute(), request, response);
            } catch (NotFoundException f) {
                throw new ServletException("Can't find a page for 404.", f);
            }
        }
    }

    void resolveMethod(HttpServletRequest request, HttpServletResponse response,
                       Class<?> clazz, String methodName, Object page,
                       Map<String, Object> view) throws NotFoundException, IOException, ServletException {
        Method method = null;
        for (Class<?> c = clazz; method == null && c != null; c = c.getSuperclass()) {
            Method[] methods = c.getDeclaredMethods();
            for (Method m : methods) {
                if (m.getName().equals(methodName)) {
                    method = m;
                }
            }
        }
        if (method == null) {
            throw new NotFoundException();
        }
        try {
            method.setAccessible(true);
            Class[] needParams = method.getParameterTypes();
            List params = new ArrayList<Class>();
            for (Class c : needParams) {
                if (c == HttpServletRequest.class) {
                    params.add(request);
                } else if (c == Map.class) {
                    params.add(view);
                } else {
                    throw new NotFoundException();
                }
            }
            method.invoke(page, params.toArray());
        } catch (InvocationTargetException e) {
            Throwable throwable = e.getTargetException();
            if (throwable instanceof RedirectException) {
                RedirectException redirectException = (RedirectException) throwable;
                String action = redirectException.getAction();
                if (action == null) {
                    response.sendRedirect(redirectException.getUrl());
                } else {
                    response.sendRedirect(redirectException.getUrl() + "?action=" + action);
                }
                return;
            }
            throw new ServletException("Can't run page method [clazz=" + clazz + ", method=" + method + "].", e);
        } catch (Exception e) {
            throw new ServletException("Can't run page method [clazz=" + clazz + ", method=" + method + "].", e);
        }
    }

    private void processRoute(Route route, HttpServletRequest request, HttpServletResponse response) throws NotFoundException, ServletException, IOException {
        Class<?> clazz = route.newClass();
        Object page;
        try {
            page = clazz.newInstance();
        } catch (Exception e) {
            throw new ServletException("Can't create page instance [clazz=" + clazz + "].", e);
        }
        Map<String, Object> view = new HashMap<>();
        resolveMethod(request, response, clazz, "before", page, view);
        resolveMethod(request, response, clazz, route.getAction(), page, view);
        resolveMethod(request, response, clazz, "after", page, view);
        try {
            Template template = newTemplate(clazz.getSimpleName() + ".ftlh");
            response.setContentType("text/html");
            PrintWriter writer = response.getWriter();
            template.process(view, writer);
            writer.flush();
        } catch (TemplateException e) {
            throw new ServletException(e);
        }
    }

    private Route findRoute(HttpServletRequest request) {
        String requestURI = request.getRequestURI();
        if (requestURI.length() <= 1) {
            return Route.getIndexPageRoute();
        }

        StringBuilder className = new StringBuilder(BASE_PAGE_NAME);
        Arrays.stream(requestURI.split("/")).filter(s -> !s.isEmpty())
                .forEach(s -> {
                    className.append('.');
                    className.append(s);
                });
        int pos = className.lastIndexOf(".") + 1;
        className.setCharAt(pos, Character.toUpperCase(className.charAt(pos)));

        String action = request.getParameter("action");
        if (action != null && action.isEmpty()) {
            action = null;
        }

        return new Route(className + "Page", action);
    }

    private static final class Route {
        private final String className;
        private final String action;

        private Route(String className, String action) {
            this.className = className;
            this.action = action;
        }

        private static Route getNotFoundPageRoute() {
            return new Route(NotFoundPage.class.getName(), null);
        }

        private static Route getIndexPageRoute() {
            return new Route(IndexPage.class.getName(), null);
        }

        private Class<?> newClass() throws NotFoundException {
            try {
                return Class.forName(className);
            } catch (ClassNotFoundException e) {
                throw new NotFoundException();
            }
        }

        private String getAction() {
            return action != null ? action : "action";
        }
    }

    private static final class NotFoundException extends Exception {
    }
}
