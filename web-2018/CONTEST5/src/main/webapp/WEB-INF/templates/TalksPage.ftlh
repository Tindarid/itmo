<#import "common.ftl" as c>

<@c.page>
<div class="datatable">
    <div class="caption">Messages</div>
    <table>
        <thead>
        <tr>
            <th>#</th>
            <th>To/From</th>
            <th>Text</th>
            <th>Time</th>
        </tr>
        </thead>
        <tbody>
        <#list talks as talk>
            <tr>
                <td>
                    ${talk_index + 1}
                </td>
                <td>
                    ${talk.adr}
                </td>
                <td>
                    ${talk.text}
                </td>
                <td>
                    ${talk.time}
                </td>
            </tr>
        </#list>
    </table>
</div>
<div class="form-box">
    <div class="header">Send a message</div>
    <div class="body">
        <form method="post" action="/talks">
            <div class="adrfield">
                <div class="name">
                    <label for="adress">To: </label>
                </div>
                <div class="value">
                    <input id="adress" name="adress" value="${adress!}"/>
                </div>
            </div>
            <input type="hidden" name="action" value="sendmessage">
            <textarea name="messagetext">${messagetext!}</textarea>
            <div class="button-field">
                <input type="submit" value="Send">
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
