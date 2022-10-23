<template>
    <div class="middle">
        <Sidebar :users="users" :posts="posts"/>
        <main>
            <Index :posts="posts" :users="users" v-if="page === 'Index'"/>
            <Enter v-if="page === 'Enter'"/>
            <Register v-if="page === 'Register'"/>
            <AddPost v-if="page === 'AddPost'"/>
            <EditPost v-if="page === 'EditPost'"/>
            <Users :users="users" v-if="page === 'Users'"/>
            <PostView :post="curPost" :users="users" v-if="page === 'PostView'"/>
        </main>
    </div>
</template>
<script>
    import Index from './middle/Index';
    import Enter from './middle/Enter';
    import Register from './middle/Register';
    import AddPost from './middle/AddPost';
    import EditPost from "./middle/EditPost";
    import Sidebar from './middle/Sidebar';
    import Users from './middle/Users';
    import PostView from './middle/PostView';

    export default {
        name: "Middle",
        data: function () {
            return {
                page: "Index",
                curPost: undefined
            }
        },
        props: ['users', 'posts'],
        components: {
            EditPost,
            Index,
            Enter,
            Register,
            AddPost,
            Sidebar,
            Users,
            PostView
        },
        beforeCreate() {
            this.$root.$on("onChangePage", (page) => {
                this.page = page;
            });
            this.$root.$on("onViewPost", (postId) => {
                this.page = "PostView";
                this.curPost = this.posts[postId];
            });
        }
    }
</script>

<style scoped>

</style>
