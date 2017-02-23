/*
 * Args成员函数实现
 */

#include "Args.h"

Args::Args(CThreadManage *arg_manage, CTcpServer *arg_tcp, DataAccess *arg_data_access, MemcAccess *arg_memc_access, CLibevent *arg_clibevent, std::string *arg_message)
    : thread_manage(arg_manage), tcp_server(arg_tcp), data_access(arg_data_access), memc_access(arg_memc_access), clibevent(arg_clibevent), message(arg_message)
{
}
Args::~Args()
{
}
CThreadManage *Args::get_thread_manage() const
{
    return thread_manage;
}
CTcpServer *Args::get_tcp_server() const
{
    return tcp_server;
}
DataAccess *Args::get_data_access() const
{
    return data_access;
}
MemcAccess *Args::get_memc_access() const
{
    return memc_access;
}
CLibevent *Args::get_clibevent() const
{
    return clibevent;
}
std::string *Args::get_message() const
{
    return message;
}
void Args::set_message(std::string *new_message)
{
    message = new_message;
}
