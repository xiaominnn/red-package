# 微信红包项目数据库设计
## 1.目录
[TOC]
## 2.数据库使用平台
ubuntu15.10下使用**mysql**数据库进行数据的存储
## 3.数据库表的设计   
### 3.1数据库的名字及使用命令

1. 登陆mysql数据库：`$mysql -uroot -p`,然后输入数据库root用户密码。
2. 查看所有的数据库：`$show databases;`
3. 建立数据库名为chat的数据库：`$create database chat;`
4. 选择数据库名为chat的数据库：`$use chat;`

### 3.2数据库表的设计及建立

* 登陆表(login)  
    * 属性：用户id(属性名：id,主键,唯一,非空,自动增加),密码(属性名：password)  
    * sql语句：create table login(  
        id int not null auto_increment unique primary key,  
        password varchar(20) not null);  
* 用户信息表(userinfo)  
    * 属性：  
    * sql创建语句：create table userinfo(  
        id int primary key not null unique,  
        name varchar(20) not null,  
        age smallint default 0,  
        sex varchar(5) not null,  
        birthday date not null,  
        email varchar(20) not null,  
        cellphone varchar(20) not null default '0',  
        constraint c_fk foreign key(id) references login(id)  
        )charset=utf8;
* 个人关系表(user_relationship)
    <!--无法添加外键，不知道为什么-->
    * 属性：  
    * sql创建语句：create table user_relationship(  
        id int primary key not null unique auto_increment,  
        user_id int unsigned not null,  
        target_user_id int unsigned not null,  
        foreign key(user_id) references login(id) on update cascade on delete cascade,  
        foreign key(target_user_id) references login(id) on update cascade on delete cascade  
        )charset=utf8;  
* 群组信息表(groupinfo)
    * 属性：  
    * sql创建语句：create table groupinfo(  
        id int not null auto_increment unique primary key,  
        announcement varchar(30) not null  
        )charset=utf8;  
    * sql修改语句：
        * 增加属性：alter table groupinfo add admin_id int not null after id;
        * 增加外键：alter table groupinfo add foreign key(admin_id) references login(id) on update cascade on delete cascade;
* 群组关系表(group_relationship)
    * 属性：  
    * sql创建语句：create table group_relationship(  
        id int not null auto_increment unique primary key,  
        group_id int unique,  
        user_id int unique,  
        foreign key(group_id) references groupinfo(id) on update cascade on delete cascade,  
        foreign key(user_id) references login(id) on update cascade on delete cascade  
        )charset=utf8;  
    * 对表属性进行修改  
        * 修改group_id，去掉其唯一性约束：alter table group_relationship drop index group_id;(必须先删除所有外键)  
        * 修改user_id，去掉其唯一性约束：alter table group_relationship drop index user_id;(必须先删除所有外键)  
* 钱包表(money)
    * 属性：  
    * sql创建语句：create table money(  
        id int not null primary key unique,  
        balance int not null default 0,  
        foreign key(id) references login(id) on update cascade on delete cascade  
        )charset=utf8;  
* 红包表(red_package)
    * 属性：  
    * sql创建语句：create table red_package(  
        user_id int,  
        red_package_time datetime,  
        type tinyint,  
        num int unsigned,  
        money int,  
        primary key(user_id,red_package_time),  
        foreign key(user_id) references login(id) on update cascade on delete cascade  
        )charset=utf8;  
    * sql修改语句：
        * 增加属性：alter table red_package add send_id int not null after money;
        * 增加外键：alter table red_package add foreign key(send_id) references login(id) on update cascade on delete cascade;

### 3.3数据库使用的错误及解决方法
1. 创建外键时，主表的属性名不能相同，如果外键的两个属性都受主表同一个属性约束，则必须使用两条外键创建语句(例子:3.2 个人关系表);  
## 4文件描述
1. mysql_connect_test.c
    * 内容：使用C与mysql数据库建立连接的简单例子
    * 编译命令：gcc -o mysql_connect_test mysql_connect_test -I/usr/include/mysql/ -lmysqlclient -g
2. mysql_connect_test
    * 内容：由mysql_connect_test.c生成的可执行文件
    * 执行内容：  
3. mysql_use_test.c
    * 内容：使用C语言进行对mysql数据库增删查改的简单例子
    * 编译命令：gcc -o mysql_use_test mysql_use_test -I/usr/include/mysql/ -lmysqlclient -g
4. mysql_use_test
    * 内容：由mysql_use_test.c生成的可执行文件
    * 执行内容：  
