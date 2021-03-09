/**
 *  虚拟学生信息管理
 *  外部调用只需要传入学生信息地址
 *  学生信息类型添加：Info_Type 及 对应操作函数数组
 **/

#ifndef _stu_main_h
#define _stu_main_h

#include "stu_basic.h"
#include "stu_epidemic.h"

typedef enum
{
    BASIC,
    EPIDEMIC
} Info_Type;

static Info_Type info_type; //操作信息类型

static int (*init_p[])(void *) = {init_stu_basic, init_stu_epid};                //初始化函数数组
static int (*input_p[])(void *) = {input_info_basic, input_info_epid};           //输入函数数组
static int (*modify_p[])(void *) = {modify_info_basic, modify_info_epid};        //修改函数数组
static int (*print_p[])(void *) = {print_stu_basic, print_stu_epid};             //打印函数数组
static int (*savet_p[])(FILE *fp) = {save_stu_basic_title, save_stu_epid_title}; //保存函数数组
static int (*savev_p[])(FILE *fp, void *) = {save_stu_basic_value, save_stu_epid_value};

void choose_itype(Info_Type itype); //选择信息类型
void get_itype(char *s);            //获得信息类型名
int get_ssize();                    //获取学生信息大小

int init_stu(Stu_Basic *stu);    //初始化
int input_info(Stu_Basic *stu);  //输入
int modify_info(Stu_Basic *stu); //修改
int print_stu(Stu_Basic *stu);   //打印
int save_stu_title(FILE *fp);    //格式化保存
int save_stu_value(FILE *fp, Stu_Basic *stu);
int search_info(Stu_Basic **stu_map, int length, Stu_Basic *stu, Search_Op op); //查询

#endif