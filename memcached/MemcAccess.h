/*
 * 对memcached的数据访问层
 * 实现对memcached的数据插入，查询，删除等
 */
#ifndef MEMCACHED_DATA_ACCESS_H
#define MEMCACHED_DATA_ACCESS_H

#include "CMemcached.h"
#include <json/json.h>

class MemcAccess : public CMemcached
{
public:
    MemcAccess(std::string ip, unsigned int port);
    /*
     * 函数功能：插入登陆login键值对
     * 参数：用户id，密码
     * 备注：转化为key为login+id，value为密码
     */
    bool insert_login(unsigned int user_id, std::string password, int flags, time_t expiration);
    /*
     * 函数功能：删除登陆记录
     */
    bool delete_login(unsigned int user_id, time_t expiration);
    /*
     * 函数功能：查询登陆记录
     */
    std::string query_login(unsigned int user_id);

    /*
     * 函数功能：插入用户信息userinfo记录
     */
    bool insert_userinfo(unsigned int user_id, std::string user_name, unsigned short age, std::string sex, std::string birthday, std::string email, std::string cellphone, int flags, time_t expiration);
    /*
     * 函数功能：删除用户信息记录
     * 参数：删除的时间expiration
     */
    bool delete_userinfo(unsigned int user_id, time_t expiration);
    /*
     * 函数功能：查询用户信息记录
     */
    std::string query_userinfo(unsigned int user_id);

    /*
     * 函数功能：添加朋友记录
     */
    bool insert_friend(unsigned int user_id, unsigned int target_user_id, int flags, time_t expiration);
    /*
     * 函数功能：删除朋友关系记录
     * 参数：设置朋友关系标志flags，删除后朋友关系存在的时间expiration
     */
    bool delete_friend(unsigned int user_id, unsigned int target_user_id, int flags, time_t expiration);
    /*
     * 函数功能：查询是否存在朋友关系
     */
    bool query_friend(unsigned int user_id, unsigned int target_user_id);

    /*
     * 函数功能：插入群信息groupinfo记录
     */
    bool insert_groupinfo(unsigned int group_id, std::string group_name, unsigned int admin_id, std::string announcement, int flags, time_t expiration);
    /*
     * 函数功能：删除群信息groupinfo记录
     * 参数：删除的时间expiration
     */
    bool delete_groupinfo(unsigned int group_id, time_t expiration);
    /*
     * 函数功能：查询群组信息记录
     * 返回值：以json对象的字符串返回
     */
    std::string query_groupinfo(unsigned int group_id);

    /*
     * 函数功能：添加群成员记录
     */
    bool insert_group_member(unsigned int group_id, unsigned int user_id, int flags, time_t expiration);
    /*
     * 函数功能：删除群成员
     * 若删除后还有群成员，则用flags，expiration重新set该记录
     * 若没有群成员，则删除该条记录，expiration为删除的时间
     */
    bool delete_group_member(unsigned int group_id, unsigned int user_id, int flags, time_t expiration);
    /*
     * 函数功能：是否是群成员
     */
    bool has_group_member(unsigned int group_id, unsigned int user_id);

    /*
     * 函数功能：插入红包记录
     */
    bool insert_red_package(unsigned int user_id, std::string red_package_time, unsigned short type, unsigned int num, int money, unsigned int send_id, int flags, time_t expiration);
    /*
     * 函数功能：删除红包记录
     */
    bool delete_red_package(unsigned int user_id, std::string red_package_time, time_t expiration);
    /*
     * 函数功能：查询红包记录
     */
    std::string query_red_package(unsigned int user_id, std::string red_package_time);

    /*
     * 函数功能：插入余额记录
     */
    bool insert_money(unsigned int user_id, int money, int flags, time_t expiration);
    /*
     * 函数功能：删除余额记录
     */
    bool delete_money(unsigned int user_id, time_t expiration);
    /*
     * 函数功能：查询余额
     * 返回值：查询成功，返回余额；查询失败，返回-1
     */
    int query_money(unsigned int user_id);
};

#endif
