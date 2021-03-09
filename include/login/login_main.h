/**
 * 登陆系统
 **/

#ifndef _login_main_h
#define _login_main_h

#include "../information/user_info.h"
#include "../system/system_main.h"
#include "../tools/printop.h"
#include "../tools/stringop.h"

User_Info user; //用户登陆信息

void login_main();

int login(User_Info *login_user); //登陆

void init_user();                 //初始化用户
void print_user(User_Info user); //打印用户信息

#endif