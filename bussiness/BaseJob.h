/*
 * 对消息进行处理的类
 */
#ifndef BASE_JOB_H
#define BASE_JOB_H

#include "../threadpool/CThreadManage.h"
#include "../value.Message.h"

/*
 * 基本消息处理类
 * 仅仅对消息进行解析
 */
class BaseJob : public CJob
{
public:
    /*
     * 注册消息处理函数：message_register=1(消息类型值)
     */
    bool register_message(std::string *message_content);
    /*
     * 登陆消息处理函数：message_login=2(消息类型值)
     */
    bool login_message(std::string *message_content);
    /*
     * 消息处理运行函数
     */
    virtual void run(void *jobdata);
private:
    /*
     * 对消息进行解析，解析成json类型
     */
    static bool prase_message_json(void *jobdata,const Json::Value &json_message);
};
#endif
