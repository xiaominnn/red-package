# 微信红包项目数据库设计   
## 1.目录   
[TOC]   
## 2.数据库使用平台   
ubuntu15.10下使用**mysql**数据库进行数据的存储
## 3.数据库表的设计   
### 3.1数据库的名字及使用命令
#### 3.1.1登陆mysql数据库

'$mysql -uroot -p'   
然后输入数据库root用户密码

2. 查看所有的数据库：
>
$show databases;
3. 建立数据库名为chat的数据库:
>
$create database chat;
4. 选择数据库名为chat的数据库：
>
$use chat;
###3.2数据库表的设计及建立
