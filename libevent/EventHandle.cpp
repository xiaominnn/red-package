/*
 * 事件处理类成员函数实现
 */

/*
 * 函数功能：接受函数处理
 */
void RPEventHandle::do_accept(int listener, short event, void *args)
{
    Args *argument = (Args * )args;/*框架组件指针集合*/
    CLibevent *clibevent = argument->get_clibevent();/*libevent封装类*/

    sockaddr_in client;
    socklen_t len_client = sizeof(sin);
    evutil_socket_t fd = accept(listener, (struct sockaddr *)&client, &len_client);
    if (fd < 0) 
    {
        std::cout << "accept error!" << std::endl;
        return;
    }

    std::cout << "ACCEPT: fd = " << fd << std::endl;

    int accept_event_flags = EV_READ | EV_WRITE | EV_PERSIST;
    clibevent->add_bufferevent(fd, accept_event_flags, read_cb, NULL, error_cb, args);
}

/*
 * 函数功能：事件可读处理函数
 */
void RPEventHandle::do_read(bufferevent *bev, void *args)
{
    Args *argument = (Args * )args;/*框架组件指针集合*/
    CThreadManage *thread_manage = args->get_thread_manage();/*线程池管理器*/
    CLibevent *clibevent = argument->get_clibevent();/*libevent封装类*/
#define MAX_CHAR  256
    char message[MAX_CHAR+1];/*存放消息的缓冲区*/
    int num_char = 0;/*消息的字符数*/
    evutil_socket_t fd = bufferevent_getfd(bev);

    while (num_char = bufferevent_read(bev, message, MAX_LINE), num_char > 0)
    {
        message[n] = '\0';
        std::cout << "fd = " << fd << ",read message:" << message << std::endl;
        //bufferevent_write(bev, message, num_char);
    }
    /*设置传递参数中的消息参数指针*/
    std::string *string_message = new std::string(message);/*必须用new开辟，否则对象生命周期到的时候，消息也随着消亡*/
    argument->set_message(string_message);
    /*调用线程池处理消息*/
    thread_manage->run(, args);
}
/*
 * 函数功能：事件可写处理函数
 */
void RPEventHandle::do_write(bufferevent *bev, void *args)
{
}
/*
 * 函数功能：事件异常理函数
 */
void RPEventHandle::do_error(bufferevent *bev, short event, void *args)
{
    evutil_socket_t fd = bufferevent_getfd(bev);
    std::cout << "fd = " << fd << std::endl;
    if (event & BEV_EVENT_TIMEOUT) 
        //if bufferevent_set_timeouts() called
    {
        std::cout << "Time out!" << std::endl;
    }
    else if (event & BEV_EVENT_EOF) 
    {
        std::cout << "connection closed" << std::endl;
    }
    else if (event & BEV_EVENT_ERROR) 
    {
        std::cout << "some other error" << std::endl;
    }
    bufferevent_free(bev);
}
