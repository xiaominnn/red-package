#include "DataAccess.h"

int main()
{
    DataAccess *dataAccess = new DataAccess("127.0.0.1", 3306, "root", "111111", "chat");
    if(dataAccess->insert_login(10,"111111"))
    {
        std::cout << "insert login success!" << std::endl;
    }

    if(dataAccess->insert_userinfo(10,"xiaomin",24,"男",
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
    }
    if(dataAccess->set_user_cellphone(10, "15594999"))
    {
        std::cout << "set user cellphone success!" << std::endl;
    }
    return 0;
}
