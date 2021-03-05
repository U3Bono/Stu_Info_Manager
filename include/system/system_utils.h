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

typedef struct
{
    Stu_Info *stu_list; //学生信息顺序表
    int length;         //顺序表长
    Col_Type col_type;  //学院
} Buf_Stu;

void init_buf(Buf_Stu *buff);                                       //初始化缓存
void destroy_buf(Buf_Stu *buff);                                    //销毁缓存
int enlarge_buf(Buf_Stu *buff, int length);                         //扩展缓存
int get_list(Buf_Stu *buff);                                        //读入到缓存
int set_list(Buf_Stu *buff);                                        //写出到磁盘
int switch_buff(Buf_Stu *buff, Col_Type s_ctype);                   //切换列表缓存
int save_list(Buf_Stu *buff, char *fname);                          //格式化输出到磁盘
int search_info(Buf_Stu *buff, Stu_Info *search_stu, Search_Op op); //根据属性查询学生信息,返回位置
int init_stu(Stu_Info *stu);                                        //初始化学生信息
void input_info(Stu_Info *student);                                 //输入学生信息

#endif