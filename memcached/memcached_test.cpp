//g++ -o memcached_test memcached_test.cpp -lmemcached -std=c++11 -g


#include <iostream>
#include <string>
#include <libmemcached/memcached.h>

using namespace std;

int main(int argc,char *argv[])
{
   //connect server

   memcached_st *memc;
   memcached_return rc;
   memcached_server_st *server;
   time_t expiration = 0;
   uint32_t flags;

   memc = memcached_create(NULL);
   server = memcached_server_list_append(NULL,"localhost",11211,&rc);
   rc=memcached_server_push(memc,server);
   memcached_server_list_free(server);

   string key = "key";
   string value = "value";
   size_t value_length = value.length();
   size_t key_length = key.length();


   //Save data

   rc=memcached_set(memc,key.c_str(),key.length(),value.c_str(),value.length(),expiration,flags);
   if(rc==MEMCACHED_SUCCESS)
   {
       cout<<"Save data:"<<value<<" sucessful!"<<endl;
   }

   //Get data

   char* result = memcached_get(memc,key.c_str(),key_length,&value_length,&flags,&rc);
   if(rc == MEMCACHED_SUCCESS)
   {
       cout<<"Get value:"<<result<<" sucessful!"<<endl;
   }

   //Delete data

   rc=memcached_delete(memc,key.c_str(),key_length,expiration);
   if(rc==MEMCACHED_SUCCESS)
   {
       cout<<"Delete key:"<<key<<" sucessful!"<<endl;
   }

   //free

   memcached_free(memc);
   return 0;
}
