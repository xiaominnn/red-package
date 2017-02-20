/*
 * C语言访问memcached类成员函数实现
 */

#include "CMemcached.h"
/*
 * 函数功能：构造函数
 * 参数：memcached的ip，端口
 */
CMemcached::CMemcached(std::string ip, unsigned int port):memc_con(NULL),memc_serv(NULL)
{
    memc_con = memcached_create(NULL);
    if(memc_con == NULL)
    {
        std::cerr << "memcached create error!" << std::endl;
        exit(-1);
    }
    memc_serv = memcached_server_list_append(NULL, ip.c_str(), port, &memc_res);
    if(memc_serv == NULL)
    {
        std::cerr << "memcached server error!" << std::endl;
        exit(-1);
    }
    memc_res = memcached_server_push(memc_con, memc_serv);
    if(memc_res != MEMCACHED_SUCCESS)
    {
        std::cerr << "memcached server push error!" << std::endl;
        exit(-1);
    }
}
/*
 * 函数功能：析构函数
 */
CMemcached::~CMemcached()
{
    memcached_server_list_free(memc_serv);
    memcached_free(memc_con);
}
/*
 * 函数功能：查询键为key的值
 * 返回值：若有，则返回值，否则，返回""
 */
std::string CMemcached::get_key(std::string key)
{
    /*若memcached_get查询无结果，则返回NULL*/
    char *value = memcached_get(memc_con,key.c_str(),key.length(),NULL,NULL,&memc_res);
    if(memc_res == MEMCACHED_SUCCESS)
        /*查询成功*/
    {
        return value;
    }
    else
        /*未找到或者错误*/
    {
        return "";
    }
}
/*
 * 函数功能：设置键为key的值为value，标志为flags，保存时间为expiration
 */
bool CMemcached::set_key(std::string key, std::string value, uint32_t flags, time_t expiration)
{
    memc_res = memcached_set(memc_con, key.c_str(), key.length(), value.c_str(), value.length(), expiration, flags);
    if(memc_res == MEMCACHED_SUCCESS)
    {
        return true;
    }
    return false;
}
/*
 * 函数功能：删除键为key的值，删除时间为expiration
 */
bool CMemcached::delete_key(std::string key, time_t expiration)
{
    memc_res = memcached_delete(memc_con, key.c_str(), key.length(), expiration);
    if(memc_res == MEMCACHED_SUCCESS)
        /*删除成功*/
    {
        return true;
    }
    return false;
}
