#ifndef _system_buf_h
#define _system_buf_h

#include "../information/stu_info.h"
#include "../tools/printop.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
    Stu_Info **stu_map; //学生信息映射表（*:学生信息地址，**:学生信息）
    int length;         //映射表长，必须实时同步
    Col_Type col_type;  //学院
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