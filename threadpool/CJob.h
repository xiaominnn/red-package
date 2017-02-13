#ifndef CJOB_H
#define CJOB_H
#include"CThread.h"
#include<string>
using namespace std;
/*
 *任务类的定义
 */
class CJob
{
public:
    CJob(int no = 0,string name = ""):jobNo(no),jobName(name) { }
    virtual ~CJob() { }
    string getJobName() { return jobName; }
    void setJobName(string new_jobName) { jobName = new_jobName; }
    int getJobNo() { return jobNo; }
    void setJobNo(int new_jobNo) { jobNo = new_jobNo; }
    CThread *getWorkThread() { return workThread; }
    void setWorkThread(CThread *new_workThread) { workThread = new_workThread; }

    virtual void run(void *jobdata) = 0;
private:
    int jobNo;//工作编号
    string jobName;//工作名字
    CThread *workThread;
};
#endif
