#include "CMemcached.h"

int main()
{
    CMemcached *cmemcached = new CMemcached("127.0.0.1", 11211);
    /* if(cmemcached->set_key("key", "value", 0, 0))
    {
        std::cout << "set key success!" << std::endl;
    }
    std::string value1 = cmemcached->get_key("key");
    if(value1 != "")
    {
        std::cout << "key value:" << value1 << std::endl;
    } */
    if(cmemcached->delete_key("key", 0))
    {
        std::cout << "delete key:key success!" << std::endl;
    }
    return 0;
}
