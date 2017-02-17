/*
 * CLibevent类的成员函数实现
 */

#include "CLibevent.h"

CLibevent::CLibevent():base(NULL)
{
    base = event_base_new();
    if(base == NULL)
    {
        std::cerr << "create event base failed!" << std::endl;
        exit(-1);
    }
}
CLibevent::~CLibevent()
{
    if(base != NULL)
    {
        event_base_free(base);
    }
}
/*
 * 函数功能：将要监听的事件添加进事件管理器中
 * 参数：要监听的文件描述符，事件标志，触发的函数，传给触发函数的参数
 */
bool CLibevent::add_event(int fd, int flags,Callback_event func,void *args)
{
    evutil_socket_t sockfd = fd;/*通用的平台无关的文件描述符*/
    evutil_make_socket_nonblocking(sockfd);
    /*添加事件*/
    event * new_event = event_new(base, sockfd, flags, func, args);
    if(new_event == NULL)
    {
        std::cerr << "create event failed!" << std::endl;
        return false;
    }
    event_add(new_event, NULL);
    return true;
}
/*
 * 函数功能：将带缓冲功能的事件添加进事件管理器中
 */
bool CLibevent::add_bufferevent(int fd, int flags,
        Callback_read cb_read, Callback_write cb_write,
        Callback_error cb_error, void *args)
{
    evutil_socket_t sockfd = fd;/*通用的平台无关的文件描述符*/
    evutil_make_socket_nonblocking(sockfd);

    bufferevent *new_bufferevent = bufferevent_socket_new(base, sockfd, BEV_OPT_CLOSE_ON_FREE);
    if(new_bufferevent == NULL)
    {
        return false;
    }
    bufferevent_setcb(new_bufferevent, cb_read, cb_write, cb_error, args);/*函数名要看清楚!!!*/
    bufferevent_enable(new_bufferevent, flags);
}
/*
 * 函数功能：事件循环
 */
void CLibevent::dispatch()
{
    event_base_dispatch(base);
}
/*
 * 函数功能：返回事件管理器base
 */
event_base *CLibevent::get_event_base() const
{
    return this->base;
}
