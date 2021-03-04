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

    fprintf(fp, "%6s", "number");
    fprintf(fp, "%16s", "name");
    fprintf(fp, "%6s", "id");
    fprintf(fp, "%16s", "student type");
    fprintf(fp, "%20s", "college");
    fprintf(fp, "%10s", "major");
    fprintf(fp, "%20s", "road");
    fprintf(fp, "%20s", "contact");
    fprintf(fp, "%16s", "temperature");
    fprintf(fp, "%26s", "medical history");
    fprintf(fp, "%20s", "symptoms");
    fprintf(fp, "%20s", "back date\n");

    Stu_Info stu;
    for (int i = 0; i < length; i++)
    {
        stu = *(stu_list + i);
        fprintf(fp, "%6d", stu.num);
        fprintf(fp, "%16s", stu.name);
        fprintf(fp, "%6lld", stu.id);
        char stype[10] = "";
        get_stype(stype, stu.stype);
        fprintf(fp, "%16s", stype);
        char ctype[20] = "";
        get_college(ctype, stu.ctype);
        fprintf(fp, "%20s", ctype);
        fprintf(fp, "%10s", stu.major);
        fprintf(fp, "%20s", stu.trafo.road);
        fprintf(fp, "%20s", stu.trafo.contact);
        fprintf(fp, "%16.1f", stu.bacfo.temperature);
        fprintf(fp, "%26s", stu.bacfo.medical_h);
        fprintf(fp, "%20d", stu.bacfo.symptoms);
        fprintf(fp, "%19s\n", stu.bacfo.back_date);
    }

    fclose(fp);
    return 1;
}