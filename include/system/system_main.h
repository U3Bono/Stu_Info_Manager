#ifndef _system_main_h
#define _system_main_h

#include "../information/stu_info.h"
#include "../login/login_main.h"
#include "../tools/printop.h"
#include "system_utils.h"

void system_main();

void exit_sys(Buf_Stu *buff);
void exit_login(Buf_Stu *buff);
void search_stu(Buf_Stu *buff);
void add_stu(Buf_Stu *buff);
void delect_stu(Buf_Stu *buff);
void modify_stu(Buf_Stu *buff);
void clear_list(Buf_Stu *buff);
void print_list(Buf_Stu *buff);
void output_info(Buf_Stu *buff);

#endif