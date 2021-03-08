#ifndef _stu_info_basic_h
#define _stu_info_basic_h

#include "stu_info_epid.h"
#include "../tools/stringop.h"

typedef enum
{
    BACHELOR, //学士
    MASTER,   //硕士
    DOCTOR    //博士
} Stu_Type;

typedef enum
{
    COMMUNICATION,    //通讯学院
    COMPUTER,         //计算机学院
    AUTOMATION,       //自动化学院
    MANUFACTURE,      //先进制造学院
    PHOTOELECTRICITY, //光电学院
    SOFTWARE,         //软件学院
    SCIENCE,          //理学院
    MANAGEMENT,       //经管学院
    MEDIA,            //传媒学院
    FOREIGH,          //外语学院
    INTERNATIONAL,    //国际学院
    LAW               //安法学院
} Col_Type;

typedef struct
{
    int num;               //学号(主键)
    char name[40];         //姓名
    unsigned long long id; //身份证号
    Stu_Type stype;        //学生类型
    Col_Type ctype;        //学院
    char major[40];        //专业
} Stu_Basic;

int get_college(char *college, Col_Type ctype);
int get_stype(char *student, Stu_Type stype);

#endif