<template>
    <section>
        <div class="header">
            By {{users[post.userId].login}}
        </div>
        <div class="body">
            {{post.text}}
        </div>
        <div class="footer">
            <a href="#page=PostView" @click="viewPost(post.id)">View all</a>
        </div>
    </section>

</template>

<script>
    export default {
        props: ['users', 'post'],
        name: "SidebarPost",
        methods: {
            viewPost: function (postId) {
                this.$root.$emit("onViewPost", postId);
            }
        }
    }
</script>

<style scoped>

</style>
