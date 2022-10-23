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
<div class="form-box">
    <div class="header">By ${notice.user.login} at ${notice.creationTime}</div>
    <div class="body">
        <div class="fieldwithtext">
            ${notice.text}
            <br>
            <#list notice.tags as tag>
                <small>
                    <div class="tag">#${tag.name} </div>
                </small>
            </#list>
        </div>
        <#if user??>
            <form method="post" action="/comment/${notice.id}">
                <div class="field">
                    <div class="name">
                        <label for="text">Comment this:</label>
                    </div>
                    <div class="value">
                        <textarea id="text" rows="3" name="text">${new_comment.text!?html}</textarea>
                    </div>
                    <@error 'new_comment.text'/>
                </div>
                <div class="button-field">
                    <input type="submit" value="Submit">
                </div>
            </form>
        <#else>
            <div class="fieldwithtext">
                Log in to leave a comment
            </div>
        </#if>
        <#list notice.comments as comment>
            <div class="field">
                <div class="name">
                    By ${comment.user.login!?html}
                </div>
                <div class="value">
                    <textarea disabled>${comment.text!?html}</textarea>
                </div>
            </div>
        </#list>
    </div>
</div>
</@c.page>
