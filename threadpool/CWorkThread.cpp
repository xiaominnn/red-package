#include "CWorkThread.h"
#include "CThreadPool.h"
#include <cstring>
CWorkThread::~CWorkThread()
{
    if(job != NULL)
    {
        delete job;
    }
    job = NULL;
    jobdata = NULL;
    pool = NULL;
}

void CWorkThread::run()
{
    std::cout << "CWorkThread is running !" << std::endl;
    for(; true; usleep(10))
    {
        while(job == NULL)//线程空闲时睡眠，直到有任务要处理
        {
            usleep(20);
        }
        job->run(jobdata);
        //任务job完成，线程移到空间链表中
        job->setWorkThread(NULL);
        job = NULL;
        pool->moveToIdleList(this);//要调用CThreadPool的方法，需CThreadPool将其设为友元类
    }
}

void CWorkThread::setJob(CJob *new_job, void *new_jobdata)
{
    job = new_job;
    jobdata = malloc(sizeof(new_jobdata));
    memcpy(jobdata, new_jobdata, sizeof(jobdata));
    cout << "Thread " << this->getID() << "run the job:" << *(int *)jobdata
        <<endl;

}

void CWorkThread::setCThreadPool(CThreadPool *new_pool)
{
    pool = new_pool;
}
