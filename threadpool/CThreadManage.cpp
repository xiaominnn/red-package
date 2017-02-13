#include "CThreadManage.h"
CThreadManage::CThreadManage()
{
    pool = new CThreadPool();
}

CThreadManage::CThreadManage(int num)
{
    pool = new CThreadPool(num);
}

CThreadManage::~CThreadManage()
{
    if(pool != NULL)
    {
        delete pool;
    }
}

void CThreadManage::run(CJob *job, void *jobdata)
{
    pool->run(job, jobdata);
}

void CThreadManage::terminateAll()
{
    pool->terminteAll();
}
