<#-- @ftlvariable name="users" type="ru.itmo.webmail.model.domain.User[]" -->
<#import "common.ftl" as c>

<@c.page>
<div class="datatable articles">
    <div class="caption">Users</div>
    <table>
        <thead>
        <tr>
            <th>#</th>
            <th>Title</th>
            <th>Switch</th>
        </tr>
        </thead>
        <tbody>
        <tr>
            <td colspan="3" class="no-data">No data</td>
        </tr>
        </tbody>
    </table>
</div>
<template class="articles-tr">
    <tr>
        <td class="id">{{#}}</td>
        <td class="title">{{title}}</td>
        <td class="switching">
            <div class="button-field">
                <input type="submit" class="switchHidden">
            </div>
        </td>
    </tr>
</template>
<script>
    $(function () {
        var $noData = $(".articles .no-data");
        $noData.text("Loading...");
        $.post("", {action: "find"}, function (articles) {
            var $tbody = $(".articles tbody");
            if (articles.length > 0) {
                $tbody.empty();
                articles.forEach(function (article) {
                    var $tr = cloneTemplate($("template.articles-tr"));
                    $tr.find(".id").text(article.id);
                    $tr.find(".title").text(article.title);
                    if (article.hidden) {
                        $tr.find(".switchHidden").attr("value", "Show");
                    } else {
                        $tr.find(".switchHidden").attr("value", "Hide");
                    }
                    $tbody.append($tr);
                });
            } else {
                $noData.text("No data");
            }
        })
    });
    $(function() {
        $(".datatable.articles").on("click", ".switchHidden", function () {
            var button = $(this);
            var articleid = $(this).parent().parent().parent().find(".id").html();
            var old = this.value;
            button.attr("value", "Wait");
            button.attr("disabled", "");
            $.post("", {action: "switchHidden", articleid : articleid}, function (response) {
                if (response["success"]) {
                    if (old === "Hide") {
                        button.attr("value", "Show");
                    } else {
                        button.attr("value", "Hide");
                    }
                }
                button.removeAttr("disabled");
            });
            return false;
        });
    })
</script>
</@c.page>
