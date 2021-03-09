/**
 *  学生的基本信息
 **/

#ifndef _stu_basic_h
#define _stu_basic_h

#include "../information/stu_info_basic.h"
#include "../tools/printop.h"
#include "../tools/stringop.h"

typedef enum
{
    NUMBER = 1, //学号
    NAME,       //姓名
    ID          //身份证
} Search_Op;

int init_stu_basic(Stu_Basic *stu_basic);
int input_info_basic(Stu_Basic *stu_basic);
int modify_info_basic(Stu_Basic *stu_basic);
int search_info_basic(Stu_Basic **stu_map, int length, Stu_Basic *stu_basic, Search_Op op);
void print_stu_basic(Stu_Basic stu_basic);
int save_stu_basic_title(FILE *fp);
int save_stu_basic_value(FILE *fp, Stu_Basic *stu_basic);

#endif