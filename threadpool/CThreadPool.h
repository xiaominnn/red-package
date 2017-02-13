#ifndef CTHREAD_POOL_H
#define CTHREAD_POOL_H

#include"CWorkThread.h"
#include"CJob.h"
#include<list>
#include<algorithm>
using namespace std;

//线程的个数的几个常量
const unsigned int THREAD_MAXNUM = 10;//线程的最大个数
const unsigned int IDLE_LOW = THREAD_MAXNUM/20;//空闲线程的最小个数
const unsigned int IDLE_HIGH = THREAD_MAXNUM/2;//空闲线程的最大个数
const unsigned int IDLE_STD = (IDLE_LOW + IDLE_HIGH)/2;//空闲现程的标准个数

class CThreadPool
{
    friend class CWorkThread;//友元类，使CWorkThread可以访问其protected成员
public:
    CThreadPool(unsigned int num = IDLE_STD);
    virtual ~CThreadPool();
    void setMaxNum(unsigned int new_maxNum);
    void setIdleLow(int new_idleLow);
    void setIdleHigh(int new_idleHigh);
    void run(CJob *job, void * jobdata);
    void terminteAll();

    unsigned int getMaxNum() { return maxNum; }
    unsigned int getIdleLow() { return idleLow; }
    unsigned int getIdleHigh() { return idleHigh; }
    unsigned int getIdleStd() { return idleStd; }
    unsigned int getIdleNum() { return idleList.size(); }
    unsigned int getBusyNum() { return busyList.size(); }
protected:
    CWorkThread * getIdleThread();
    void appendToIdleList(CWorkThread *new_thread);
    void moveToBusyList(CWorkThread *idleThread);
    void moveToIdleList(CWorkThread *busyThread);
    void createIdleThread(int num);
    void deleteIdleThread(int num);
private:
    cond idleCond;//idleCond is used to sync idle thread list
    locker busyLocker;//locker used in busy thread list
    locker idleLocker;//locker used in idle thread list
    list<CWorkThread *> busyList;//busy thread list
    list<CWorkThread *> idleList;//idle thread list
private:
    unsigned int maxNum;   //the max thread num that can created at the same time
    unsigned int idleLow; //the min num of idle thread
    unsigned int idleHigh;//the max num of idle thread
    unsigned int idleStd;  /*
                            *the standard idle that is used to recover
                            *when idle num is below idleLow or is higher
                            *than idleHigh.
                            */
};
#endif
