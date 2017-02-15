#include "CMysql.h"
#include <json/json.h>
#include <stdlib.h>

/*
 * 函数功能：mysql访问层构造函数，连接mysql数据库
 * 参数：mysql数据库的iP，端口，用户名，密码，访问的数据库名字
 */
CMysql::CMysql(std::string ip, unsigned short port, std::string user, std::string password, std::string database_name):mysql_con(NULL),mysql_res(NULL),mysql_row(NULL)
{
    /*初始化*/
    mysql_con = mysql_init(NULL);
    if(mysql_con == NULL)
    {
        std::cout << "mysql init error!" << std::endl;
        exit(-1);
    }
    /*连接指定的数据库*/
    if(!mysql_real_connect(mysql_con, ip.c_str(), user.c_str(), password.c_str(), database_name.c_str(), port, NULL, 0))
    {
        std::cerr << mysql_error(mysql_con) << std::endl;
        exit(-1);
    }
}
/*
 * 函数功能：关闭与mysql的连接，释放所开辟的内存
 */
CMysql::~CMysql()
{
    if(mysql_res != NULL)
    {
        mysql_free_result(mysql_res);
    }
    if(mysql_con != NULL)
    {
        mysql_close(mysql_con);
    }
}
/*
 * 函数功能：对数据库进行查询
 */
std::string CMysql::query(std::string statement)
{
    Json::FastWriter writer;/*用于将json变量反序列化为字符串*/
    Json::Value res_query;/*存储查询结果*/

    int num_field = 0;/*属性列的数量*/
    int res = mysql_real_query(mysql_con, statement.c_str(), statement.length());
    if(res != 0)
    {
        std::cerr << mysql_error(mysql_con) << std::endl;
        exit(-1);
    }
    mysql_res = mysql_store_result(mysql_con);
    if(mysql_res == NULL)
    {
        std::cerr << "mysql_restore_result():" << mysql_error(mysql_con) << std::endl;
        exit(-1);
    }

    num_field = mysql_num_fields(mysql_res);/*获取结果集中属性列的数量*/
    mysql_field = mysql_fetch_fields(mysql_res);/*获取结果集中属性名字*/

    int num_row = mysql_num_rows(mysql_res);/*获取结果集中的行数*/
    if(!num_row)
        /*结果集为空,返回空字符串*/
    {
        return "";
    }

    /*将查询结果以json数组格式储存*/
    while(mysql_row = mysql_fetch_row(mysql_res))
        /*获取每一行结果集*/
    {
        Json::Value item;     /*临时保存每一行查询结果*/
        for(int i = 0;i < num_field;++i)
        {
            char *field_name = mysql_field[i].name;/*属性列名字*/
            item[field_name] = mysql_row[i];       /*该属性值*/
        }
        res_query.append(item);
    }
    /*
     * 将Json对象反序列化为字符串返回
     * 将null json对象写入字符串，结果为"null\n"
     */
    return writer.write(res_query);
}
/*
 * 函数功能：对数据库执行更新操作：包括插入，删除，修改
 * 返回值：成功返回true，失败返回false
 */
bool CMysql::update(std::string statement)
{
    /*执行更新操作*/
    int res = mysql_real_query(mysql_con, statement.c_str(), statement.length());
    if(res != 0)
        /*如果失败，返回false*/
    {
        std::cerr << "mysql_real_query():" << mysql_error(mysql_con) << std::endl;
        return false;
    }
    /*操作成功*/
    return true;
}
