<#import "common.ftl" as c>

<@c.page>
<div class="form-box">
    <div class="header">Add news</div>
    <div class="body">
        <form method="post" action="/addnews">
            <input type="hidden" name="action" value="addnews">
            <textarea name="newstext" value="${newstext!}">Type your news here.</textarea>
            <div class="button-field">
                <input type="submit" value="Submit">
            </div>
            <#if error??>
            <div class="error">
                ${error}
            </div>
            </#if>
        </form>
    </div>
</div>
</@c.page>

