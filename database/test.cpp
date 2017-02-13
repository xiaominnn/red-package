#include "DataAccess.h"
#include "mysqlValue.h"

extern int MY_MYSQL_PROT;

int main()
{
    DataAccess *dataAccess = new DataAccess("127.0.0.1", MY_MYSQL_PROT, "root", "111111", "chat");
    if(dataAccess->insert_login(10,"111111"))
    {
        std::cout << "insert login success!" << std::endl;
    }


    return 0;
}
