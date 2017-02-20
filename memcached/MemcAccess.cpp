/*
 * MemcAccess类的成员函数实现
 */

#include "MemcAccess.h"

MemcAccess::MemcAccess(std::string ip, unsigned int port):CMemcached(ip, port)
{
}
/*
 * 函数功能：插入登陆login键值对
 * 参数：用户id，密码
 * 备注：转化为key为login+id，value为密码
 */
bool MemcAccess::insert_login(unsigned int user_id, std::string password, int flags, time_t expiration)
{
    std::string string_user_id;/*用于储存int转化的字符串*/
    std::stringstream mystream;/*用于int转换为字符串*/
    mystream << user_id;
    mystream >> string_user_id;

    /*插入的key值:login+用户id*/
    std::string key_login = std::string("login") + string_user_id;

    return set_key(key_login, password, flags, expiration);
}
/*
 * 函数功能：删除登陆记录
 */
bool MemcAccess::delete_login(unsigned int user_id, time_t expiration)
{
    std::string string_user_id;/*用于储存int转化的字符串*/
    std::stringstream mystream;/*用于int转换为字符串*/
    mystream << user_id;
    mystream >> string_user_id;

    /*删除的key值:login+用户id*/
    std::string key_login = std::string("login") + string_user_id;

    return delete_key(key_login, expiration);
}
/*
 * 函数功能：查询登陆记录
 */
std::string MemcAccess::query_login(unsigned int user_id)
{
    std::string string_user_id;/*用于储存int转化的字符串*/
    std::stringstream mystream;/*用于int转换为字符串*/
    mystream << user_id;
    mystream >> string_user_id;

    /*查询的key值:login+用户id*/
    std::string key_login = std::string("login") + string_user_id;

    return get_key(key_login);
}

/*
 * 函数功能：插入用户信息userinfo记录
 */
bool MemcAccess::insert_userinfo(unsigned int user_id, std::string user_name, unsigned short age, 
        std::string sex, std::string birthday, std::string email, std::string cellphone,
        int flags, time_t expiration)
{
    std::string string_user_id,string_age;/*用于储存int转化的字符串*/
    std::stringstream mystream1,mystream2;/*用于int转换为字符串*/
    mystream1 << user_id;
    mystream1 >> string_user_id;
    mystream2 << age;
    mystream2 >> string_age;

    /*插入的key值:userinfo+用户id*/
    std::string key_userinfo = std::string("userinfo") + string_user_id;

    /*将插入key的值以json形式反序列化为字符串储存*/
    Json::FastWriter writer;/*用于将json变量反序列化为字符串*/
    Json::Value value;/*存储value的json对象*/
    value["name"] = user_name;
    value["age"] = string_age;
    value["sex"] = sex;
    value["birthday"] = birthday;
    value["email"] = email;
    value["cellphone"] = cellphone;
    std::string value_userinfo = writer.write(value);/*key中值的字符串*/

    return set_key(key_userinfo, value_userinfo, flags, expiration);
}
/*
 * 函数功能：删除用户信息记录
 * 参数：删除的时间expiration
 */
bool MemcAccess::delete_userinfo(unsigned int user_id, time_t expiration)
{
    std::string string_user_id;/*用于储存int转化的字符串*/
    std::stringstream mystream;/*用于int转换为字符串*/
    mystream << user_id;
    mystream >> string_user_id;

    /*删除的key值:userinfo+用户id*/
    std::string key_userinfo = std::string("userinfo") + string_user_id;

    return delete_key(key_userinfo, expiration);
}
/*
 * 函数功能：查询用户信息记录
 */
std::string MemcAccess::query_userinfo(unsigned int user_id)
{
    std::string string_user_id;/*用于储存int转化的字符串*/
    std::stringstream mystream;/*用于int转换为字符串*/
    mystream << user_id;
    mystream >> string_user_id;

    /*查询的key值:userinfo+用户id*/
    std::string key_userinfo = std::string("userinfo") + string_user_id;

    return get_key(key_userinfo);
}

/*
 * 函数功能：添加朋友记录
 */
bool MemcAccess::insert_friend(unsigned int user_id, unsigned int target_user_id, int flags, time_t expiration)
{
    std::string string_user_id,string_target_id;/*用于储存int转化的字符串*/
    std::stringstream mystream1,mystream2;/*用于int转换为字符串*/
    mystream1 << user_id;
    mystream1 >> string_user_id;
    mystream2 << target_user_id;
    mystream2 >> string_target_id;

    /*插入的key值:user_relationship+用户id*/
    std::string key_user_relationship = std::string("user_relationship") + string_user_id;

    /*将插入key的值以json形式反序列化为字符串储存*/
    Json::FastWriter writer;/*用于将json变量反序列化为字符串*/
    Json::Reader reader;/*用于将字符串序列化为json对象*/
    Json::Value value;/*存储value的json对象*/

    std::string query_user_friend = get_key(key_user_relationship);/*查询该id的好友关系是否存在*/
    if(query_user_friend == "")
        /*若没有查询到，则是第一次插入该id好友*/
    {
        value.append(string_target_id);
    }
    else
        /*该id已经有好友，则看该好友是否已经存在；若不存在，则插入*/
    {
        /*解析string字符串为json对象*/
        if(!reader.parse(query_user_friend, value))
            /*解析出错*/
        {
            std::cerr << "parse string to json object failed!" << std::endl;
            return false;
        }
        for(Json::Value::iterator iter = value.begin(); iter != value.end(); ++iter)
        {
            if(*iter == string_target_id)
                /*好友已经存在，返回true*/
            {
                std::cerr << "user_id:" << user_id << "has friend id:" << target_user_id << ".can't insert!"<< std::endl;
                return true;
            }
        }
        /*若没有找到，则插入该好友*/
        value.append(string_target_id);
    }

    std::string value_user_relationship = writer.write(value);/*key的value*/
    return set_key(key_user_relationship, value_user_relationship, flags, expiration);
}
/*
 * 函数功能：删除朋友关系记录
 * 参数：设置朋友关系标志flags，删除后朋友关系存在的时间expiration */
bool MemcAccess::delete_friend(unsigned int user_id, unsigned int target_user_id, int flags, time_t expiration)
{
    std::string string_user_id,string_target_id;/*用于储存int转化的字符串*/
    std::stringstream mystream1,mystream2;/*用于int转换为字符串*/
    mystream1 << user_id;
    mystream1 >> string_user_id;
    mystream2 << target_user_id;
    mystream2 >> string_target_id;

    /*删除的key值:user_relationship+用户id*/
    std::string key_user_relationship = std::string("user_relationship") + string_user_id;

    /*将插入key的值以json形式反序列化为字符串储存*/
    Json::FastWriter writer;/*用于将json变量反序列化为字符串*/
    Json::Reader reader;/*用于将字符串序列化为json对象*/
    Json::Value value_return,value_query;/*存储value的json对象*/

    std::string query_user_friend = get_key(key_user_relationship);/*查询该id的好友关系是否存在*/
    if(query_user_friend == "")
        /*若没有查询到，则没有好友，返回true*/
    {
        std::cerr << "user id :" << user_id << "have not friend id:" << target_user_id << "." << std::endl;
        return true;
    }
    else
        /*
         * 由于Json无法删除数组成员，只能把要删除成员之外的成员重新添加到一个json对象
         * 已达到删除该数组成员的目的
         */
    {
        /*解析string字符串为json对象*/
        if(!reader.parse(query_user_friend, value_query))
            /*解析出错*/
        {
            std::cerr << "parse string to json object failed!" << std::endl;
            return false;
        }
        for(Json::Value::iterator iter = value_query.begin(); iter != value_query.end(); ++iter)
        {
            if(*iter != string_target_id)
                /*如果不是该好友，则把该id原值添加*/
            {
                value_return.append(*iter);
            }
        }
        if(!value_return.size())
            /*若该用户无好友，则删除该记录*/
        {
            return delete_key(key_user_relationship, expiration);
        }
    }

    /*该用户剩下好友写入key对应的值中*/
    std::string value_user_relationship = writer.write(value_return);/*key的value*/
    return set_key(key_user_relationship, value_user_relationship, flags, expiration);
}
/*
 * 函数功能：查询是否存在朋友关系
 */
bool MemcAccess::query_friend(unsigned int user_id, unsigned int target_user_id)
{
    std::string string_user_id,string_target_id;/*用于储存int转化的字符串*/
    std::stringstream mystream1,mystream2;/*用于int转换为字符串*/
    mystream1 << user_id;
    mystream1 >> string_user_id;
    mystream2 << target_user_id;
    mystream2 >> string_target_id;

    /*查询的key值:user_relationship+用户id*/
    std::string key_user_relationship = std::string("user_relationship") + string_user_id;

    Json::Reader reader;/*用于将字符串序列化为json对象*/
    Json::Value value;/*存储value的json对象*/

    std::string query_user_friend = get_key(key_user_relationship);/*查询该id的好友关系是否存在*/
    if(query_user_friend == "")
        /*若没有查询到，则没有好友*/
    {
        return false;
    }
    else
        /*该id有好友，则看该好友是否已经存在；若存在，则返回true*/
    {
        /*解析string字符串为json对象*/
        if(!reader.parse(query_user_friend, value))
            /*解析出错*/
        {
            std::cerr << "parse string to json object failed!" << std::endl;
            return false;
        }
        for(Json::Value::iterator iter = value.begin(); iter != value.end(); ++iter)
        {
            if(*iter == string_target_id)
                /*好友存在*/
            {
                return true;
            }
        }
        /*没找到，则好友不存在*/
        return false;
    }
}

/*
 * 函数功能：插入群信息groupinfo记录
 */
bool MemcAccess::insert_groupinfo(unsigned int group_id, std::string group_name, unsigned int admin_id, std::string announcement, int flags, time_t expiration)
{
    std::string string_group_id,string_admin_id;/*用于储存int转化的字符串*/
    std::stringstream mystream1,mystream2;/*用于int转换为字符串*/
    mystream1 << group_id;
    mystream1 >> string_group_id;
    mystream2 << admin_id;
    mystream2 >> string_admin_id;

    /*插入的key值:groupinfo+用户id*/
    std::string key_groupinfo = std::string("groupinfo") + string_group_id;

    /*将插入key的值以json形式反序列化为字符串储存*/
    Json::FastWriter writer;/*用于将json变量反序列化为字符串*/
    Json::Value value;/*存储value的json对象*/
    value["group_name"] = group_name;
    value["admin_id"] = string_admin_id;
    value["announcement"] = announcement;
    std::string value_groupinfo = writer.write(value);/*key中值的字符串*/

    return set_key(key_groupinfo, value_groupinfo, flags, expiration);
}
/*
 * 函数功能：删除群信息groupinfo记录
 * 参数：删除的时间expiration
 */
bool MemcAccess::delete_groupinfo(unsigned int group_id, time_t expiration)
{
    std::string string_group_id;/*用于储存int转化的字符串*/
    std::stringstream mystream;/*用于int转换为字符串*/
    mystream << group_id;
    mystream >> string_group_id;

    /*删除的key值:groupinfo+用户id*/
    std::string key_groupinfo = std::string("groupinfo") + string_group_id;

    return delete_key(key_groupinfo, expiration);
}
/*
 * 函数功能：查询群组信息记录
 * 返回值：以json对象的字符串返回
 */
std::string MemcAccess::query_groupinfo(unsigned int group_id)
{
    std::string string_group_id;/*用于储存int转化的字符串*/
    std::stringstream mystream;/*用于int转换为字符串*/
    mystream << group_id;
    mystream >> string_group_id;

    /*查询的key值:groupinfo+用户id*/
    std::string key_groupinfo = std::string("groupinfo") + string_group_id;

    return get_key(key_groupinfo);
}

/*
 * 函数功能：添加群成员记录
 */
bool MemcAccess::insert_group_member(unsigned int group_id, unsigned int user_id, int flags, time_t expiration)
{
    std::string string_group_id,string_user_id;/*用于储存int转化的字符串*/
    std::stringstream mystream1,mystream2;/*用于int转换为字符串*/
    mystream1 << group_id;
    mystream1 >> string_group_id;
    mystream2 << user_id;
    mystream2 >> string_user_id;

    /*插入的key值:group_relationship+用户id*/
    std::string key_group_relationship = std::string("group_relationship") + string_group_id;

    /*将插入key的值以json形式反序列化为字符串储存*/
    Json::FastWriter writer;/*用于将json变量反序列化为字符串*/
    Json::Reader reader;/*用于将字符串序列化为json对象*/
    Json::Value value;/*存储value的json对象*/

    std::string query_group_member = get_key(key_group_relationship);/*查询是否有群成员*/
    if(query_group_member == "")
        /*若没有查询到，则是第一次往该群中加入用户*/
    {
        value.append(string_user_id);
    }
    else
        /*该群组已经有成员，则看该用户是否已经存在；若不存在，则插入*/
    {
        /*解析string字符串为json对象*/
        if(!reader.parse(query_group_member, value))
            /*解析出错*/
        {
            std::cerr << "parse string to json object failed!" << std::endl;
            return false;
        }
        for(Json::Value::iterator iter = value.begin(); iter != value.end(); ++iter)
        {
            if(*iter == string_user_id)
                /*该用户已经存在在群中，返回true*/
            {
                std::cerr << "group_id:" << group_id << "has member id:" << user_id << ".can't insert!"<< std::endl;
                return true;
            }
        }
        /*若没有找到，则插入该用户*/
        value.append(string_user_id);
    }

    std::string value_group_relationship = writer.write(value);/*key的value*/
    return set_key(key_group_relationship, value_group_relationship, flags, expiration);
}
/*
 * 函数功能：删除群成员
 */
bool MemcAccess::delete_group_member(unsigned int group_id, unsigned int user_id, int flags, time_t expiration)
{
    std::string string_group_id,string_user_id;/*用于储存int转化的字符串*/
    std::stringstream mystream1,mystream2;/*用于int转换为字符串*/
    mystream1 << group_id;
    mystream1 >> string_group_id;
    mystream2 << user_id;
    mystream2 >> string_user_id;

    /*删除的key值:group_relationship+用户id*/
    std::string key_group_relationship = std::string("group_relationship") + string_group_id;

    /*将插入key的值以json形式反序列化为字符串储存*/
    Json::FastWriter writer;/*用于将json变量反序列化为字符串*/
    Json::Reader reader;/*用于将字符串序列化为json对象*/
    Json::Value value_return,value_query;/*存储value的json对象*/

    std::string query_group_member = get_key(key_group_relationship);/*查询该群id的群成员是否存在*/
    if(query_group_member == "")
        /*若没有查询到，则没有群成员，返回true*/
    {
        std::cerr << "group id :" << group_id << "have not member id:" << string_user_id << "." << std::endl;
        return true;
    }
    else
        /*
         * 由于Json无法删除数组成员，只能把要删除成员之外的成员重新添加到一个json对象
         * 已达到删除该数组成员的目的
         */
    {
        /*解析string字符串为json对象*/
        if(!reader.parse(query_group_member, value_query))
            /*解析出错*/
        {
            std::cerr << "parse string to json object failed!" << std::endl;
            return false;
        }
        for(Json::Value::iterator iter = value_query.begin(); iter != value_query.end(); ++iter)
        {
            if(*iter != string_user_id)
                /*如果不是该群成员，则把该id原值添加*/
            {
                value_return.append(*iter);
            }
        }
        if(!value_return.size())
            /*若该群组没有群成员，则删除该记录*/
        {
            return delete_key(key_group_relationship, expiration);
        }
    }

    /*该用户剩下好友写入key对应的值中*/
    std::string value_group_relationship = writer.write(value_return);/*key的value*/
    return set_key(key_group_relationship, value_group_relationship, flags, expiration);
}
/*
 * 函数功能：是否是群成员
 */
bool MemcAccess::has_group_member(unsigned int group_id, unsigned int user_id)
{
    std::string string_group_id,string_user_id;/*用于储存int转化的字符串*/
    std::stringstream mystream1,mystream2;/*用于int转换为字符串*/
    mystream1 << group_id;
    mystream1 >> string_group_id;
    mystream2 << user_id;
    mystream2 >> string_user_id;

    /*查询的key值:group_relationship+用户id*/
    std::string key_group_relationship = std::string("group_relationship") + string_group_id;

    Json::Reader reader;/*用于将字符串序列化为json对象*/
    Json::Value value;/*存储value的json对象*/

    std::string query_group_friend = get_key(key_group_relationship);/*查询该群组id的群成员是否存在*/
    if(query_group_friend == "")
        /*若没有查询到，则没有群成员*/
    {
        return false;
    }
    else
        /*该群id有成员，则看该用户是否已经存在；若存在，则返回true*/
    {
        /*解析string字符串为json对象*/
        if(!reader.parse(query_group_friend, value))
            /*解析出错*/
        {
            std::cerr << "parse string to json object failed!" << std::endl;
            return false;
        }
        for(Json::Value::iterator iter = value.begin(); iter != value.end(); ++iter)
        {
            if(*iter == string_user_id)
                /*该用户存在*/
            {
                return true;
            }
        }
        /*没找到，则该用户不存在*/
        return false;
    }
}


/*
 * 函数功能：插入红包记录
 */
bool MemcAccess::insert_red_package(unsigned int user_id, std::string red_package_time, unsigned short type, unsigned int num, int money, unsigned int send_id, int flags, time_t expiration)
{
    std::string string_user_id,string_type,string_num,string_money,string_send_id;/*用于储存int转化的字符串*/
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

    /*
     * 由于memcached键不能有空格，则需要对时间red_package_time(例如：2017-2-20 17:06:00)中的空格进行处理
     * 使空格转化为|
     */
    int pos = red_package_time.find('\ ', 0);
    red_package_time.replace(pos, 1, "|");
    /*插入的key值:red_package(用户id,时间)*/
    std::string key_red_package = std::string("red_package(") + string_user_id + "," + red_package_time + ")";

    /*将插入key的值以json形式反序列化为字符串储存*/
    Json::FastWriter writer;/*用于将json变量反序列化为字符串*/
    Json::Value value;/*存储value的json对象*/
    value["type"] = string_type;
    value["num"] = string_num;
    value["money"] = string_money;
    value["send_id"] = string_send_id;
    std::string value_red_package = writer.write(value);/*key中值的字符串*/

    return set_key(key_red_package, value_red_package, flags, expiration);
}
/*
 * 函数功能：删除红包记录
 */
bool MemcAccess::delete_red_package(unsigned int user_id, std::string red_package_time, time_t expiration)
{
    std::string string_user_id;/*用于储存int转化的字符串*/
    std::stringstream mystream;/*用于int转换为字符串*/
    mystream << user_id;
    mystream >> string_user_id;

    /*
     * 由于memcached键不能有空格，则需要对时间red_package_time(例如：2017-2-20 17:06:00)中的空格进行处理
     * 使空格转化为|
     */
    int pos = red_package_time.find('\ ', 0);
    red_package_time.replace(pos, 1, "|");
    /*删除的key值:red_package(用户id,时间)*/
    std::string key_red_package = std::string("red_package(") + string_user_id + "," + red_package_time + ")";

    return delete_key(key_red_package, expiration);
}
/*
 * 函数功能：查询红包记录
 */
std::string MemcAccess::query_red_package(unsigned int user_id, std::string red_package_time)
{
    std::string string_user_id;/*用于储存int转化的字符串*/
    std::stringstream mystream;/*用于int转换为字符串*/
    mystream << user_id;
    mystream >> string_user_id;

    /*
     * 由于memcached键不能有空格，则需要对时间red_package_time(例如：2017-2-20 17:06:00)中的空格进行处理
     * 使空格转化为|
     */
    int pos = red_package_time.find('\ ', 0);
    /*查询的key值:red_package(用户id,时间)*/
    std::string key_red_package = std::string("red_package(") + string_user_id + "," + red_package_time + ")";

    return get_key(key_red_package);
}

/*
 * 函数功能：插入余额记录
 */
bool MemcAccess::insert_money(unsigned int user_id, int money, int flags, time_t expiration)
{
    std::string string_user_id,string_money;/*用于储存int转化的字符串*/
    std::stringstream mystream1,mystream2;/*用于int转换为字符串*/
    mystream1 << user_id;
    mystream1 >> string_user_id;
    mystream2 << money;
    mystream2 >> string_money;

    /*插入的key值:money+用户id*/
    std::string key_money = std::string("money") + string_user_id;
    /*插入的value值*/
    std::string value_money = string_money;

    return set_key(key_money, value_money, flags, expiration);
}
/*
 * 函数功能：删除余额记录
 */
bool MemcAccess::delete_money(unsigned int user_id, time_t expiration)
{
    std::string string_user_id;/*用于储存int转化的字符串*/
    std::stringstream mystream1;/*用于int转换为字符串*/
    mystream1 << user_id;
    mystream1 >> string_user_id;

    /*删除的key值:money+用户id*/
    std::string key_money = std::string("money") + string_user_id;

    return delete_key(key_money, expiration);
}
/*
 * 函数功能：查询余额
 * 返回值：查询成功，返回余额；查询失败，返回-1
 */
int MemcAccess::query_money(unsigned int user_id)
{
    std::string string_user_id;/*用于储存int转化的字符串*/
    std::stringstream mystream1;/*用于int转换为字符串*/
    mystream1 << user_id;
    mystream1 >> string_user_id;
    mystream1.clear();

    /*查询的key值:money+用户id*/
    std::string key_money = std::string("money") + string_user_id;

    /*查询money的结果*/
    std::string value_money = get_key(key_money);
    if(value_money == "")
        /*查询失败，返回-1*/
    {
        return -1;
    }
    /*将字符串结果转化为int*/
    int money = 0;
    mystream1 << value_money;
    mystream1 >> money;

    return money;

}

