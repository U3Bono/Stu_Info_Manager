#ifndef _system_utils_h
#define _system_utils_h

#include "../information/stu_info.h"
#include "../tools/printop.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef enum
{
    NUMBER, //学号
    NAME,   //姓名
    ID      //身份证
} Search_Op;

void input_info(Stu_Info *student);
int search_info(FILE *fp, Stu_Info *search_stu, Search_Op op); //根据属性查询学生信息,返回位置
int init_stu(Stu_Info *stu);                                   //初始化学生信息
Stu_Info *get_list(char *fname, int *total);                   //读入到表格
int save_list(char *fname, Stu_Info *stu_list, int length);    //输出到文件

#endif