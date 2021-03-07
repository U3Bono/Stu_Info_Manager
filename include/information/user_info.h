#ifndef _user_info_h
#define _user_info_h

typedef struct
{
    char username[20]; //账户
    char password[20]; //密码
    int type;          //用户类型（0为root用户）
} User_Info;

#endif