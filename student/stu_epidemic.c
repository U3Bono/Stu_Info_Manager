#include "../include/student/stu_epidemic.h"

int init_stu_epid(Stu_Epid *stu_epid)
{
    if (stu_epid == NULL)
    {
        return 0;
    }
    strcat(stu_epid->road, "");
    strcat(stu_epid->contact, "");
    stu_epid->temperature = 0;
    strcat(stu_epid->medical_h, "");
    stu_epid->symptoms = 0;
    strcat(stu_epid->back_date, "");
    return 1;
}

int input_info_epid(Stu_Epid *stu_epid)
{
    if (stu_epid == NULL)
    {
        return 0;
    }
    print_line("epidemic");
    printf("road(xx-xx-xx):");
    scanf("%s", stu_epid->road);
    printf("contact(xx,xx,xx):");
    scanf("%s", stu_epid->contact);
    printf("temperature:");
    scanf("%f", &(stu_epid->temperature));
    printf("medical history:");
    scanf("%s", stu_epid->medical_h);
    printf("has symptoms(0,1)?");
    scanf("%d", &(stu_epid->symptoms));
    printf("back date(xxxx-xx-xx):");
    scanf("%s", stu_epid->back_date);
    return 1;
}

int modify_info_epid(Stu_Epid *stu_epid)
{
    if (stu_epid == NULL)
    {
        return 0;
    }
    char *op_arr[] = {"road", "contact", "temperature", "medical histroy", "has symptoms?", "back date"};
    print_star(" Options ");
    for (int i = 0; i < 6; i++) //打印选项
    {
        printf("%d.%s\n", i, op_arr[i]);
    }
    print_star(" Select ");
    int op;
    scanf("%d", &op);
    printf("new:");
    switch (op)
    {
    case 0:
        scanf("%s", stu_epid->road);
        break;
    case 1:
        scanf("%s", stu_epid->contact);
        break;
    case 2:
        scanf("%f", &(stu_epid->temperature));
        break;
    case 3:
        scanf("%s", stu_epid->medical_h);
        break;
    case 4:
        scanf("%d", &(stu_epid->symptoms));
        break;
    case 5:
        scanf("%s", stu_epid->back_date);
        break;
    default:
        break;
    }
    return 1;
}

void print_stu_epid(Stu_Epid stu_epid)
{
    printf("road:%s\n", stu_epid.road);
    printf("contact:%s\n", stu_epid.contact);
    printf("temperature:%.1f\n", stu_epid.temperature);
    printf("medical histroy:%s\n", stu_epid.medical_h);
    printf("has symptoms?");
    bool_printf(stu_epid.symptoms);
    printf("back date:%s\n", stu_epid.back_date);
}

int save_stu_epid_title(FILE *fp)
{
    if (fp == NULL)
    {
        return 0;
    }
    fprintf(fp, "%20s", "road");
    fprintf(fp, "%20s", "contact");
    fprintf(fp, "%16s", "temperature");
    fprintf(fp, "%26s", "medical history");
    fprintf(fp, "%20s", "symptoms");
    fprintf(fp, "%20s", "back date\n");
    return 1;
}

int save_stu_epid_value(FILE *fp, Stu_Epid *stu_epid)
{
    if (fp == NULL || stu_epid == NULL)
    {
        return 0;
    }
    fprintf(fp, "%20s", stu_epid->road);
    fprintf(fp, "%20s", stu_epid->contact);
    fprintf(fp, "%16.1f", stu_epid->temperature);
    fprintf(fp, "%26s", stu_epid->medical_h);
    fprintf(fp, "%20d", stu_epid->symptoms);
    fprintf(fp, "%19s\n", stu_epid->back_date);
    return 1;
}