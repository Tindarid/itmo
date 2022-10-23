#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#define BUFFER_SIZE 1024
#define SOCKET_NAME "/tmp/my-chat.socket"
#define BACKLOG 10

void abort(const char* message) {
    perror(message);
    exit(EXIT_FAILURE);
}

void send_fd(int socket) {
    struct msghdr msg = {0};
    struct cmsghdr *cmsg;
    char buf[CMSG_SPACE(sizeof(int))], dup[BUFFER_SIZE];
    memset(buf, '\0', sizeof(buf));
    struct iovec io = { .iov_base = &dup, .iov_len = sizeof(dup) };

    msg.msg_iov = &io;
    msg.msg_iovlen = 1;
    msg.msg_control = buf;
    msg.msg_controllen = sizeof (buf);

    cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(int));

    int* fdptr = (int*)CMSG_DATA(cmsg);
    *fdptr = 1;

    if(sendmsg(socket, &msg, 0) == -1) {
        abort("Error sending server stdout");
    }
}

int main() {
    int sockfd;
    struct sockaddr_un addr;
    socklen_t peer_addr_size;

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1) {
        abort("Failed to create socket");
    }
    if (unlink(SOCKET_NAME) == -1 && errno != ENOENT) {
        abort("Error while removing socket file");
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);
    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_un)) == -1) {
        abort("Failed to bind to socket");
    }
    if (listen(sockfd, BACKLOG) == -1) {
        abort("Failed to listen on socket");
    }

    printf("Welcome to our chat!\n");
    int clientfd;
    while ((clientfd = accept(sockfd, NULL, NULL)) != -1) {
        send_fd(clientfd);
    }
    abort("Failed to accept incoming connection");
}
