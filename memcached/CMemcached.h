/*
 * C语言访问memcached类
 */
#ifndef CMEMCACHED_H
#define CMEMCACHED_H

#include <libmemcached/memcached.h>
#include <string>
#include <iostream>

class CMemcached
{
public:
    CMemcached(std::string ip, unsigned int port);
    ~CMemcached();
    /*
     * 函数功能：查询键为key的值
     * 返回值：若有，则返回值，否则，返回""
     */
    std::string get_key(std::string key);
    /*
     * 函数功能：设置键为key的值为value，标志为flags
     *     保存时间为expiration
     */
    bool set_key(std::string key, std::string value, uint32_t flags, time_t expiration);
    /*
     * 函数功能：删除键为key的值，删除时间为expiration
     */
    bool delete_key(std::string key, time_t expiration);
private:
    memcached_st *memc_con;/*memcached connection数据结构*/
    memcached_server_st *memc_serv;/*memcached server数据结构*/
    memcached_return memc_res;/*memcached返回值*/
};
#endif
