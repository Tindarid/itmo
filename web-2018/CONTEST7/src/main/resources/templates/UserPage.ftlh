<#import "./common.ftlh" as c>

<@c.page>
    <#if userInfo??>
        <p>Id: ${userInfo.id!}</p>
        <p>Login: ${userInfo.login!}</p>
        <p>Creation time: ${userInfo.creationTime!}</p>
    <#else>
        <p>No such user</p>
    </#if>
</@c.page>
