#ifndef _printop_h
#define _printop_h

#include "../information/user_info.h"
#include "../information/stu_info.h"
#include "../information/system_info.h"

#include <stdio.h>

void print_logo();

void print_star(char *title);
void print_line(char *title);
void print_pause(char *notice);
void bool_printf(int bl);

void print_user(User_Info user);
void print_stu(Stu_Info stu);
void print_stu_basic(Stu_Info stu);
void print_stu_travel(Stu_Info stu);
void print_stu_back(Stu_Info stu);

void flushiobuf();

#endif