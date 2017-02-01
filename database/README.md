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
    <--无法添加外键，不知道为什么--!>
    * 属性：  
    * sql创建语句：create table user_relationship(  
        id int primary key not null unique auto_increment,  
        user_id int unsigned not null,  
        target_user_id int unsigned not null  
        )charset=utf8;  
