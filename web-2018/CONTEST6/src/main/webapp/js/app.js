window.setMessage = function(message) {
    localStorage.setItem("message", message);
};

window.getMessage = function() {
    return localStorage.getItem("message");
};

window.removeMessage = function() {
    return localStorage.removeItem("message");
};

window.cloneTemplate = function ($template) {
    return $($template.prop('content')).clone();
};

function validationOfUser(form, action, message) {
    $(function() {
        $(form).submit(function () {
            var login = $(this).find("input[name='login']").val();
            var password = $(this).find("input[name='password']").val();
            var $error = $(this).find(".error").text("");
            $.post("", {action: action, login: login, password: password}, function (response) {
                if (response["success"]) {
                    setMessage(message);
                    document.location.href = "/";
                } else {
                    $error.text(response["error"]);
                }
            });
            return false;
        });
    })
}

function validationOfArticle(form, action, message) {
    $(function() {
        $(form).submit(function () {
            var title = $(this).find("input[name='title']").val();
            var articletext = $(this).find("textarea[name='articletext']").val();
            var ishidden = $(this).find("input[name='ishidden']").prop("checked");
            var $error = $(this).find(".error").text("");
            $.post("", {action: action, title: title, articletext: articletext, ishidden: ishidden}, function (response) {
                if (response["success"]) {
                    setMessage(message);
                    document.location.href = "/";
                } else {
                    $error.text(response["error"]);
                }
            });
            return false;
        });
    })
}
