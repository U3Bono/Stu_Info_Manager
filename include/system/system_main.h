#ifndef _system_main_h
#define _system_main_h

#include "../information/stu_info.h"
#include "../login/login_main.h"
#include "../tools/printop.h"
#include <string.h>

void system_main();

static void exit_login();
static void search_stu();
static void add_stu();
static void delect_stu();
static void modify_stu();

#endif