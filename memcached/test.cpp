/*
 * 编译命令：g++ -o test test.cpp MemcAccess.cpp MemcAccess.h CMemcached.cpp CMemcached.h -g -lmemcached -ljson -std=c++11
 */
//#include "CMemcached.h"
#include "MemcAccess.h"

int main()
{
    /* CMemcached *cmemcached = new CMemcached("127.0.0.1", 11211); */
    /* if(cmemcached->set_key("key", "value", 0, 0))
    {
        std::cout << "set key success!" << std::endl;
    }
    std::string value1 = cmemcached->get_key("key");
    if(value1 != "")
    {
        std::cout << "key value:" << value1 << std::endl;
    } */
    /* if(cmemcached->delete_key("key", 0))
    {
        std::cout << "delete key:key success!" << std::endl;
    } */

    MemcAccess *memcAccess = new MemcAccess("127.0.0.1", 11211);
    if(memcAccess->insert_login(5, "111111", 0, 0))
    {
        std::cout << "insert login id:5 success!" << std::endl;
    }
    std::string value1 = memcAccess->query_login(5);
    if(value1 != "")
    {
        std::cout << "login id 5 value:" << value1 << std::endl;
    } 
    /* if(memcAccess->delete_login(5, 0))
    {
        std::cout << "delete login id 5 success!" << std::endl;
    } */
    /* if(memcAccess->insert_userinfo(5, "xiaomin", 24, "男", "1992-12-19", "8970@qq.com", "1559498", 0, 0))
    {
        std::cout << "insert id:5 userinfo success!" << std::endl;
    }
    std::string value_userinfo = memcAccess->query_userinfo(5);
    if(value_userinfo != "")
    {
        std::cout << "user id:5 userinfo:" << value_userinfo <<std::endl;
    } */
    /* if(memcAccess->insert_friend(5, 6, 0, 0))
    {
        std::cout << "id:5 insert friend id:6 success!" << std::endl;
    }
    if(memcAccess->insert_friend(5, 7, 0, 0))
    {
        std::cout << "id:5 insert friend id:7 success!" << std::endl;
    }
    if(memcAccess->insert_friend(5, 8, 0, 0))
    {
        std::cout << "id:5 insert friend id:8 success!" << std::endl;
    } */
    /* if(memcAccess->query_friend(5, 7))
    {
        std::cout << "id:5 has friend id:7." << std::endl;
    }
    if(memcAccess->query_friend(5, 8))
    {
        std::cout << "id:5 has friend id:8." << std::endl;
    } 
    if(memcAccess->delete_friend(5, 6, 0, 0))
    {
        std::cout << "id:5 delete friend id:6 success!" << std::endl;
    }
    if(memcAccess->delete_friend(5, 7, 0, 0))
    {
        std::cout << "id:5 delete friend id:7 success!" << std::endl;
    }
    if(memcAccess->delete_friend(5, 8, 0, 0))
    {
        std::cout << "id:5 delete friend id:8 success!" << std::endl;
    } */

    /* if(memcAccess->insert_groupinfo(10, "love nan", 5, "nan beauty", 0, 0))
    {
        std::cout << "insert group id:10 success!" << std::endl;
    }
    std::string value_group = memcAccess->query_groupinfo(10);
    if(value_group != "")
    {
        std::cout << "group id 10:" << value_group << "." << std::endl;
    } */
    /* if(memcAccess->delete_groupinfo(10, 0))
    {
        std::cout << "delete group: 10 success!" << std::endl;
    } */
    /* if(memcAccess->insert_group_member(10, 8, 0, 0))
    {
        std::cout << "group id:10 insert member id:8 success!" << std::endl;
    }
    if(memcAccess->insert_group_member(10, 9, 0, 0))
    {
        std::cout << "group id:10 insert member id:9 success!" << std::endl;
    }
    if(memcAccess->insert_group_member(10, 7, 0, 0))
    {
        std::cout << "group id:10 insert member id:7 success!" << std::endl;
    }  */
    /* if(memcAccess->has_group_member(10, 7))
    {
        std::cout << "group id:10 has member id:7" << std::endl;
    }
    if(memcAccess->has_group_member(10, 8))
    {
        std::cout << "group id:10 has member id:8" << std::endl;
    }
    if(memcAccess->has_group_member(10, 20))
    {
        std::cout << "group id:10 has member id:20" << std::endl;
    }
    else
    {
        std::cout << "group id:10 have not member id:20" << std::endl;
    }
    if(memcAccess->delete_group_member(10, 7, 0, 0))
    {
        std::cout << "group id:10 delete member id:7 success!" << std::endl;
    }
    if(memcAccess->delete_group_member(10, 8, 0, 0))
    {
        std::cout << "group id:10 delete member id:8 success!" << std::endl;
    }
    if(memcAccess->delete_group_member(10, 9, 0, 0))
    {
        std::cout << "group id:10 delete member id:9 success!" << std::endl;
    } */
    /* if(memcAccess->insert_red_package(6, "2017-2-20 15:48:01", 1, 8, 10, 6, 0, 0))
    {
        std::cout << "insert red package id:6 time:2017-2-20 15:48:00 success!" << std::endl;
    }
    std::string value_red_package = memcAccess->query_red_package(6, "2017-2-2015:48:01");
    if(value_red_package != "")
    {
        std::cout << "query red package id:6 time:2017-2-20 15:48:00:" << value_red_package << std::endl;
    } */
    if(memcAccess->delete_red_package(6, "2017-2-20 15:48:01", 0))
    {
        std::cout << "delete red package id:6 time:2017-2-20 15:48:00 success!" << std::endl;
    } 
    /* if(memcAccess->insert_money(6, 20, 0, 0))
    {
        std::cout << "insert money:20 id:6 success!" << std::endl;
    }
    int money = memcAccess->query_money(6);
    if(money != -1)
    {
        std::cout << "id:6 money:" << money << std::endl;
    } */
    if(memcAccess->delete_money(6, 0))
    {
        std::cout << "delete money id:6 success!" << std::endl;
    }
    return 0;
}
