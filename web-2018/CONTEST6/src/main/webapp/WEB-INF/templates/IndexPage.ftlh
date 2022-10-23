<#-- @ftlvariable name="message" type="java.lang.String" -->

<#import "common.ftl" as c>

<@c.page>
    <#if message??>
        <p>${message}</p>
    </#if>
<main2>
    <p class="no-data"></p>
</main2>
<template class="article-temp">
    <article>
        <div class="title">{{title}}</div>
        <div class="information">{{login}}</div>
        <div class="body">{{text}}</div>
        <div class="footer">
            <div class="left">
                <img src="img/voteup.png" title="Vote Up" alt="Vote Up"/>
                <span class="positive-score">+173</span>
                <img src="img/votedown.png" title="Vote Down" alt="Vote Down"/>
            </div>
            <div class="right">
                <div class="time">{{time}}</div>
            </div>
        </div>
    </article>
</template>
<script>
    $(function () {
        var $noData = $("main .no-data");
        $noData.text("Loading...");
        $.post("", {action: "findarticles"}, function (articles) {
            var $mainbody = $("main2");
            if (articles.length > 0) {
                $mainbody.empty();
                articles.forEach(function (article) {
                    var $art = cloneTemplate($("template.article-temp"));
                    $art.find(".title").text(article.title);
                    $art.find(".body").text(article.text);
                    $art.find(".information").text("By " + article.user);
                    $art.find(".time").text(article.time);
                    $mainbody.append($art);
                });
            } else {
                $noData.text("No articles");
            }
        })
    })
</script>
</@c.page>
