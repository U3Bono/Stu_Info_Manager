#ifndef _printop_h
#define _printop_h

#include "../information/user_info.h"
#include "../information/stu_info.h"

#include <stdio.h>

void print_logo();
void print_star(char *title);
void print_line(char *title);

void print_user(User_Info user);

#endif