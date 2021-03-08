/**
 *  学生的疫情信息
 **/

#ifndef _stu_epidemic_h
#define _stu_epidemic_h

#include "../information/stu_info_epid.h"
#include "../tools/printop.h"
#include "../tools/stringop.h"

int init_stu_epid(Stu_Epid *stu_epid); //初始化
int input_info_epid(Stu_Epid *stu_epid); //输入
int modify_info_epid(Stu_Epid *stu_epid); //修改
void print_stu_epid(Stu_Epid stu_epid); //打印
int save_stu_epid_title(FILE *fp); //格式化保存
int save_stu_epid_value(FILE *fp, Stu_Epid *stu_epid);

#endif