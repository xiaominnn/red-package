#include"CThread.h"
CThread::CThread(bool new_detach, bool new_suspend)
    :detach(new_detach),suspend(new_suspend)
{
    if(create(this) == false)
    {
        exit();
    }
    //CThread::setDetach(detach);
}
CThread::~CThread()
{
}

void *CThread::threadRoutine(void *para)
{
    CThread *cThread = (CThread *)para;
    std::cout <<"before CThread run!" << std::endl;
    cThread->run();
    std::cout << "after CThread run!" << std::endl;
    return NULL;
}
bool CThread::create(CThread *new_thread)//创建线程
{
    std::cout << "create CThread" << std::endl;
    int result = pthread_create(&id, NULL,threadRoutine, new_thread);
    if(result ==0)
    {
        return true;
    }
    return false;
}
bool CThread::join()
{
    if(pthread_join(id, NULL) == 0)
    {
        return true;
    }
    return false;
}
void CThread::exit()
{
    pthread_exit(NULL);
}
//void CThread::setDetach(bool new_detach)
//{
//    detach = new_detach;
//    if(detach)
//    {
//        if(!pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACH))
//        {
//            exit();
//        }
//    }
//    else
//    {
//        if(!pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE))
//        {
//            exit();
//        }
//    }
//}
