#ifndef _stu_info_h
#define _stu_info_h

#include <string.h>

typedef struct
{
    char road[200];    //路途（格式xx-xx-xx）
    char contact[200]; //接触人员(格式xx,xx,xx)
} Travel_Info;

typedef struct
{
    float temperature;   //体温
    char medical_h[200]; //病史
    int symptoms;        //是否有相关症状
    char back_date[9];   //返校时间（格式xxxx-xx-xx）
} Back_Info;

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
    int num;               //学号
    char name[40];         //姓名
    unsigned long long id; //身份证id(主键)
    Stu_Type stype;        //学生类型
    Col_Type ctype;        //学院
    char major[40];        //专业
    Travel_Info trafo;     //旅行史
    Back_Info bacfo;       //返校信息
} Stu_Info;

int get_college(char *college, Col_Type ctype);
int get_stype(char *student, Stu_Type stype);

#endif