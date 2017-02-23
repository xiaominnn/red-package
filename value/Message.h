/*
 * 关于消息的一些定义
 */
#ifndef MESSAGE_H
#define MESSAGE_H
/*消息类型*/
enum MessageType
{
    message_register = 1,
    message_login,
    message_insert_friend,
    message_delete_friend,
    message_insert_group,
    message_delete_group,
    message_chat,
    message_send_redpackage,
    message_recv_redpackage

};
#endif
