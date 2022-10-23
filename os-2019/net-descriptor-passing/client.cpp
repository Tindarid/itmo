#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#define BUFFER_SIZE 1024
#define SOCKET_NAME "/tmp/my-chat.socket"

char name[BUFFER_SIZE];

void abort(const char* message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int get_fd(int socket) {
    struct msghdr msg = {0};
    char buf[CMSG_SPACE(sizeof(int))], dup[BUFFER_SIZE];
    memset(buf, '\0', sizeof(buf));
    struct iovec io = { .iov_base = &dup, .iov_len = sizeof(dup) };

    msg.msg_iov = &io;
    msg.msg_iovlen = 1;
    msg.msg_control = buf;
    msg.msg_controllen = sizeof(buf);

    if (recvmsg(socket, &msg, 0) < 0) {
        abort("Failed to receive mesage");
    }
    struct cmsghdr* cmsg = CMSG_FIRSTHDR(&msg);

    int* fdptr = (int*)CMSG_DATA(cmsg);
    return *fdptr;
}

int main() {
    int sockfd;
    struct sockaddr_un addr;
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1) {
        abort("Failed to create socket");
    }
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);
    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_un)) == -1) {
        abort("Failed to connect to socket");
    }

    printf("Your name: ");
    scanf("%s", name);
    dup2(get_fd(sockfd), 1);

    while (true) {
        char buffer[BUFFER_SIZE];
        scanf("%s", buffer);
        if (feof(stdin)) {
            break;
        }
        printf("%s: %s\n", name, buffer);
    }

    if (close(sockfd) == -1) {
        abort("Failed to close socket");
    }
    exit(EXIT_SUCCESS);
}
