/**
 *  学生所有信息综合管理
 *  （信息类型添加需要实现basic方法，并添加到管理函数中）
 **/

#ifndef _stu_main_h
#define _stu_main_h

#include "stu_basic.h"
#include "stu_epidemic.h"

typedef enum
{
    EPIDEMIC
} Info_Type;

typedef enum
{
    NUMBER = 1, //学号
    NAME,       //姓名
    ID          //身份证
} Search_Op;

static Info_Type info_type; //操作信息类型

void choose_itype(Info_Type itype); //选择信息类型
void get_itype(char *s);            //获得信息类型名
int get_ssize();                    //获取学生信息大小

int input_info(void *stu);    //输入
int modify_info(void *stu);   //修改
void print_stu(void *stu);    //打印
int save_stu_title(FILE *fp); //格式化保存
int save_stu_value(FILE *fp, void *stu);
int init_stu(void *stu);                                              //初始化
int search_info(void **stu_map, int length, void *stu, Search_Op op); //查询

#endif