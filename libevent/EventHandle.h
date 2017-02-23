/*
 * 用于对libevent使用中事件的处理函数进行封装
 */
#ifndef EVENT_HANDLE_H
#define EVENT_HANDLE_H

#include "CLibevent.h"
#include "../value/Args.h"

/*
 * 事件处理的抽象基类
 */
class EventHandle
{
public:
    virtual void do_accept(int listener, short event, void *args) = 0;
    virtual void do_read(bufferevent *bev, void *args) = 0;
    virtual void do_write(bufferevent *bev, void *args) = 0;
    virtual void do_error(bufferevent *bev, short, void *args) = 0;
};

/*
 * Red Package Event Handle红包的事件处理类
 */
class RPEventHandle : public EventHandle
{
public:
    virtual void do_accept(int listener, short event, void *args);
    virtual void do_read(bufferevent *bev, void *args);
    virtual void do_write(bufferevent *bev, void *args);
    virtual void do_error(bufferevent *bev, short, void *args);
};
#endif
