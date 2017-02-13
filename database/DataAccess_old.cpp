/*
 * 数据访问层DataAccess成员函数实现：继承自CMysql类
 * 作用：mysql数据库之上的数据访问层，实现访问数据与具体的数据库的分离
 */

#include "DataAccess.h"
DataAccess::DataAccess(std::string ip, unsigned short port, 
        std::string user, std::string password, std::string datebase_name)
        :CMysql(ip,port,user,password,datebase_name)
{
}
 /*
  * 函数功能：插入登陆表
  * 函数参数：用户id，密码
  */
bool DataAccess::insert_login(unsigned int user_id,std::string password)
{
    /*插入login登陆表*/
    std::string insert_login_statement = "insert into login(id,password) values(\'" + user_id + "\',\'"+ password + "\');";
    if(!update(insert_login_statement))
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
bool DataAcess::delete_login(unsigned int user_id)
{
    /*删除用户登陆表*/
    std::string delete_login_statement = "delete from login where id='" + user_id + "';";
    if(!update(delete_login_statement))
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
bool DateAccess::match_login(unsigned int id, std::string password)
{
    /*查询是否有该用户*/
    std::string match_login_statement = "select * from login where id='" + id + "' and password='" + password + "';";
    if(query(match_login_statement) != NULL)
        /*存在该用户*/
    {
        return true;
    }
    return false;
}

/*
 * 函数功能：插入用户信息
 */
bool DataAccess::insert_userinfo(unsigned int user_id, std::string user_name, unsigned short age, std::string sex, std::string birthday, std::string email, std::string cellphone)
{
    /*插入用户信息*/
    std::string insert_userinfo_statement = "insert into userinfo(id,name,sex,birthday,email,cellphone) values(" + user_id + ",'" + user_name + "'," + age + ",'" + sex + "','" + birthday + "','" + email + "','" + cellphone + "');";
    if(!update(insert_userinfo_statement))
        /*插入失败*/
    {
        return false;
    }
    return true;
}
/*
 * 函数功能：删除用户信息表
 */
bool DataAccess::delete_userinfo(unsigned int user_id)
{
    std::string delete_userinfo_statement = "delete from userinfo where id=" + user_id + ");";
    if(!update(delete_userinfo_statement))
    {
        return false;
    }
    return true;
}
/*
 * 函数功能：通过用户id查询用户信息表
 */
std::string DataAccess::query_userinfo(unsigned int user_id)
{
    std::string query_userinfo_statement = "select * from userinfo where id=" + user_id + ";";
    return query(query_userinfo_statement);
}
/*
 * 函数功能：设置新的用户名字
 */
bool DataAccess::set_user_name(unsigned int user_id, std::string new_name)
{
    /*修改userinfo的用户名字*/
    std::string set_statement = "update userinfo set name='" + new_name
        + "where id=" user_id + ";";
    if(!update(set_statement))
    {
        return false;
    }
    return true;
}
/*
 * 函数功能：设置新的用户年龄
 */
bool DataAccess::set_user_age(unsigned int user_id, unsigned short new_age)
{
    /*修改userinfo的用户年龄*/
    std::string set_statement = "update userinfo set age=" + new_age
        + "where id=" user_id + ";";
    if(!update(set_statement))
    {
        return false;
    }
    return true;
}
/*
 * 函数功能：设置新的用户性别
 */
bool DataAccess::set_user_sex(unsigned int user_id, std::string new_sex)
{
    /*修改userinfo的用户性别*/
    std::string set_statement = "update userinfo set sex='" + new_sex
        + "where id=" user_id + ";";
    if(!update(set_statement))
    {
        return false;
    }
    return true;
}
/*
 * 函数功能：设置新的用户生日
 */
bool DataAccess::set_user_birth(unsigned int user_id, std::string new_birth)
{
    /*修改userinfo的用户生日*/
    std::string set_statement = "update userinfo set birthday='" + new_birth + "where id=" user_id + ";";
    if(!update(set_statement))
    {
        return false;
    }
    return true;
}
/*
 * 函数功能：设置新的用户email
 */
bool DataAccess::set_user_email(unsigned int user_id, std::string new_email)
{
    /*修改userinfo的用户邮箱*/
    std::string set_statement = "update userinfo set email='" + new_email + "';";
        + "where id=" user_id + ";";
    if(!update(set_statement))
    {
        return false;
    }
    return true;
}
/*
 * 函数功能：设置新的用户电话
 */
bool DataAccess::set_user_cellphone(unsigned int user_id, std::string new_cellphone)
{
    /*修改userinfo的用户电话*/
    std::string set_statement = "update userinfo set cellphone='
        + "where id=" user_id + ";";
    if(!update(set_statement))
    {
        return false;
    }
    return true;
}
/*
 * 函数功能：添加好友
 * 函数参数：用户ID，被添加的好友
 */
bool DataAccess::insert_friend(unsigned int user_id,unsigned int target_user_id)
{
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

/*
 * 函数功能：插入群组(创建)
 * 函数参数：群组id，群名字，管理员用户id，群公告
 * 返回值：若成功，返回群ID；失败，则返回-1
 */
unsigned int DataAccess::insert_group(unsigned int group_id, std::string group_name, int admin_id, std::string announcement)
{
    std::string insert_groupinfo_statement = "insert into groupinfo(id,group_name,admin_id,announcement) values(" + group_id + ",'" + group_name + "','" + admin_id + ",'" + announcement + "');";
    if(!update(insert_groupinfo_statement))
    {
        return false;
    }
    return true;
}
/*
 * 函数功能：删除群组
 * 函数参数：群ID
 * 返回值：若成功，返回true；失败，则返回false
 */
bool DataAccess::delete_group(int group_id)
{
    std::string delete_groupinfo_statement = "delete from groupinfo where id=" + group_id + ";";
    if(!update(delete_groupinfo_statement))
    {
        return false;
    }
    return true;
}
/*
 * 函数功能：修改群公告
 */
bool DataAccess::set_group_announce(unsigned int group_id, std::string new_announcement)
{
    std::string set_group_statement = "update groupinfo set announcement="
        + announcement + "where id=" + group_id + ";";
    if(!undate(set_group_statement))
    {
        return false;
    }
    return true;
}
/*
 * 函数功能：是否是群管理员
 */
bool DataAccess::is_group_admin(int group_id, int admin_id)
{
    std::string query_statement = "select * from groupinfo where id=" 
        + group_id + " and admin_id=" + admin_id + ";";
    if(query(query_statement) != NULL)
    {
        return true;
    }
    return false;
}
/*
 * 函数功能：是否是群成员
 */
bool DataAccess::is_group_member(int group_id, int user_id)
{
    std::string query_statement = "select * from group_relationship where"
        + "id=" + group_id + ",user_id=" + user_id + ";";
    if(query(query_statement) != NULL)
    {
        return true;
    }
    return false;
}
/*
 * 函数功能：进群
 */
bool DataAccess::join_group(int user_id, int group_id)
{
    std::string join_group_statement = "insert into group_relationship(id,group_id,user_id) values(" + user_id + "," + group_id + ");";
    if(!update(join_group_statement))
    {
        return false;
    }
    return true;
}
/*
 * 函数功能：退群
 */
bool DataAccess::quit_group(int user_id, int group_id)
{
    std::string quit_group_statement = "delete from group_relationship"
        + "where group_id=" + group_id + ",user_id=" + user_id + ";";
    if(!update(quite_group_statement))
    {
        return false;
    }
    return true;
}
/*
 * 函数功能：创建红包
 * 函数参数：领取/发送红包id，领取/发送时间，红包类型
 * 函数参数：红包被分的数量，金额，发送红包id
 */
bool DataAccess::insert_red_package(unsigned int user_id, std::string datetime, unsigned short type, unsigned int num, float money, unsigned int send_id)
{
    std::string insert_statement = "insert into red_package"
        + "(user_id,red_package_time,type,num,money,send_id)"
        + " values(" + user_id + ",'" + datetime + "',"
        + type + "," + num + "," + money + "," + send_id + ");";
    if(!update(insert_statement))
    {
        return false;
    }
    return true;
}
/*
 * 函数功能：删除红包
 * 函数参数：用户id，创建时间
 */
bool DataAccess::delete_red_package(unsigned int user_id, std::string datetime)
{
    std::string delete_statement = "delete from red_package where user_id="
        + user_id + ",datetime='" + datetime + "';";
    if(!update(delete_statement))
    {
        return false;
    }
    return true;
}
