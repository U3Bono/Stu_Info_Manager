#include "../include/system/system_utils.h"

void init_buf(Buf_Stu *buff)
{
    buff->stu_list = NULL;
    buff->length = 0;
    buff->col_type = 0;
}

void destroy_buf(Buf_Stu *buff)
{
    if (buff == NULL | buff->stu_list == NULL)
    {
        return;
    }
    free(buff->stu_list);
    init_buf(buff);
}

int enlarge_buf(Buf_Stu *buff, int length)
{
    if (buff == NULL | buff->stu_list == NULL)
    {
        return 0;
    }
    int new_length = buff->length + length;                    //扩展长度
    Stu_Info *new_list = malloc(sizeof(Buf_Stu) * new_length); //分配内存
    if (new_list == NULL)
    {
        return 0;
    }
    Stu_Info bastu;
    init_stu(&bastu);
    for (int i = 0; i < new_length; i++)
    {
        if (i < length)
        {
            *(new_list + i) = *(buff->stu_list + i);
        }
        else
        {
            *(new_list + i) = bastu;
        }
    }
    free(buff->stu_list);

    buff->stu_list = new_list;
    buff->length = new_length;
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
    buff->stu_list = malloc(sizeof(Stu_Info) * buff->length);  //分配缓存
    fread(buff->stu_list, sizeof(Stu_Info), buff->length, fp); //读入到缓存
    fclose(fp);
    return 1;
}

int set_list(Buf_Stu *buff)
{
    if (buff == NULL | buff->stu_list == NULL)
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
    Stu_Info stu;
    for (int i = 0; i < buff->length; i++)
    {
        stu = *(buff->stu_list + i);
        if (stu.num > 0) //未被标记删除的数据
        {
            total++;                               //统计总数
            fwrite(&stu, sizeof(Stu_Info), 1, fp); //写入学生信息
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

    if (buff->stu_list != NULL) //数据不为空
    {
        set_list(buff); //回写数据
        free(buff->stu_list);
        buff->stu_list = NULL;
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

    Stu_Info stu;
    for (int i = 0; i < buff->length; i++)
    {
        stu = *(buff->stu_list + i);
        if (stu.num > 0)
        {
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

    Stu_Info read_stu;
    for (int i = 0; i < buff->length; i++)
    {
        read_stu = *(buff->stu_list + i);
        if (read_stu.num > 0)
        {
            switch (op)
            {
            case NUMBER:
                if (search_stu->num == read_stu.num)
                {
                    *(search_stu) = read_stu;
                    return i;
                }
                break;
            case NAME:
                if (strcmp(search_stu->name, read_stu.name) == 0)
                {
                    *(search_stu) = read_stu;
                    return i;
                }
                break;
            case ID:
                if (search_stu->id == read_stu.id)
                {
                    *(search_stu) = read_stu;
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