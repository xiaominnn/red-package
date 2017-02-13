#include <stdio.h>  
#include <mysql.h>  
#include <string.h>  
int main(int argc, const char *argv[])  
{  
    MYSQL           mysql;  
    MYSQL_RES       *res = NULL;  
    MYSQL_ROW       row;  
    char            *query_str = NULL;  
    int             rc, i, fields;  
    int             rows;  
    if (NULL == mysql_init(&mysql)) {  
        printf("mysql_init(): %s\n", mysql_error(&mysql));  
        return -1;  
    }  
    if (NULL == mysql_real_connect(&mysql,  
                "localhost",  
                "root",  
                "111111",  
                "chat",  
                3306,  
                NULL,  
                0)) {  
        printf("mysql_real_connect(): %s\n", mysql_error(&mysql));  
        return -1;  
    }  
    printf("1. Connected MySQL successful! \n");  
//执行插入请求  
    query_str = "insert into login values (2, 111111)";  
    rc = mysql_real_query(&mysql, query_str, strlen(query_str));  
    if (0 != rc) {  
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));  
        return -1;  
    }  
//然后查询插入删除之后的数据  
    query_str = "select * from login";  
    rc = mysql_real_query(&mysql, query_str, strlen(query_str));  
    if (0 != rc) {  
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));  
        return -1;  
    }  
    res = mysql_store_result(&mysql);  
    if (NULL == res) {  
         printf("mysql_restore_result(): %s\n", mysql_error(&mysql));  
         return -1;  
    }  
    rows = mysql_num_rows(res);  
    printf("The total rows is: %d\n", rows);  
    fields = mysql_num_fields(res);  
    printf("The total fields is: %d\n", fields);  
    while ((row = mysql_fetch_row(res))) {  
        for (i = 0; i < fields; i++) {  
            printf("%s\t", row[i]);  
        }  
        printf("\n");  
    }  
//执行删除请求  
    query_str = "delete from login where id=2";  
    rc = mysql_real_query(&mysql, query_str, strlen(query_str));  
    if (0 != rc) {  
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));  
        return -1;  
    }  
//然后查询插入删除之后的数据  
    query_str = "select * from login";  
    rc = mysql_real_query(&mysql, query_str, strlen(query_str));  
    if (0 != rc) {  
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));  
        return -1;  
    }  
    res = mysql_store_result(&mysql);  
    if (NULL == res) {  
         printf("mysql_restore_result(): %s\n", mysql_error(&mysql));  
         return -1;  
    }  
    rows = mysql_num_rows(res);  
    printf("The total rows is: %d\n", rows);  
    fields = mysql_num_fields(res);  
    printf("The total fields is: %d\n", fields);  
    while ((row = mysql_fetch_row(res))) {  
        for (i = 0; i < fields; i++) {  
            printf("%s\t", row[i]);  
        }  
        printf("\n");  
    }  
    mysql_free_result(res);  
    mysql_close(&mysql);  
    return 0;  
}  
