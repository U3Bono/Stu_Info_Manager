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

int init_stu_basic(void *stu);
int input_info_basic(void *stu);
int modify_info_basic(void *stu);
int print_stu_basic(void *stu);
int save_stu_basic_title(FILE *fp);
int save_stu_basic_value(FILE *fp, void *stu);
int search_info_basic(Stu_Basic **stu_map, int length, Stu_Basic *stu_basic, Search_Op op);

#endif