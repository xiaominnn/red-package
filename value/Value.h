/*
 * 此文件为项目所用到的一些常量定义
 */
#ifndef VALUE_H
#define VALUE_H

#include <string>

/*
 * 程序所用到的一些敞亮定义在该类中
 */
class Value
{
public:
    /*
     * IP地址常量
     */
    static const std::string SERV_IP_ADRESS;            /*服务器端IP地址*/
    static const std::string MEMACHED_IP_ADRESS;        /*memcachedIP地址*/
    static const std::string MYSQL_IP_ADRESS;           /*mysql数据库IP地址*/

    /*
     * 端口常量
     */
    static const int SERV_PORT;                          /*服务器端口号*/
    static const int MEMCACHED_PORT;                    /*memcached端口号*/
    static const int MYSQL_PORT;                         /*mysql端口号*/

    /*
     * mysql数据库用户名,密码,数据库名字
     */
    static const std::string MYSQL_USER;
    static const std::string MYSQL_PASSWORD;
    static const std::string MYSQL_DATABASE_NAME;
};
#endif
