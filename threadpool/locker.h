#ifndef LOCKER_H
#define LOCKER_H
//synchronization

#include<exception>
#include<pthread.h>
#include<semaphore.h>

//semaphore
class sem
{
public:
    sem(int value = 0)//value of init
    {
        if(sem_init(&m_sem, 0, value) != 0)
        {
            throw std::exception();
        }
    }
    ~sem()
    {
        if(sem_destroy(&m_sem) != 0)
        {
            throw std::exception();
        }
    }
    bool wait()
    {
        return sem_wait(&m_sem) == 0;
    }
    bool post()
    {
        return sem_post(&m_sem) == 0;
    }
private:
    sem_t m_sem;
};
//mutex locker
class locker
{
public:
    locker()
    {
        if(pthread_mutex_init(&m_mutex, NULL) != 0)
        {
            throw std::exception();
        }
    }
    ~locker()
    {
        if(pthread_mutex_destroy(&m_mutex) != 0)
        {
            throw std::exception();
        }
    }
    //获取互斥锁
    bool lock()
    {
        return pthread_mutex_lock(&m_mutex) == 0;
    }
    //释放互斥锁
    bool unlock()
    {
        return pthread_mutex_unlock(&m_mutex) == 0;
    }
private:
    pthread_mutex_t m_mutex;
};
//封装条件的类
class cond
{
public:
    //创建并初始化条件变量
    cond()
    {
        if(pthread_mutex_init(&m_mutex, NULL) != 0)
        {
            throw std::exception();
        }
        if(pthread_cond_init(&m_cond, NULL) != 0)
        {
            if(pthread_mutex_destroy(&m_mutex) != 0)
            {
                throw std::exception();
            }
            throw std::exception();
        }
    }
    ~cond()
    {
        if(pthread_mutex_destroy(&m_mutex) != 0)
        {
            throw std::exception();
        }
        if(pthread_cond_destroy(&m_cond) != 0)
        {
            throw std::exception();
        }
    }
    bool wait()
    {
        pthread_mutex_lock(&m_mutex);
        int ret = pthread_cond_wait(&m_cond, &m_mutex);
        pthread_mutex_unlock(&m_mutex);
        return ret == 0;
    }
    bool signal()
    {
        return pthread_cond_signal(&m_cond) == 0;
    }
private:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
};

#endif
