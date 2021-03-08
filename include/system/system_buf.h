/**
 *  学生信息缓存 
 **/

#ifndef _system_buf_h
#define _system_buf_h

#include "../student/stu_main.h"
#include "../tools/stringop.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    void **stu_map;    //学生信息映射表（*:学生信息地址，**:学生信息）
    int length;        //映射表长，必须实时同步
    Col_Type col_type; //学院
    int stu_size;      //学生信息大小
} Buf_Stu;

void init_buf(Buf_Stu *buff);                     //初始化缓存
void destroy_buf(Buf_Stu *buff);                  //销毁缓存
int get_buf(Buf_Stu *buff, int length);           //扩展缓存
int get_list(Buf_Stu *buff);                      //读入到缓存
int set_list(Buf_Stu *buff);                      //写出到磁盘
int switch_buff(Buf_Stu *buff, Col_Type s_ctype); //切换列表缓存
int save_list(Buf_Stu *buff, char *fname);        //格式化输出到磁盘
int clean_buff(Buf_Stu *buff);                    //整理缓存

#endif