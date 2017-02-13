#include "CThreadPool.h"
using namespace std;
//public method
//const unsigned int IDLE_LOW = 50;
//const unsigned int IDLE_HIGH = 500;
//const unsigned int IDLE_STD = (IDLE_LOW + IDLE_HIGH)/2;
CThreadPool::CThreadPool(unsigned int num)
    :maxNum(THREAD_MAXNUM),idleLow(IDLE_LOW),idleHigh(IDLE_HIGH),idleStd(IDLE_STD)
     /*
      * 创建num个线程的线程池，将每个线程加入空闲链表，并设置其线程池为
      * 该线程池，线程进入睡眠状态，等待其CJob不为空，然后运行
      */
{
    std::cout << "cd CThreadPool !" << std::endl;
    if(num > maxNum)
    {
        std::cout << "Create thread num is over max number!" << std::endl;
        exit(1);
    }
    for(unsigned int i = 0;i < num; ++i)
    {
        std::cout << "ready create CWorkThread!" <<std::endl;
        CWorkThread * cworkThread = new CWorkThread();
        appendToIdleList(cworkThread);
        cworkThread->setCThreadPool(this);
        //cworkThread->run();
    }
}
CThreadPool::~CThreadPool()
{
    terminteAll();
}
void CThreadPool::run(CJob *job, void * jobdata)
{
    if(job == NULL)
    {
        std::cout << "Job is no exist!" << std::endl;
        return;
    }

    if(CThreadPool::getBusyNum() == maxNum)
    {
        idleCond.wait();
    }
    if(CThreadPool::getIdleNum() < idleLow)/*空闲线程小于最低值*/
    {
        if(busyList.size() + idleStd < maxNum)/*若空闲线程增大到标准值，
                                               *总线程仍小于线程最大值
                                               */
        {
            createIdleThread(idleStd - idleList.size());
        }
        else
        {
            createIdleThread(maxNum - busyList.size() - idleList.size());
        }
    }
    /*获得空闲线程*/
    CWorkThread *cworkThread = getIdleThread();
    if(cworkThread != NULL)
    {
        moveToBusyList(cworkThread);
        cworkThread->setCThreadPool(this);
        job->setWorkThread((CThread *)cworkThread);
        std::cout << "Job is set to thread:" << ((CThread *)cworkThread)->getID()
            << std::endl;
        cworkThread->setJob(job, jobdata);/*将任务加入空闲线程中运行*/
    }
}
void CThreadPool::terminteAll()
    /*
     * 终止所有的线程，包括正在执行任务的线程及空闲线程
     */
{
    busyLocker.lock();
    unsigned int num = busyList.size();
    for(unsigned int i = 0;i < num;++i)
    {
        CWorkThread *cworkThread = busyList.front();
        ((CThread *)cworkThread)->exit();
        busyList.pop_front();
    }
    busyLocker.unlock();

    idleLocker.lock();
    num = idleList.size();
    for(unsigned int i = 0;i < num;++i)
    {
        CWorkThread *cworkThread = idleList.front();
        ((CThread *)cworkThread)->exit();
        idleList.pop_front();
    }
    idleLocker.unlock();
}

CWorkThread * CThreadPool::getIdleThread()
{
    while(idleList.size() == 0)
    {
        idleCond.wait();
    }

    /*空闲链表是临界资源*/
    idleLocker.lock();
    if(idleList.size() > 0)
    {
        CWorkThread *cworkThread = idleList.front();
        std::cout << "Get idle thread:" << ((CThread *)cworkThread)->getID() << std::endl;
        idleLocker.unlock();
        return cworkThread;
    }
    idleLocker.unlock();
    return NULL;
}
void CThreadPool::appendToIdleList(CWorkThread *new_thread)
{
    idleLocker.lock();
    idleList.push_back(new_thread);
    idleLocker.unlock();
}
void CThreadPool::moveToBusyList(CWorkThread *idleThread)
{
    //从空闲链表中删除，如果未找到，则直接返回
    idleLocker.lock();
    list<CWorkThread *>::iterator pos;
    pos = find(idleList.begin(), idleList.end(), idleThread);
    if(pos != idleList.end())
    {
        idleList.erase(pos);
    }
    else
    {
        idleLocker.unlock();
        return;
    }
    idleLocker.unlock();
    //插入到busy链表中
    busyLocker.lock();
    busyList.push_back(idleThread);
    busyLocker.unlock();
}
void CThreadPool::moveToIdleList(CWorkThread *busyThread)
{
    //从busy闲链表中删除，如果未找到，则直接返回
    busyLocker.lock();
    list<CWorkThread *>::iterator pos;
    pos = find(busyList.begin(), busyList.end(), busyThread);
    if(pos != busyList.end())
    {
        busyList.erase(pos);
    }
    else
    {
        busyLocker.unlock();
        return;
    }
    busyLocker.unlock();
    //插入到busy链表中
    idleLocker.lock();
    idleList.push_back(busyThread);
    idleLocker.unlock();

    idleCond.signal();
}
void CThreadPool::createIdleThread(int num)
{
    unsigned int currentTNum = busyList.size() + idleList.size();/*当前线程数量*/
    if(num <=0 || currentTNum + num > maxNum)//创建线程超出最大数量或者越界
    {
        std::cout << "Create idle thread error." << std::endl;
        return;
    }
    for(int i = 0;i < num;++i)
    {
        CWorkThread *cworkThread = new CWorkThread();
        cworkThread->setCThreadPool(this);
        appendToIdleList(cworkThread);
        cworkThread->run();
    }
}
void CThreadPool::deleteIdleThread(int num)
{
    if(num <=0 || idleList.size() - num > 0)//删除线程数越界或者超过空闲线程个数
    {
        std::cout << "Delete idle thread error." << std::endl;
        return;
    }

    idleLocker.lock();
    for(int i = 0;i < num;++i)
    {
        CWorkThread *cworkThread;//用于存储删除的线程
        if(idleList.size() > 0)
        {
            cworkThread = idleList.front();
            std::cout << "Get idle thread:" << ((CThread *)cworkThread)->getID()
                << std::endl;
        }

        list<CWorkThread *>::iterator pos;
        pos = find(idleList.begin(), idleList.end() ,cworkThread);
        if(pos != idleList.end())
        {
            idleList.erase(pos);
            std::cout << "The idle thread num:" << idleList.size() << std::endl;
        }
    }
    idleLocker.unlock();
}
