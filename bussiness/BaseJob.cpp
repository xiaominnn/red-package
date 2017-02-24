/*
 * BaseJob类的成员函数实现
 */

#include "BaseJob.h"

/*
 * 对消息进行解析，解析出消息类型
 */
bool BaseJob::prase_message(void *jobdata)
/*
 * 注册消息处理函数：message_register=1(消息类型值)
 */
bool BaseJob::register_message(void *jobdata)
{
    Arg *argument = (Arg *)jobdata;/*框架组合参数指针*/
    std::string *message_content = argument->get_message();/*消息*/
    Json::Reader reader;
    Json::Value json_message;
    /*解析string字符串为json对象*/
    if(!reader.parse(*message_content, json_message))
        /*解析出错*/
    {
        std::cerr << "parse string to json object failed!" << std::endl;
        return;
    }
}
/*
 * 登陆消息处理函数：message_login=2(消息类型值)
 */
bool BaseJob::login_message(std::string *message_content);
/*
 * 消息处理运行函数
 */
void BaseJob::run(void *jobdata)
{
    Arg *argument = (Arg *)jobdata;/*框架组合参数指针*/
    std::string *message_content = argument->get_message();/*消息*/
    Json::Reader reader;
    Json::Value json_message;
    /*解析string字符串为json对象*/
    if(!reader.parse(*message_content, json_message))
        /*解析出错*/
    {
        std::cerr << "parse string to json object failed!" << std::endl;
        return;
    }
    MessageType message_type = json_message["type"].asInt();/*消息类型*/
    switch(message_type)
    {
    case message_register:
        if(!register_message(jobdata))
            /*注册消息失败*/
        {
            std::cerr << "register message failed!" << std::endl              return;
        }
        break;
    case message_chat:
        if(!chat_message(jobdata))
            /*处理聊天消息失败*/
        {
            std::cerr << "handle chat message failed!" << std::endl;
            return;
        }
        break;
    }

}
