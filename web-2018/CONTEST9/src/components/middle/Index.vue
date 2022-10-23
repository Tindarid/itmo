<template>
    <div>
        <article v-for="post in viewPosts" :post="post" :users="users" :key="post.id">
            <div class="title">
                <a href="#page=PostView" @click="viewPost(post.id)">{{post.title}}</a>
            </div>
            <div class="information">
                By {{users[post.userId].login}}
            </div>
            <div class="body">
                {{post.text}}
            </div>
        </article>
    </div>
</template>

<script>
    export default {
        name: "Index",
        props: ['posts', 'users'],
        computed: {
            viewPosts: function () {
                return Object.values(this.posts).reverse();
            }
        },
        methods: {
            viewPost: function (postId) {
                this.$root.$emit("onViewPost", postId);
            }
        }
    }
</script>

<style scoped>

</style>
