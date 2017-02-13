#include "CThreadManage.h"
using namespace std;

class CXJob : public CJob
{
public:
    CXJob() { }
    ~CXJob() { }
    void run(void *jobdata)
    {
        std::cout << "The job comes from CXJOb:" << *((int *)jobdata) << std::endl;
    }
};

class CYJob : public CJob
{
public:
    CYJob() { }
    ~CYJob() { }
    void run(void *jobdata)
    {
        std::cout << "The job comes from CYJOb:" << *((int *)jobdata) << std::endl;
    }
};

int main()
{
    std::cout <<" cd main." << std::endl;
    CThreadManage *manage = new CThreadManage();
    for(int i = 0;i < 5;++i)
    {
        if(i%2 == 0)
        {
            std::cout << "ready create CXJob:" << i << std::endl;
            CXJob *job = new CXJob();
            std::cout << "create CXJob finished!" << std::endl;
            manage->run(job, &i);
        }
        else
        {
            std::cout << "ready create CYJob:" << i << std::endl;
            CYJob *job = new CYJob();
            std::cout << "create CYJob finished!" << std::endl;
            manage->run(job, &i);
        }
    }
    sleep(10);
    return 0;
}
