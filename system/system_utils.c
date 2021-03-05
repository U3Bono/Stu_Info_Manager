#include "../include/system/system_utils.h"

void init_buf(Buf_Stu *buff)
{
    buff->stu_map = NULL;
    buff->length = 0;
    buff->col_type = 0;
}

void destroy_buf(Buf_Stu *buff)
{
    if (buff == NULL | buff->stu_map == NULL)
    {
        return;
    }
    Stu_Info *sp;
    for (int i = 0; i < buff->length; i++)
    {
        sp = *(buff->stu_map + i);
        free(sp); //清理学生信息缓存
    }
    free(buff->stu_map); //清理映射表
    init_buf(buff);
}

int enlarge_buf(Buf_Stu *buff, int length)
{
    if (buff == NULL | buff->stu_map == NULL)
    {
        return 0;
    }
    int new_length = buff->length + length;                        //扩展长度
    Stu_Info **new_table = malloc(sizeof(Buf_Stu *) * new_length); //分配内存
    if (new_table == NULL)
    {
        return 0;
    }

    for (int i = 0; i < new_length; i++)
    {
        if (i < buff->length)
        {
            *(new_table + i) = *(buff->stu_map + i); //复制地址
        }
        else
        {
            *(new_table + i) = NULL; //初始化新地址
        }
    }
    buff->length = new_length;
    buff->stu_map = new_table;

    return 1;
}

int get_list(Buf_Stu *buff)
{
    if (buff == NULL)
    {
        return 0;
    }
    FILE *fp;
    char fname[30] = "info_";
    get_college(fname, buff->col_type);
    if ((fp = fopen(fname, "rb")) == NULL)
    {
        return 0;
    }
    fread(&buff->length, sizeof(int), 1, fp);                  //读入总数
    buff->stu_map = malloc(sizeof(Stu_Info *) * buff->length); //分配映射表
    Stu_Info *sp;
    for (int i = 0; i < buff->length; i++)
    {
        sp = malloc(sizeof(Stu_Info));      //分配缓存
        fread(sp, sizeof(Stu_Info), 1, fp); //读入到缓存
        *(buff->stu_map + i) = sp;          //地址存放入映射表
    }
    fclose(fp);

    return 1;
}

int set_list(Buf_Stu *buff)
{
    if (buff == NULL | buff->stu_map == NULL)
    {
        return 0;
    }
    FILE *fp;
    char fname[30] = "info_";
    get_college(fname, buff->col_type);
    if ((fp = fopen(fname, "wb")) == NULL)
    {
        return 0;
    }
    int total = 0;
    fwrite(&total, sizeof(int), 1, fp); //初始化总数
    Stu_Info *sp;
    for (int i = 0; i < buff->length; i++)
    {
        sp = *(buff->stu_map + i);
        if (sp != NULL) //未被标记删除的数据
        {
            total++;                             //统计总数
            fwrite(sp, sizeof(Stu_Info), 1, fp); //写入学生信息
        }
    }
    rewind(fp);
    fwrite(&total, sizeof(int), 1, fp); //更新总数
    fclose(fp);
    return 1;
}

int switch_buff(Buf_Stu *buff, Col_Type s_ctype)
{
    if (buff == NULL)
    {
        return 0;
    }

    if (buff->stu_map != NULL) //数据不为空
    {
        set_list(buff);    //回写数据
        destroy_buf(buff); //清空缓存
    }
    buff->col_type = s_ctype; //切换院校
    get_list(buff);           //读出数据

    return 1;
}

int save_list(Buf_Stu *buff, char *fname)
{
    if (buff == NULL)
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

    Stu_Info *sp;
    for (int i = 0; i < buff->length; i++)
    {
        sp = *(buff->stu_map + i);
        if (sp != NULL)
        {
            fprintf(fp, "%6d", sp->num);
            fprintf(fp, "%16s", sp->name);
            fprintf(fp, "%6lld", sp->id);
            char stype[10] = "";
            get_stype(stype, sp->stype);
            fprintf(fp, "%16s", stype);
            char ctype[20] = "";
            get_college(ctype, sp->ctype);
            fprintf(fp, "%20s", ctype);
            fprintf(fp, "%10s", sp->major);
            fprintf(fp, "%20s", sp->trafo.road);
            fprintf(fp, "%20s", sp->trafo.contact);
            fprintf(fp, "%16.1f", sp->bacfo.temperature);
            fprintf(fp, "%26s", sp->bacfo.medical_h);
            fprintf(fp, "%20d", sp->bacfo.symptoms);
            fprintf(fp, "%19s\n", sp->bacfo.back_date);
        }
    }

    fclose(fp);
    return 1;
}

int search_info(Buf_Stu *buff, Stu_Info *search_stu, Search_Op op)
{
    if (buff == NULL || search_stu == NULL)
    {
        return -1;
    }

    if (buff->col_type != search_stu->ctype) //院校不同则切换缓存
    {
        switch_buff(buff, search_stu->ctype);
    }

    Stu_Info *sp;
    for (int i = 0; i < buff->length; i++)
    {
        sp = *(buff->stu_map + i);
        if (sp != NULL)
        {
            switch (op)
            {
            case NUMBER:
                if (search_stu->num == sp->num)
                {
                    *search_stu = *sp;
                    return i;
                }
                break;
            case NAME:
                if (strcmp(search_stu->name, sp->name) == 0)
                {
                    *(search_stu) = *sp;
                    return i;
                }
                break;
            case ID:
                if (search_stu->id == sp->id)
                {
                    *(search_stu) = *sp;
                    return i;
                }
                break;
            default:
                return -1;
            }
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
    stu->num = -1;
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