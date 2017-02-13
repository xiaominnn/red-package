/*
 * mysql访问层
 */
#ifndef MYSQL_H
#define MYSQL_H

#include <mysql/mysql.h>
#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>

class CMysql
{
public:
    /*
     * 函数功能：mysql访问层构造函数，连接mysql数据库
     * 参数：mysql数据库的iP，端口，用户名，密码，访问的数据库名字
     */
    CMysql(std::string ip, unsigned short port, std::string user, std::string password, std::string datebase_name);
    /*
     * 函数功能：关闭与mysql的连接，释放所开辟的内存
     */
    ~CMysql();
    /*
     * 函数功能：对数据库进行查询
     */
    std::string query(std::string statement);
    /*
     * 函数功能：对数据库执行更新操作：包括插入，删除，修改
     */
    bool update(std::string statement);
private:
    MYSQL *mysql_con;         /*数据库连接句柄*/
    MYSQL_RES *mysql_res;     /*结果集*/
    MYSQL_ROW mysql_row;     /*行结构*/
    MYSQL_FIELD *mysql_field; /*属性结构*/

};
#endif
