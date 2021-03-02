#include "../include/tools/serialize_stu.h"

int write_info(Stu_Info *node_list, unsigned int length, Col_Type type)
{
    if (length > LIMIT)
    {
        return 0;
    }
    FILE *fp;
    char *fname;
    if (!get_name(type, fname))
    {
        return 0;
    }

    if ((fp = fopen(fname, "wb")) == NULL)
    {
        return 0;
    }
    fwrite(&length, sizeof(int), 1, fp); //写入总数
    fseek(fp, sizeof(int), 0);
    fwrite(node_list, sizeof(Stu_Info), length, fp); //写入学生信息
    free(fname);
    fclose(fp);
    return 1;
}

int add_info(Stu_Info *node_list, unsigned int length, Col_Type type)
{
    FILE *fp;
    char *fname;
    if (!get_name(type, fname))
    {
        return 0;
    }
    int total = -1;
    if ((fp = fopen(fname, "rb")) == NULL)
    {
        return 0;
    }
    fread(&total, sizeof(int), 1, fp); //读入总数
    fclose(fp);
    total += length;
    if (total > LIMIT)
    {
        return 0;
    }
    if ((fp = fopen(fname, "wb")) == NULL)
    {
        return 0;
    }
    fwrite(&total, sizeof(int), 1, fp); //写入总数
    fseek(fp, sizeof(int), 0);
    fwrite(node_list, sizeof(Stu_Info), length, fp); //写入学生信息
    free(fname);
    fclose(fp);
    return 1;
}

int read_info(Stu_Info *node_list, unsigned int start, unsigned int length, int *total, Col_Type type)
{
    if (start + length > LIMIT)
    {
        printf("Out of limit.\n");
        return 0;
    }
    FILE *fp;
    char *fname;
    if (!get_name(type, fname))
    {
        printf("init file name error!\n");
        return 0;
    }
    if ((fp = fopen(fname, "rb")) == NULL)
    {
        return 0;
    }
    fread(total, sizeof(int), 1, fp); //读出总数
    fseek(fp, start * sizeof(Stu_Info) + sizeof(int), 0);
    int c;
    if ((c = fgetc(fp)) == EOF) //判断是否是末尾
    {
        return 0;
    }
    fseek(fp, start * sizeof(Stu_Info) + sizeof(int), 0);
    fread(node_list, sizeof(Stu_Info), length, fp); //读出学士信息
    free(fname);
    fclose(fp);
    return 1;
}

int get_name(Col_Type type, char *fname)
{
    fname = malloc(sizeof(char) * 30);
    switch (type)
    {
    case COMMUNICATION:
        strcat(fname, "communication_info");
        break;
    case COMPUTER:
        strcat(fname, "computer_info");
        break;
    case AUTOMATION:
        strcat(fname, "automation_info");
        break;
    case MANUFACTURE:
        strcat(fname, "manufacture_info");
        break;
    case PHOTOELECTRICITY:
        strcat(fname, "photoelectricity_info");
        break;
    case SOFTWARE:
        strcat(fname, "software_info");
        break;
    case SCIENCE:
        strcat(fname, "science_info");
        break;
    case MANAGEMENT:
        strcat(fname, "management_info");
        break;
    case MEDIA:
        strcat(fname, "media_info");
        break;
    case FOREIGH:
        strcat(fname, "forigh_info");
        break;
    case INTERNATIONAL:
        strcat(fname, "internationmal_info");
        break;
    case LAW:
        strcat(fname, "law_info");
        break;
    default:
        return 0;
    }
    return 1;
}