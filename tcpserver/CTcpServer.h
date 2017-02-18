/*
 * 对tcp协议的三次握手进行封装
 */
#ifndef C_TCP_SERVER_H
#define C_TCP_SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#include <cstring>

#include <string>
#include <iostream>

class CTcpServer
{
public:
    CTcpServer(std::string ip, unsigned int port);
    ~CTcpServer();
    /*
     * 函数功能：获取监听描述符
     */
    int get_listenfd() const;
private:
    int listenfd;/*监听socket文件描述符*/
};
#endif
