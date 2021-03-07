#ifndef _login_main_h
#define _login_main_h

#include "../information/user_info.h"
#include "../tools/printop.h"
#include "../system/system_main.h"

#include <string.h>

User_Info user; //用户登陆信息

void login_main();

int login(User_Info *login_user); //登陆

void initUser();                 //初始化用户
void print_user(User_Info user); //打印用户信息

#endif