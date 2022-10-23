<#import "/spring.ftl" as spring>
<#import "./common.ftlh" as c>

<#macro error field>
    <@spring.bind field/>
    <#list spring.status.errorMessages as error>
        <div class="error">${error}</div>
        <#break/>
    </#list>
</#macro>

<@c.page>
<div class="addnotice form-box">
    <div class="header">Add news</div>
    <div class="body">
        <form method="post" action="/addnotice">
            <input type="hidden" name="action" value="addnotice">
            <textarea name="content" value="${submitForm.content!}">Type your notice here.</textarea>
            <div class="button-field">
                <input type="submit" value="Submit">
            </div>
            <@error 'submitForm.content'/>
        </form>
    </div>
</div>
</@c.page>