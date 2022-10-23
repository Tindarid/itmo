<#import "common.ftl" as c>

<@c.page>
<div class="register form-box">
    <div class="header">Register</div>
    <div class="body">
        <form method="post" action="/register">
            <input type="hidden" name="action" value="register">
            <div class="field">
                <div class="name">
                    <label for="login">Login</label>
                </div>
                <div class="value">
                    <input id="login" name="login" value="${login!}"/>
                </div>
            </div>
            <div class="field">
                <div class="name">
                    <label for="password">Password</label>
                </div>
                <div class="value">
                    <input id="password" type="password" name="password" value="${password!}"/>
                </div>
            </div>
            <div class="button-field">
                <input type="submit" value="Register">
            </div>
            <div class="error"></div>
        </form>
    </div>
</div>
<script>
    validationOfUser(".register form", "register", "You are registered. Welcome!");
</script>
</@c.page>
