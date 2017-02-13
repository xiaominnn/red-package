/*
 * 数据访问层DataAccess成员函数实现：继承自CMysql类
 * 作用：mysql数据库之上的数据访问层，实现访问数据与具体的数据库的分离
 */

#include "DataAccess.h"

std::stringstream mystream;/*用于int转换为字符串*/

DataAccess::DataAccess(std::string ip, unsigned short port, 
        std::string user, std::string password, std::string database_name)
        :CMysql(ip,port,user,password,database_name)
{
}
 /*
  * 函数功能：插入登陆表
  * 函数参数：用户id，密码
  * 备注：静态函数不能调用非静态函数成员
  */
bool DataAccess::insert_login(unsigned int user_id,std::string password)
{
    std::string temp;/*用于存储int转化为的字符串*/
    mystream << user_id;
   mystream  >> temp;

    /*插入login登陆表*/
    std::string insert_login_statement = std::string("insert into login(id,password) values(\'") + temp + "\',\'"+ password + "\');";
    if(!this->update(insert_login_statement))
        /*插入失败*/
    {
        return false;
    }
    return true;
}
/*
 * 函数功能：删除用户
 * 函数参数：用户ID
 * 返回值：成功则返回true，失败则返回false
 */
bool DataAccess::delete_login(unsigned int user_id)
{
    std::string temp;/*用于存储int转化为的字符串*/
    mystream << user_id;
    mystream >> temp;
    /*删除用户登陆表*/
    std::string delete_login_statement = std::string("delete from login where id=\'") + temp + "\';";
    if(!this->update(delete_login_statement))
        /*删除失败*/
    {
        return false;
    }
    return true;
}
/*
 * 函数功能：用户匹配(登陆)
 * 函数参数：用户ID，密码
 * 返回值：成功则返回true，失败则返回false
 */
bool DataAccess::match_login(unsigned int id, std::string password)
{
    std::string temp;/*用于存储int转化为的字符串*/
    mystream << id;
    mystream >> temp;
    /*查询是否有该用户*/
    std::string match_login_statement = std::string("select * from login where id=\'") + temp + "\' and password=\'" + password + "\';";
    if(this->query(match_login_statement) != "")
        /*存在该用户*/
    {
        return true;
    }
    return false;
}
/*
 * 函数功能：添加好友
 * 函数参数：用户ID，被添加的好友
 */
bool DataAccess::insert_friend(unsigned int user_id,unsigned int target_user_id)
{
    std::string string_userid,string_targetid;/*用于存储int转化为的字符串*/
    mystream << id;
    mystream >> temp;
    std::string insert_user_relationship = "insert into uesr_relationship(user_id,target_user_id) values(" + user_id + "," + target_user_id + ");";
    if(!update(insert_user_relationship))
    {
        return false;
    }
    return true;
}
/*
 * 函数功能：删除好友
 * 函数参数：用户ID，被删除的好友
 */
bool DataAccess::delete_friend(unsigned int user_id,unsigned int target_user_id)
{
    std::string delete_user_relationship = "delete from user_relationship where user_id=" + user_id + ",target_user_id=" + target_user_id + ";";
    if(!update(delete_user_relationship))
    {
        return false;
    }
    return true;
}
/*
 * 函数功能：匹配好友关系
 * 函数参数：用户ID，被匹配的好友
 */
bool DataAccess::match_friend(unsigned int user_id,unsigned int target_user_id)
{
    std::string is_friend_statement = "select * from user_relationship where user_id=" + user_id + ",target_user_id=" + target_user_id + ";";
    if(query(is_friend_statement) != NULL)
        /*存在好友关系*/
    {
        return true;
    }
    return false;
}
