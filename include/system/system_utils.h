#ifndef _system_utils_h
#define _system_utils_h

#include "system_buf.h"

typedef enum
{
    NUMBER, //学号
    NAME,   //姓名
    ID      //身份证
} Search_Op;

int init_stu(Stu_Info *stu);                                        //初始化学生信息
void input_info(Stu_Info *student);                                 //输入学生信息
int search_info(Buf_Stu *buff, Stu_Info *search_stu, Search_Op op); //根据属性查询学生信息,返回位置
int clean_buff(Buf_Stu *buff);                                      //整理学生信息

#endif