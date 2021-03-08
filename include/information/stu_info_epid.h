#ifndef _stu_info_epid_h
#define _stu_info_epid_h

typedef struct
{
    char road[200];      //路途（格式xx-xx-xx）
    char contact[200];   //接触人员(格式xx,xx,xx)
    float temperature;   //体温
    char medical_h[200]; //病史
    int symptoms;        //是否有相关症状
    char back_date[9];   //返校时间（格式xxxx-xx-xx）
} Stu_Epid;

#endif