#include "../include/system/system_utils.h"

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

int renew_info(Buf_Stu *buff)
{
    if (buff == NULL | buff->stu_map == NULL)
    {
        return 0;
    }

    Stu_Info *sp;
    int last = buff->length - 1; //指向最后一个有数据的地方
    for (int i = 0; i < last + 1; i++)
    {
        sp = *(buff->stu_map + i);
        if (sp == NULL) //无数据
        {
            while (i < last)
            {
                if ((sp = *(buff->stu_map + last)) != NULL) //填入最后一个数据
                {
                    *(buff->stu_map + i) = sp;
                    *(buff->stu_map + last) = NULL;
                    last--;
                    break;
                }
                last--;
            }
        }
        if (sp != NULL)
        {
            for (int j = i - 1; j > -1; j--)
            {
                if ((sp->num >= (*(buff->stu_map + j))->num))
                {
                    if (j + 1 != i)
                    {
                        *(buff->stu_map + j + 1) = sp;
                    }
                    break;
                }
                *(buff->stu_map + j + 1) = *(buff->stu_map + j); //后移
            }
        }
    }
    return 1;
}