#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include "../tcpserver/CTcpServer.h"
#include "../libevent/CLibevent.h"
#include "../database/DataAccess.h"
#include "../memcached/MemcAccess.h"
#include "../threadpool/CThreadManage.h"
#include "Value.h"

/*
 * Arguements
 * 项目框架的各组件指针组成
 * 用于传递参数
 */
class Args
{
public:
    Args(CThreadManage *arg_manage, CTcpServer *arg_tcp, DataAccess *arg_data_access, MemcAccess *arg_memc_access, CLibevent *arg_clibevent, std::string *arg_message);
    ~Args();
    CThreadManage *get_thread_manage() const;
    CTcpServer *get_tcp_server() const;
    DataAccess *get_data_access() const;
    MemcAccess *get_memc_access() const;
    CLibevent *get_clibevent() const;
    std::string *get_message() const;
    void set_message(std::string *new_string);
private:
    CThreadManage *thread_manage;
    CTcpServer *tcp_server;
    DataAccess *data_access;
    MemcAccess *memc_access;
    CLibevent *clibevent;
    std::string *message;
};

#endif
