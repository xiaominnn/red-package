/*
 * 数据访问层：继承自CMysql类
 * 作用：mysql数据库之上的数据访问层，实现访问数据与具体的数据库的分离
 */
#ifndef DATA_ACCESS_H
#define DATA_ACCESS_H

#include "CMysql.h"

class DataAccess : public CMysql
{
public:
    /*
     * 函数功能：构造函数
     */
    DataAccess(std::string ip, unsigned short port,
            std::string user, std::string password, 
            std::string datebase_name);
    /*
     * 函数功能：插入登陆表
     * 函数参数：用户id，密码
     */
    static bool insert_login(unsigned int user_id, std::string password);
    /*
     * 函数功能：删除登陆用户
     * 函数参数：用户ID
     * 返回值：成功则返回true，失败则返回false
     */
    static bool delete_login(unsigned int user_id);
    /*
     * 函数功能：用户匹配(登陆)
     * 函数参数：用户ID，密码
     * 返回值：成功则返回true，失败则返回false
     */
    static bool match_login(unsigned int user_id, std::string password);

    /*
     * 函数功能：插入用户信息
     */
    static bool insert_userinfo(unsigned int user_id, std::string user_name, unsigned short age, std::string sex, std::string birthday, std::string email, std::string cellphone);
    /*
     * 函数功能：删除用户信息表
     */
    static bool delete_userinfo(unsigned int user_id);
    /*
     * 函数功能：通过用户id查询用户信息表
     */
    static std::string query_userinfo(unsigned int user_id);
    /*
     * 函数功能：设置新的用户名字
     */
    static bool set_user_name(unsigned int user_id, std::string new_name);
    /*
     * 函数功能：设置新的用户年龄
     */
    static bool set_user_age(unsigned int user_id, unsigned short new_age);
    /*
     * 函数功能：设置新的用户性别
     */
    static bool set_user_sex(unsigned int user_id, std::string new_sex);
    /*
     * 函数功能：设置新的用户生日
     */
    static bool set_user_birth(unsigned int user_id, std::string new_birth);
    /*
     * 函数功能：设置新的用户email
     */
    static bool set_user_email(unsigned int user_id, std::string new_email);
    /*
     * 函数功能：设置新的用户电话
     */
    static bool set_user_cellphone(unsigned int user_id, std::string new_cellphone);

    /*
     * 函数功能：添加好友
     * 函数参数：用户ID，被添加的好友
     */
    static bool insert_friend(unsigned int user_id,unsigned int target_user_id);
    /*
     * 函数功能：删除好友
     * 函数参数：用户ID，被删除的好友
     */
    static bool delete_friend(unsigned int user_id,unsigned int target_user_id);
    /*
     * 函数功能：匹配好友关系
     * 函数参数：用户ID，被匹配的好友
     */
    static bool match_friend(unsigned int user_id,unsigned int target_user_id);

    /*
     * 函数功能：插入群组(创建)
     * 函数参数：群ID，群名字，管理员用户id，群公告
     * 返回值：若成功，则返回true；失败，则返回false
     */
    static bool insert_group(unsigned int group_id, std::string group_name, int admin_id, std::string announcement);
    /*
     * 函数功能：删除群组
     * 函数参数：群ID
     * 返回值：若成功，返回true；失败，则返回false
     */
    static bool delete_group(int group_id);
    /*
     * 函数功能：修改群公告
     */
    static bool set_group_announce(unsigned int group_id, std::string new_announcement);
    /*
     * 函数功能：是否是群管理员
     */
    static bool is_group_admin(int group_id, int admin_id);
    /*
     * 函数功能：是否是群成员
     */
    static bool is_group_member(int group_id, int user_id);
    /*
     * 函数功能：进群
     */
    static bool join_group(int user_id, int group_id);
    /*
     * 函数功能：退群
     */
    static bool quit_group(int user_id, int group_id);
    /*
     * 函数功能：创建红包
     * 函数参数：领取/发送红包id，领取/发送时间，红包类型
     * 函数参数：红包被分的数量，金额，发送红包id
     */
    static bool insert_red_package(unsigned int user_id, std::string datetime, unsigned short type, unsigned int num, float money, unsigned int send_id);
    /*
     * 函数功能：删除红包
     * 函数参数：用户id，创建时间
     */
    static bool delete_red_package(unsigned int user_id, std::string datetime);
};
#endif
