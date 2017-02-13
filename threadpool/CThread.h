#ifndef CTHREAD_H
#define CTHREAD_H
#include<pthread.h>
#include<unistd.h>
#include<iostream>
#include"locker.h"
/*
 *对线程的类封装
 */
class CThread
{
public:
    CThread(bool new_detach = true, bool new_suspend = true);
    virtual ~CThread();
    virtual void run() = 0;//创建线程运行的函数
    bool create(CThread *new_thread);//创建线程
    bool join();
    void exit();
    pthread_t getID() { return id; }
    bool getDetach() { return detach; }
   // void setDetach(bool new_detach);
    bool getSuspend() { return suspend; }
    void setSuspend(bool new_suspend) { suspend = new_suspend; }
protected:
    static void *threadRoutine(void *);//为了支持类的多线程必须增加一个这样的参数
private:
    pthread_t id;
    pthread_attr_t attr;
    bool detach;
    bool suspend;
};
#endif
