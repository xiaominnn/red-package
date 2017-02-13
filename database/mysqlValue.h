/*
 * 此文件为项目数据库所用到的一些常量定义
 */
#ifndef MYSQL_VALUE_H
#define MYSQL_VALUE_H

/*
 * IP地址常量
 */
const char *SERV_IP_ADRESS = "127.0.0.1";            /*服务器端IP地址*/
const char *MEMACHED_IP_ADRESS = "127.0.0.1";        /*memcachedIP地址*/
const char *mysql_IP_ADRESS = "127.0.0.1";           /*mysql数据库IP地址*/

/*
 * 端口常量
 */
const int SERV_PORT = 8000;                          /*服务器端口号*/
const int MEMCACHED_PORT = 11211;                    /*memcached端口号*/
const int MY_MYSQL_PORT = 3306;                         /*mysql端口号*/

/*
 * mysql数据库用户名,密码
 */
const char *MYSQL_USER = "root";
const char *MYSQL_PASSWORD = "111111";
#endif
