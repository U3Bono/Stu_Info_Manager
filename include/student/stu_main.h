/**
 *  虚拟学生信息管理
 *  外部调用只需要传入学生信息地址
 *  所有的学生信息类型需要添加到对应的信息管理函数
 **/

#ifndef _stu_main_h
#define _stu_main_h

#include "stu_basic.h"
#include "stu_epidemic.h"

typedef enum
{
    EPIDEMIC
} Info_Type;

static Info_Type info_type; //操作信息类型

void choose_itype(Info_Type itype); //选择信息类型
void get_itype(char *s);            //获得信息类型名
int get_ssize();                    //获取学生信息大小

int input_info(Stu_Basic *stu);  //输入
int modify_info(Stu_Basic *stu); //修改
void print_stu(Stu_Basic *stu);  //打印
int save_stu_title(FILE *fp);    //格式化保存
int save_stu_value(FILE *fp, Stu_Basic *stu);
int init_stu(Stu_Basic *stu);                                                   //初始化
int search_info(Stu_Basic **stu_map, int length, Stu_Basic *stu, Search_Op op); //查询

#endif