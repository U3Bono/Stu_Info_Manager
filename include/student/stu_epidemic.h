/**
 *  学生的疫情信息
 **/

#ifndef _stu_epidemic_h
#define _stu_epidemic_h

#include "../information/stu_info_epid.h"
#include "../tools/printop.h"
#include "../tools/stringop.h"

int init_stu_epid(void *stu);      //初始化
int input_info_epid(void *stu);    //输入
int modify_info_epid(void *stu);   //修改
int print_stu_epid(void *stu);     //打印
int save_stu_epid_title(FILE *fp); //格式化保存
int save_stu_epid_value(FILE *fp, void *stu);

#endif