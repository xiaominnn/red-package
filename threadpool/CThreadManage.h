#ifndef CTHREAD_MANAGE_H
#define CTHREAD_MANAGE_H

#include "CThreadPool.h"
/*
 * CThreadManage类：用于创建并管理线程池
 */
class CThreadManage
{
public:
    CThreadManage();
    CThreadManage(int num);
    virtual ~CThreadManage();

    void run(CJob *job,void * jobdata);
    void terminateAll();
private:
    CThreadPool *pool;
};
#endif
