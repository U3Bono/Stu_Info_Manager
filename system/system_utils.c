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
    Stu_Info read_stu;
    init_stu(&read_stu);
    rewind(fp);
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