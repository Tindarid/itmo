<#-- @ftlvariable name="message" type="java.lang.String" -->

<#import "common.ftl" as c>

<@c.page>
    <h1>Welcome to the index page</h1>
    <#if message??>
        <p>${message}</p>
    </#if>
</@c.page>
