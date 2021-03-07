#ifndef _system_utils_h
#define _system_utils_h

#include "system_buf.h"
#include "../tools/printop.h"

typedef enum
{
    NUMBER, //学号
    NAME,   //姓名
    ID      //身份证
} Search_Op;

int init_stu(Stu_Info *stu);                                        //初始化学生信息
void input_info(Stu_Info *student);                                 //输入学生信息
int modify_info(Stu_Info *new_stu);                                 //修改学生信息
int search_info(Buf_Stu *buff, Stu_Info *search_stu, Search_Op op); //查询学生信息
void print_stu(Stu_Info stu);                                       //打印学生信息
void print_stu_basic(Stu_Info stu);
void print_stu_travel(Stu_Info stu);
void print_stu_back(Stu_Info stu);

#endif