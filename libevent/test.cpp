#include "CLibevent.h"
#include <arpa/inet.h>

#define LISTEN_PORT 9999
#define LISTEN_IP_ADDRESS "127.0.0.1"
#define LISTEN_BACKLOG 32

void do_accept(int listener, short event, void *arg);
void read_cb(struct bufferevent *bev, void *arg);
void write_cb(struct bufferevent *bev, void *arg);
void error_cb(struct bufferevent *bev, short event, void *arg);
int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    inet_pton(AF_INET, LISTEN_IP_ADDRESS, &serv.sin_addr);
    serv.sin_port = htons(LISTEN_PORT);

    if(bind(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
    {
        std::cerr << "bind eror!" << std::endl;
        exit(-1);
    }
    if(listen(sockfd, LISTEN_BACKLOG) < 0)
    {
        std::cerr << "listen error!" << std::endl;
        exit(-1);
    }

    CLibevent *clibevent = new CLibevent();
    int listen_event_flags = EV_READ | EV_PERSIST;
    clibevent->add_event(sockfd, listen_event_flags, do_accept, (void *)clibevent);
    clibevent->dispatch();
    return 0;
}
void do_accept(int listener, short event, void *arg)
{
    CLibevent *clibevent = (CLibevent *)arg;
    evutil_socket_t fd;
    struct sockaddr_in sin;
    socklen_t slen = sizeof(sin);
    fd = accept(listener, (struct sockaddr *)&sin, &slen);
    if (fd < 0) {
        perror("accept");
        return;
    }
    if (fd > FD_SETSIZE) { //这个if是参考了那个ROT13的例子，貌似是官方的疏漏，从select-based例子里抄过来忘了改
        perror("fd > FD_SETSIZE\n");
        return;
    }

    printf("ACCEPT: fd = %u\n", fd);

    int accept_event_flags = EV_READ | EV_WRITE | EV_PERSIST;
    clibevent->add_bufferevent(fd, accept_event_flags, read_cb, NULL, error_cb, arg);
}

void read_cb(struct bufferevent *bev, void *arg)
{
#define MAX_LINE    256
    char line[MAX_LINE+1];
    int n;
    evutil_socket_t fd = bufferevent_getfd(bev);

    while (n = bufferevent_read(bev, line, MAX_LINE), n > 0) {
        line[n] = '\0';
        printf("fd=%u, read line: %s\n", fd, line);

        bufferevent_write(bev, line, n);
    }
}

void write_cb(struct bufferevent *bev, void *arg) {}

void error_cb(struct bufferevent *bev, short event, void *arg)
{
    evutil_socket_t fd = bufferevent_getfd(bev);
    printf("fd = %u, ", fd);
    if (event & BEV_EVENT_TIMEOUT) {
        printf("Timed out\n"); //if bufferevent_set_timeouts() called
    }
    else if (event & BEV_EVENT_EOF) {
        printf("connection closed\n");
    }
    else if (event & BEV_EVENT_ERROR) {
        printf("some other error\n");
    }
    bufferevent_free(bev);
}
