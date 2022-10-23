package ru.itmo.wm4.controller;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.*;
import ru.itmo.wm4.domain.Comment;
import ru.itmo.wm4.domain.Notice;
import ru.itmo.wm4.domain.Role;
import ru.itmo.wm4.security.AnyRole;
import ru.itmo.wm4.security.Guest;

import javax.servlet.http.HttpSession;
import javax.validation.Valid;

@Controller
public class ShowNoticePage extends Page {
    @Guest
    @GetMapping(path = "/notice/{reqid}")
    public String showNoticeGet(@PathVariable("reqid") String requestedId, Model model, HttpSession session) {
        try {
            Long id = Long.parseLong(requestedId);
            Notice notice = getNoticeService().findById(id);
            if (notice == null) {
                return "redirect:/";
            }
            model.addAttribute("notice", notice);
            if (getUser(session) != null) {
                model.addAttribute("new_comment", new Comment());
            }
            return "ShowNoticePage";
        } catch (NumberFormatException e) {
            return "redirect:/";
        }
    }

    @AnyRole({Role.Name.ADMIN, Role.Name.USER})
    @PostMapping(path = "/comment/{reqid}")
    public String showNoticePost(@PathVariable("reqid") String requestedId,
                                 @Valid @ModelAttribute("new_comment") Comment comment,
                                 BindingResult bindingResult, Model model, HttpSession httpSession) {
        try {
            Long id = Long.parseLong(requestedId);
            Notice notice = getNoticeService().findById(id);
            if (notice == null) {
                return "redirect:/";
            }

            if (bindingResult.hasErrors()) {
                model.addAttribute("notice", notice);
                return "ShowNoticePage";
            }

            getCommentService().save(comment, notice, getUser(httpSession));
            return "redirect:/notice/" + notice.getId();
        } catch (NumberFormatException e) {
            return "redirect:/";
        }
    }
}
