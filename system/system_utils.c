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

    switch_buff(buff, search_stu->ctype);

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

int clean_buff(Buf_Stu *buff)
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
        if (sp == NULL) //清理空闲缓存
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
            if (sp == NULL) //之后的缓存都为空，整理完成
            {
                break;
            }
        }

        if (i > 0) //插入排序
        {
            if ((sp->num < (*(buff->stu_map + i - 1))->num))
            {
                *(buff->stu_map + i) = *(buff->stu_map + i - 1);
                for (int j = i - 1; j > 0; j--)
                {
                    if ((sp->num >= (*(buff->stu_map + j - 1))->num)) //大于等于上一个数
                    {
                        *(buff->stu_map + j) = sp;
                        break;
                    }
                    *(buff->stu_map + j) = *(buff->stu_map + j - 1); //上一个数后移
                }
            }
        }
    }
    return 1;
}