package ru.itmo.wm4.controller;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.WebDataBinder;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.InitBinder;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;
import ru.itmo.wm4.form.NoticeCredentials;
import ru.itmo.wm4.form.validator.NoticeCredentialsSubmitValidator;
import ru.itmo.wm4.service.NoticeService;

import javax.servlet.http.HttpSession;
import javax.validation.Valid;

@Controller
public class AddnoticePage extends Page {
    private final NoticeService noticeService;
    private final NoticeCredentialsSubmitValidator noticeCredentialsSubmitValidator;

    public AddnoticePage(NoticeService noticeService, NoticeCredentialsSubmitValidator noticeCredentialsSubmitValidator) {
        this.noticeService = noticeService;
        this.noticeCredentialsSubmitValidator = noticeCredentialsSubmitValidator;
    }

    @InitBinder("NoticeCredentials")
    public void initSubmitFormBinder(WebDataBinder binder) {
        binder.addValidators(noticeCredentialsSubmitValidator);
    }

    @GetMapping(path = "/addnotice")
    public String submitGet(Model model, HttpSession httpSession) {
        if (getUser(httpSession) == null) {
            return "redirect:/";
        }
        model.addAttribute("submitForm", new NoticeCredentials());
        return "AddnoticePage";
    }

    @PostMapping(path = "/addnotice")
    public String submitPost(@Valid @ModelAttribute("submitForm") NoticeCredentials submitForm,
                               BindingResult bindingResult, HttpSession httpSession) {
        if (getUser(httpSession) == null) {
            return "redirect:/";
        }
        if (bindingResult.hasErrors()) {
            return "AddnoticePage";
        }

        noticeService.save(submitForm);

        return "redirect:/";
    }
}
