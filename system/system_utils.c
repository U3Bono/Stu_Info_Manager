#include "../include/system/system_utils.h"

void input_info(Stu_Info *student)
{
    print_line("basic");
    printf("number:");
    scanf("%d", &(student->num));
    printf("name:");
    scanf("%s", student->name);
    printf("ID card:");
    scanf("%lld", &(student->id));
    printf("student type(0-2):");
    scanf("%d", &(student->stype));
    printf("college(0-11):");
    scanf("%d", &(student->ctype));
    printf("major:");
    scanf("%s", student->major);

    print_line("travel");
    printf("road(xx-xx-xx):");
    scanf("%s", student->trafo.road);
    printf("contact(xx,xx,xx):");
    scanf("%s", student->trafo.contact);

    print_line("back");
    printf("temperature:");
    scanf("%f", &(student->bacfo.temperature));
    printf("medical history:");
    scanf("%s", student->bacfo.medical_h);
    printf("has symptoms(0,1)?");
    scanf("%d", &(student->bacfo.symptoms));
    printf("back date(xxxx-xx-xx):");
    scanf("%s", student->bacfo.back_date);
}

int search_info(FILE *fp, Stu_Info *search_stu, Search_Op op)
{
    if (fp == NULL || search_stu == NULL)
    {
        return -1;
    }

    fseek(fp, sizeof(int), 0); //跳过总数到数据段
    Stu_Info read_stu;
    for (int i = 0; (fread(&read_stu, sizeof(Stu_Info), 1, fp)) == 1; i++)
    {
        switch (op)
        {
        case NUMBER:
            if (search_stu->num == read_stu.num)
            {
                *(search_stu) = read_stu;
                return read_stu.num > 0 ? i : -1;
            }
            break;
        case NAME:
            if (strcmp(search_stu->name, read_stu.name) == 0)
            {
                *(search_stu) = read_stu;
                return read_stu.num > 0 ? i : -1;
            }
            break;
        case ID:
            if (search_stu->id == read_stu.id)
            {
                *(search_stu) = read_stu;
                return read_stu.num > 0 ? i : -1;
            }
            break;
        default:
            return -1;
        }
    }
    return -1;
}

int init_stu(Stu_Info *stu)
{
    if (stu == NULL)
    {
        return 0;
    }
    stu->num = 0;
    strcat(stu->name, "");
    stu->id = 0;
    stu->stype = 0;
    stu->ctype = 0;
    strcat(stu->trafo.road, "");
    strcat(stu->trafo.contact, "");
    stu->bacfo.temperature = 0;
    strcat(stu->bacfo.medical_h, "");
    stu->bacfo.symptoms = 0;
    strcat(stu->bacfo.back_date, "");
    return 1;
}

Stu_Info *get_list(char *fname, int *total)
{
    if (fname == NULL || total == NULL)
    {
        return NULL;
    }
    FILE *fp;
    if ((fp = fopen(fname, "rb")) == NULL)
    {
        return NULL;
    }
    fread(total, sizeof(int), 1, fp);                       //读入总数
    Stu_Info *stu_list = malloc(sizeof(Stu_Info) * *total); //分配内存
    Stu_Info read_stu;
    for (int i = 0; fread(&read_stu, sizeof(Stu_Info), 1, fp) == 1;)
    {
        if (read_stu.num > 0) //写入信息
        {
            *(stu_list + i) = read_stu;
            i++;
        }
    }

    return stu_list;
}

int save_list(char *fname, Stu_Info *stu_list, int length)
{
    if (fname == NULL || stu_list == NULL)
    {
        return 0;
    }
    FILE *fp;
    if ((fp = fopen(fname, "w")) == NULL)
    {
        return 0;
    }

    fprintf(fp, "number\t");
    fprintf(fp, "name\t");
    fprintf(fp, "id\t");
    fprintf(fp, "student type\t");
    fprintf(fp, "college\t\t");
    fprintf(fp, "major\t");
    fprintf(fp, "road\t\t");
    fprintf(fp, "contact\t\t");
    fprintf(fp, "temperature\t");
    fprintf(fp, "medical history\t\t");
    fprintf(fp, "symptoms\t");
    fprintf(fp, "back date\n");

    Stu_Info stu;
    char stype[10] = "";
    char ctype[20] = "";
    for (int i = 0; i < length; i++)
    {
        stu = *(stu_list + i);
        fprintf(fp, "%d\t", stu.num);
        fprintf(fp, "%s\t", stu.name);
        fprintf(fp, "%lld\t", stu.id);
        get_stype(stype, stu.stype);
        fprintf(fp, "%s\t\t", stype);
        get_college(ctype, stu.ctype);
        fprintf(fp, "%s\t", ctype);
        fprintf(fp, "%s\t", stu.major);
        fprintf(fp, "%s\t", stu.trafo.road);
        fprintf(fp, "%s\t\t", stu.trafo.contact);
        fprintf(fp, "%.1f\t\t", stu.bacfo.temperature);
        fprintf(fp, "%s\t\t\t", stu.bacfo.medical_h);
        fprintf(fp, "%d\t\t", stu.bacfo.symptoms);
        fprintf(fp, "%s\n", stu.bacfo.back_date);
    }

    fclose(fp);
    return 1;
}