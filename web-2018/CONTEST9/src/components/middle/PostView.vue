<template>
    <article v-if="post !== undefined" >
        <div class="title">{{post.title}}</div>
        <div class="information">By {{users[post.userId].login}}</div>
        <div class="body">{{post.text}}</div>
    </article>
</template>

<script>
    export default {
        name: "PostView",
        props: ['post', 'users'],
    }
</script>

<style scoped>

</style>
