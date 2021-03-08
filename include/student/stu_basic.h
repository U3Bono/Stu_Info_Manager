/**
 *  学生的基本信息
 **/

#ifndef _stu_basic_h
#define _stu_basic_h

#include "../information/stu_info_basic.h"
#include "../tools/printop.h"
#include "../tools/stringop.h"

int init_stu_basic(Stu_Basic *stu_basic);
int input_info_basic(Stu_Basic *stu_basic);
int modify_info_basic(Stu_Basic *stu_basic);
void print_stu_basic(Stu_Basic stu_basic);
int save_stu_basic_title(FILE *fp);
int save_stu_basic_value(FILE *fp, Stu_Basic *stu_basic);

#endif