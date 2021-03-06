/*
 * 数据访问层DataAccess成员函数实现：继承自CMysql类
 * 作用：mysql数据库之上的数据访问层，实现访问数据与具体的数据库的分离
 */

#include "DataAccess.h"

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
    std::string string_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream;/*用于int转换为字符串*/
    mystream << user_id;
    mystream >> string_id;

    /*插入login登陆表*/
    std::string insert_login_statement = std::string("insert into login(id,password) values(\'") + string_id + "\',\'"+ password + "\');";
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
    std::string string_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream;/*用于int转换为字符串*/
    mystream << user_id;
    mystream >> string_id;
    /*删除用户登陆表*/
    std::string delete_login_statement = std::string("delete from login where id=\'") + string_id + "\';";
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
    std::string string_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream;/*用于int转换为字符串*/
    mystream << id;
    mystream >> string_id;
    /*查询是否有该用户*/
    std::string match_login_statement = std::string("select * from login where id=\'") + string_id + "\' and password=\'" + password + "\';";
    if(this->query(match_login_statement) != "")
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
    std::string string_id,string_age;/*用于存储int转化为的字符串*/
    std::stringstream mystream1,mystream2;/*用于int转换为字符串*/
    mystream1 << user_id;
    mystream1 >> string_id;
    mystream2 << age;
    mystream2 >> string_age;
    /*插入用户信息*/
    std::string insert_userinfo_statement = std::string("insert into userinfo(id,name,age,sex,birthday,email,cellphone) values(")
        + string_id + ",\'" + user_name + "\'," + string_age + ",\'" + sex + "\',\'" + birthday + "\',\'" + email + "\',\'"
        + cellphone + "\');";
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
    std::string string_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream;/*用于int转换为字符串*/
    mystream << user_id;
    mystream >> string_id;

    std::string delete_userinfo_statement = std::string("delete from userinfo where id=\'") + string_id + "\');";
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
    std::string string_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream;/*用于int转换为字符串*/
    mystream << user_id;
    mystream >> string_id;

    std::string query_userinfo_statement = std::string("select * from userinfo where id=") + string_id + ";";
    return query(query_userinfo_statement);
}
/*
 * 函数功能：设置新的用户名字
 */
bool DataAccess::set_user_name(unsigned int user_id, std::string new_name)
{
    std::string string_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream;/*用于int转换为字符串*/
    mystream << user_id;
    mystream >> string_id;

    /*修改userinfo的用户名字*/
    std::string set_statement = std::string("update userinfo set name=\'") + new_name
        + "\' where id=" + string_id + ";";
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
    std::string string_id,string_age;/*用于存储int转化为的字符串*/
    std::stringstream mystream1,mystream2;/*用于int转换为字符串*/
    mystream1 << user_id;
    mystream1 >> string_id;
    mystream2 << new_age;
    mystream2 >> string_age;
    /*修改userinfo的用户年龄*/
    std::string set_statement = std::string("update userinfo set age=") +string_age
        + " where id=" + string_id + ";";
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
    std::string string_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream;/*用于int转换为字符串*/
    mystream << user_id;
    mystream >> string_id;
    /*修改userinfo的用户性别*/
    std::string set_statement = std::string("update userinfo set sex=\'") + new_sex
        + "\' where id=" + string_id + ";";
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
    std::string string_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream;/*用于int转换为字符串*/
    mystream << user_id;
    mystream >> string_id;
    /*修改userinfo的用户生日*/
    std::string set_statement = std::string("update userinfo set birthday=\'") + new_birth + "\' where id=" + string_id + ";";
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
    std::string string_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream;/*用于int转换为字符串*/
    mystream << user_id;
    mystream >> string_id;
    /*修改userinfo的用户邮箱*/
    std::string set_statement = std::string("update userinfo set email=\'") + new_email
        + "\' where id=" +  string_id + ";";
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
    std::string string_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream;/*用于int转换为字符串*/
    mystream << user_id;
    mystream >> string_id;
    /*修改userinfo的用户电话*/
    std::string set_statement = std::string("update userinfo set cellphone=\'") + new_cellphone
        + "\' where id=" + string_id + ";";
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
    std::string string_id,string_target_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream1,mystream2;/*用于int转换为字符串*/
    mystream1 << user_id;
    mystream1 >> string_id;
    mystream2 << target_user_id;
    mystream2 >> string_target_id;

    std::string query_statement = std::string("select * from user_relationship where user_id=") + string_id
        + " and target_user_id=" + string_target_id + ";";
    if(this->query(query_statement) != "")
        /*已经存在好友关系,插入失败！*/
    {
        std::cerr << "id:" << user_id << "target_id:" << target_user_id << "is friend!insert failed!" << std::endl;
        return false;
    }

    std::string insert_user_relationship = std::string("insert into user_relationship(user_id,target_user_id) values(") + string_id + "," + string_target_id + ");";
    /*插入好友关系*/
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
    std::string string_id,string_target_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream1,mystream2;/*用于int转换为字符串*/
    mystream1 << user_id;
    mystream1 >> string_id;
    mystream2 << target_user_id;
    mystream2 >> string_target_id;

    std::string delete_user_relationship = std::string("delete from user_relationship where user_id=")
        + string_id + ",target_user_id=" + string_target_id + ";";
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
    std::string string_id,string_target_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream1,mystream2;/*用于int转换为字符串*/
    mystream1 << user_id;
    mystream1 >> string_id;
    mystream2 << target_user_id;
    mystream2 >> string_target_id;

    std::string is_friend_statement = std::string("select * from user_relationship where user_id=")
        + string_id + " and target_user_id=" + string_target_id + ";";
    if(query(is_friend_statement) != "")
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
bool DataAccess::insert_group(unsigned int group_id, std::string group_name, int admin_id, std::string announcement)
{
    std::string string_group_id,string_admin_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream1,mystream2;/*用于int转换为字符串*/
    mystream1 << group_id;
    mystream1 >> string_group_id;
    mystream2 << admin_id;
    mystream2 >> string_admin_id;

    std::string insert_groupinfo_statement = std::string("insert into groupinfo(id,group_name,admin_id,announcement) values(") + string_group_id + ",\'" + group_name + "\'," + string_admin_id + ",\'" + announcement + "\');";
    if(!this->update(insert_groupinfo_statement))
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
    std::string string_group_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream1;/*用于int转换为字符串*/
    mystream1 << group_id;
    mystream1 >> string_group_id;

    std::string delete_groupinfo_statement = std::string("delete from groupinfo where id=") + string_group_id + ";";
    if(!this->update(delete_groupinfo_statement))
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
    std::string string_group_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream1;/*用于int转换为字符串*/
    mystream1 << group_id;
    mystream1 >> string_group_id;

    std::string set_group_statement = std::string("update groupinfo set announcement=\'")
        + new_announcement + "\' where id=" + string_group_id + ";";
    if(!this->update(set_group_statement))
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
    std::string string_group_id,string_admin_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream1,mystream2;/*用于int转换为字符串*/
    mystream1 << group_id;
    mystream1 >> string_group_id;
    mystream2 << admin_id;
    mystream2 >> string_admin_id;

    std::string query_statement = std::string("select * from groupinfo where id=")
        + string_group_id + " and admin_id=" + string_admin_id + ";";
    if(this->query(query_statement) != "")
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
    std::string string_group_id,string_user_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream1,mystream2;/*用于int转换为字符串*/
    mystream1 << group_id;
    mystream1 >> string_group_id;
    mystream2 << user_id;
    mystream2 >> string_user_id;

    /*查询是否已经存在，若存在，在返回false*/
    std::string query_statement = std::string("select * from group_relationship where group_id=") + string_group_id
        + " and user_id=" + string_user_id + ";";
    if(this->query(query_statement) != "")
    {
        return false;
    }
    /*插入群用户*/
    std::string join_group_statement = std::string("insert into group_relationship(group_id,user_id) values(")
        + string_group_id + "," + string_user_id + ");";
    if(!this->update(join_group_statement))
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
    std::string string_group_id,string_user_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream1,mystream2;/*用于int转换为字符串*/
    mystream1 << group_id;
    mystream1 >> string_group_id;
    mystream2 << user_id;
    mystream2 >> string_user_id;

    std::string quit_group_statement = std::string("delete from group_relationship")
        + "where group_id=" + string_group_id + " and user_id=" + string_user_id + ";";
    if(!this->update(quit_group_statement))
    {
        return false;
    }
    return true;
}
/*
 * 函数功能：是否是群成员
 */
bool DataAccess::is_group_member(int group_id, int user_id)
{
    std::string string_group_id,string_user_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream1,mystream2;/*用于int转换为字符串*/
    mystream1 << group_id;
    mystream1 >> string_group_id;
    mystream2 << user_id;
    mystream2 >> string_user_id;

    std::string query_statement = std::string("select * from group_relationship where")
        + " group_id=" + string_group_id + " and user_id=" + string_user_id + ";";
    //std::string temp = " empty string";
    if(this->query(query_statement) != "")
    {
        return true;
    }
    return false;
}

/*
 * 函数功能：创建红包
 * 函数参数：领取/发送红包id，领取/发送时间，红包类型
 * 函数参数：红包被分的数量，金额，发送红包id
 */
bool DataAccess::insert_red_package(unsigned int user_id, std::string datetime, unsigned short type, unsigned int num, int money, unsigned int send_id)
{
    std::string string_user_id,string_type,string_num,string_money,string_send_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream1,mystream2,mystream3,mystream4,mystream5;/*用于int转换为字符串*/
    mystream1 << user_id;
    mystream1 >> string_user_id;
    mystream2 << type;
    mystream2 >> string_type;
    mystream3 << num;
    mystream3 >> string_num;
    mystream4 << money;
    mystream4 >> string_money;
    mystream5 << send_id;
    mystream5 >> string_send_id;

    /*查询是否已经存在，若存在，在返回false*/
    std::string query_statement = std::string("select * from red_package where user_id=") + string_user_id
        + " and red_package_time=\'" + datetime + "\';";
    if(this->query(query_statement) != "")
    {
        return false;
    }
    /*插入红包*/
    std::string insert_statement = std::string("insert into red_package")
        + "(user_id,red_package_time,type,num,money,send_id)"
        + " values(" + string_user_id + ",\'" + datetime + "\',"
        + string_type + "," + string_num + "," + string_money + "," + string_send_id + ");";
    if(!this->update(insert_statement))
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
    std::string string_id;/*用于存储int转化为的字符串*/
    std::stringstream mystream;/*用于int转换为字符串*/
    mystream << user_id;
    mystream >> string_id;

    std::string delete_statement = std::string("delete from red_package where user_id=")
        + string_id + " and red_package_time=\'" + datetime + "\';";
    if(!update(delete_statement))
    {
        return false;
    }
    return true;
}
