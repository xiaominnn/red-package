/*
 * CTcpServer类成员函数的实现
 */

#include "CTcpServer.h"

#define LISTEN_BACKLOG 5

/*构造函数*/
CTcpServer::CTcpServer(std::string ip, unsigned int port)
    :listenfd(0)
{
    /*创建socket套接字*/
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd < 0)
    {
        std::cerr << "create socket failed!" << std::endl;
        exit(-1);
    }

    struct sockaddr_in serv_addr;/*服务器ip*/

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr);
    serv_addr.sin_port = htons(port);

    if(bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "bind failed!" << std::endl;
        exit(-1);
    }
    if(listen(listenfd, LISTEN_BACKLOG) < 0)
    {
        std::cerr << "Failed to listen to socket!" << std::endl;
        exit(-1);
    }

    /*设置该监听套接字地址可重用*/
    int reuse = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
}
CTcpServer::~CTcpServer()
{
    close(listenfd);
}
/*
 * 函数功能：获取监听描述符
 */
int CTcpServer::get_listenfd() const
{
    return listenfd;
}
