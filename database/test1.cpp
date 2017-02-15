#include "DataAccess.h"

int main()
{
    DataAccess *dataAccess = new DataAccess("127.0.0.1", 3306, "root", "111111", "chat");
    /* if(dataAccess->insert_login(11,"111111"))
    {
        std::cout << "insert login success!" << std::endl;
    }
    if(dataAccess->insert_login(12,"小敏"))
    {
        std::cout << "insert login success!" << std::endl;
    }

    if(dataAccess->insert_userinfo(11,"xiaomin",24,"男",
                "1992-12-19","897069662@qq.com","5594984044"))
    {
        std::cout << "insert userinfo success!" << std::endl;
    }
    if(dataAccess->insert_login(10,"111111"))
    {
        std::cout << "insert login success!" << std::endl;
    }

    if(dataAccess->insert_userinfo(10,"xiaomin",24,"man",
                "1992-12-19","897069662@qq.com","5594984044"))
    {
        std::cout << "insert userinfo success!" << std::endl;
    }

    if(dataAccess->set_user_name(10,"nannan"))
    {
        std::cout << "set user name success!" << std::endl;
    }

    if(dataAccess->set_user_age(10, 20))
    {
        std::cout << "set user age success !" << std::endl;
    }
    if(dataAccess->set_user_sex(10,"女"))
    {
        std::cout << "set user sex success!" << std::endl;
    }
    if(dataAccess->set_user_birth(10,"1995-10-30"))
    {
        std::cout << "set user birthday success!" << std::endl;
    }
    if(dataAccess->set_user_email(10, "1234@qq.com"))
    {
        std::cout << "set user email success!" << std::endl;
    } */
    /* if(dataAccess->set_user_cellphone(10, "15594999"))
    {
        std::cout << "set user cellphone success!" << std::endl;
    }  */
    /* if(dataAccess->insert_friend(10,11))
    {
        std::cout << "user_id:10 insert friend user_id:11 success!" << std::endl;
    }
    if(dataAccess->match_friend(10,11))
    {
        std::cout << "id:10 and id:11 is frined!" << std::endl;
    } */
    /* if(dataAccess->insert_group(5,"beauty",10,"love nn"))
    {
        std::cout << "insert group success!" << std::endl;
    }
    if(dataAccess->set_group_announce(5,"very love nn"))
    {
        std::cout << "set group annoucement success!" << std::endl;
    }
    if(dataAccess->is_group_admin(5,10))
    {
        std::cout << "id:10 is admin of group 5!" << std::endl;
    }  */
    /* if(dataAccess->delete_group(5))
    {
        std::cout << "group 5 is deleted!" << std::endl;
    } */
    /* if(dataAccess->join_group(10,5))
    {
        std::cout << "user_id:10 join group:5 success!" << std::endl;
    }
    if(dataAccess->join_group(11,5))
    {
        std::cout << "user_id:11 join group:5 success!" << std::endl;
    }
    if(dataAccess->is_group_member(5,11))
    {
        std::cout << "user_id:11 is member of group:5!" << std::endl;
    } */
    /* if(dataAccess->insert_red_package(10,"2017-2-15 15:18:00",1,5,10,10))
    {
        std::cout << "insert red package success!" << std::endl;
    } */
    if(dataAccess->delete_red_package(10,"2017-2-15 15:18:00"))
    {
        std::cout << "delete red package success!" << std::endl;
    }

    return 0;
}
