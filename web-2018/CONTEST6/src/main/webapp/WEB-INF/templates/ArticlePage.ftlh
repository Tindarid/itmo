<#import "common.ftl" as c>

<@c.page>
<div class="article form-box">
    <div class="header">Create an article</div>
    <div class="body">
        <form method="post" action="/article">
            <div class="checkbox-field">
                <input type="checkbox" class="checkbox-input" name="ishidden">
                <div class="name">
                    <label for="checkbox">Hide: </label>
                </div>
            </div>
            <div class="titlefield">
                <div class="name">
                    <label for="title">Title: </label>
                </div>
                <div class="value">
                    <input id="title" name="title" value="${title!}"/>
                </div>
            </div>
            <input type="hidden" name="action" value="submitarticle">
            <textarea name="articletext">${articletext!}</textarea>
            <div class="button-field">
                <input type="submit" value="Create">
            </div>
            <div class="error"></div>
        </form>
    </div>
</div>
<script>
    validationOfArticle(".article form", "submitarticle", "You have succesfully created article")
</script>
</@c.page>