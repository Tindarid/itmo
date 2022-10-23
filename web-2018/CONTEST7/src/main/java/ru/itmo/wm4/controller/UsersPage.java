package ru.itmo.wm4.controller;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import ru.itmo.wm4.domain.User;
import ru.itmo.wm4.service.UserService;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

@Controller
public class UsersPage extends Page {
    private final UserService userService;

    public UsersPage(UserService userService) {
        this.userService = userService;
    }

    @GetMapping(path = "/users")
    public String main(Model model, HttpSession httpSession) {
        if (getUser(httpSession) == null) {
            return "redirect:/";
        }
        model.addAttribute("users", userService.findAll());
        return "UsersPage";
    }

    @PostMapping(path = "/switch")
    public String switchDisabled(Model model, HttpServletRequest request) {
        User curUser = getUser(request.getSession());
        if (curUser == null) {
            return "redirect:/";
        }
        try {
            Long userId = Long.parseLong(request.getParameter("userId"));
            User user = userService.findById(userId);
            if (user != null) {
                boolean newDisabled = !user.isDisabled();
                userService.switchDisabled(userId, newDisabled);
                if (newDisabled && curUser.getId() == userId) {
                    unsetUser(request.getSession());
                }
            }
        } catch (NumberFormatException e) {
            return "redirect:/";
        }
        return "redirect:/users";
    }
}
