<#-- @ftlvariable name="users" type="ru.itmo.webmail.model.domain.User[]" -->
<#import "common.ftl" as c>

<@c.page>
<div class="datatable users">
    <div class="caption">Users</div>
    <table>
        <thead>
        <tr>
            <th>#</th>
            <th>Login</th>
            <th>Rating</th>
            <th hidden="" class="isadminth">Admin</th>
        </tr>
        </thead>
        <tbody>
        <tr>
            <td colspan="3" class="no-data">No data</td>
        </tr>
        </tbody>
    </table>
</div>
<template class="users-tr">
    <tr>
        <td class="id">{{#}}</td>
        <td class="login">{{login}}</td>
        <td class="rating"></td>
        <td class="isadmin">
            <p></p>
            <div class="button-field">
                <input type="submit" class="switchAdmin">
            </div>
        </td>
    </tr>
</template>
<script>
    $(function () {
        var $noData = $(".users .no-data");
        $.post("", {action: "isAdmin"}, function (isAdmin) {
            if (isAdmin) {
                $(document).find(".isadminth").removeAttr("hidden");
                $noData.attr("colspan", "4");
            } else {
                $(document).find(".isadminth").remove("hidden");
            }
            $noData.text("Loading...");
            $.post("", {action: "find"}, function (users) {
                var $tbody = $(".users tbody");
                if (users.length > 0) {
                    var logins = [];
                    $tbody.empty();
                    users.forEach(function (user) {
                        var $tr = cloneTemplate($("template.users-tr"));
                        $tr.find(".id").text(user.id);
                        $tr.find(".login").text(user.login);
                        if (!isAdmin) {
                            $tr.find(".isadmin").remove();
                        } else {
                            $tr.find(".isadmin").find("p").text(user.admin);
                            if (user.admin) {
                                $tr.find(".isadmin").find("input").attr("value", "Disable");
                            } else {
                                $tr.find(".isadmin").find("input").attr("value", "Enable");
                            }
                        }
                        $tr.find("tr").attr("id", "user_" + user.login.toLowerCase());
                        logins.push(user.login);
                        $tbody.append($tr);
                    });
                    $.ajax({
                        url: "http://codeforces.com/api/user.info",
                        jsonp: "jsonp",
                        dataType: "jsonp",
                        data: {
                            handles: logins.join(";")
                        },
                        success: function(response) {
                            if (response["status"] === "OK") {
                                response["result"].forEach(function (user) {
                                    $("#user_" + user.handle.toLowerCase()).find(".rating").text(user["rating"]);
                                })
                            }
                        }
                    })
                } else {
                    $noData.text("No data");
                }
            })
        })
    })
    $(function() {
        $(".datatable.users").on("click", ".switchAdmin", function () {
            var button = $(this);
            var title = $(this).parent().parent().find("p");
            var userid = $(this).parent().parent().parent().find(".id").html();
            var old = this.value;
            button.attr("value", "Wait");
            button.attr("disabled", "");
            $.post("", {action: "switchAdmin", updateid : userid, oldadmin: title.html()}, function (response) {
                if (response["success"]) {
                    if (old === "Enable") {
                        button.attr("value", "Disable");
                        title.text("true");
                    } else {
                        button.attr("value", "Enable");
                        title.text("false");
                    }
                    if (response["reload"]) {
                        setMessage("You have deleted yourself from admins")
                        document.location.href = "/";
                    }
                }
                button.removeAttr("disabled");
            });
            return false;
        });
    })
</script>
</@c.page>
