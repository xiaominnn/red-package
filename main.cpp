/*
 * main.cpp:主函数入口
 */

#include "tcpserver/CTcpServer.h"
#include "libevent/CLibevent.h"
#include "database/DataAccess.h"
#include "memcached/MemcAccess.h"
#include "threadpool/CThreadManage.h"
#include "value/Value.h"
#include "value/Args.h"

int main()
{
    Value value; /*常量值类*/
    CThreadManage *thread_manage = new CThreadManage();/*线程池管理类*/
    CTcpServer *tcp_server = new CTcpServer(value::SERV_IP_ADRESS, value::SERV_PORT);/*tcp服务器类*/
    DataAccess *data_access = new DataAccess(value::MYSQL_IP_ADESS, value::MYSQL_PORT, value::MYSQL_USER, value::MYSQL_PASSWORD, value::MYSQL_DATABASE_NAME);/*数据库访问类*/
    MemcAccess *memc_access = new MemcAccess(value::MEMACHED_IP_ADRESS, value::MEMCACHED_PROT);/*memached数据访问类*/
    CLibevent *clibevent = new CLibevent();/*libevent使用类*/
    Args args = new Args(thread_manage, tcp_server, data_access, memc_access, clibevent, NULL);/*传递的框架组件参数指针*/
    /*获取监听套接字描述符,监听事件标志*/
    int listenfd = tcp_server->get_listenfd();
    int listen_event_flags = EV_READ | EV_PERSIST;
    clibevent->add_event(listenfd, listen_event_flags, ,(void *)args);

    clibevent->dispatch();
    return 0;
}
