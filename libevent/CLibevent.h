/*
 * 对C语言使用libevent的类封装
 */
#ifndef CLIBEVENT_H
#define CLIBEVENT_H

#include <event2/event.h>
#include <event2/bufferevent.h>

#include <iostream>
#include <stdlib.h>


class CLibevent
{
public:
    /*事件的回调函数*/
    typedef void (Callback_event)(int, short, void *);
    /*bufferevent的read回调函数*/
    typedef void (Callback_read)(bufferevent *, void *);
    /*bufferevent的write回调函数*/
    typedef Callback_read Callback_write;
    //typedef void *Callback_write(bufferevent *,void *);
    /*bufferevent的error回调函数*/
    typedef void (Callback_error)(bufferevent *, short, void *);

public:
    CLibevent();
    ~CLibevent();
    /*
     * 函数功能：将要监听的事件添加进事件管理器中
     * 参数：要监听的文件描述符，事件标志，触发的函数，传给触发函数的参数
     */
    bool add_event(int fd, int flags,Callback_event func,void *args);
    /*
     * 函数功能：将带缓冲功能的事件添加进事件管理器中
     */
    bool add_bufferevent(int fd, int flags,
            Callback_read cb_read, Callback_write cb_write,
            Callback_error cb_error, void *args);
    /*
     * 函数功能：事件循环
     */
    void dispatch();
    /*
     * 函数功能：返回事件管理器base
     */
    event_base *get_event_base() const;
private:
    event_base *base;/*事件管理器*/

};
#endif
