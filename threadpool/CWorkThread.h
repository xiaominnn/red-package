#ifndef CWORK_THREAD_H
#define CWORK_THREAD_H
#include "CThread.h"
//#include "CThreadPool.h"
#include "CJob.h"
#include <cstdio>
/*
 * 工作线程的定义
 */
class CThreadPool;

class CWorkThread : public CThread
{
public:
    CWorkThread():job(NULL),jobdata(NULL),pool(NULL) { }
    virtual ~CWorkThread();
    void run();
    void setJob(CJob *new_job, void *new_jobdata);
    void setCThreadPool(CThreadPool *new_pool);
    CJob * getJob() { return job; }
    CThreadPool * getCThreadPool() { return pool; }
private:
    CJob *job;
    void *jobdata;
    CThreadPool *pool;
};
#endif
