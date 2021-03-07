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

int modify_info(Stu_Info *new_stu)
{
    if (new_stu == NULL)
    {
        return 0;
    }

    char *options[] = {"name", "type", "major",
                       "road", "contact", "temperature", "medical histroy", "has symptoms?", "back date"};
    print_star(" Options ");
    for (int i = 0; i < 9; i++) //打印选项
    {
        printf("%d.%s\n", i, *(options + i));
    }
    print_star("Select");
    int op;
    scanf("%d", &op);
    if (op == 9)
    {
        printf("%s:", *(options + op));
    }
    else
    {
        printf("new %s:", *(options + op));
    }

    switch (op)
    {
    case 0:
        scanf("%s", new_stu->name);
        break;
    case 1:
        scanf("%d", &(new_stu->stype));
        break;
    case 2:
        scanf("%s", new_stu->major);
        break;
    case 3:
        scanf("%s", new_stu->trafo.road);
        break;
    case 4:
        scanf("%s", new_stu->trafo.contact);
        break;
    case 5:
        scanf("%f", &(new_stu->bacfo.temperature));
        break;
    case 6:
        scanf("%s", new_stu->bacfo.medical_h);
        break;
    case 7:
        scanf("%d", &(new_stu->bacfo.symptoms));
        break;
    case 8:
        scanf("%s", new_stu->bacfo.back_date);
        break;
    default:
        break;
    }
    return 1;
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

void print_stu(Stu_Info stu)
{
    print_line("basic");
    print_stu_basic(stu);
    print_line("travel");
    print_stu_travel(stu);
    print_line("back");
    print_stu_back(stu);
    print_line(NULL);
}

void print_stu_basic(Stu_Info stu)
{
    printf("number:%d\n", stu.num);
    printf("name:%s\n", stu.name);
    printf("id:%lld\n", stu.id);
    char stype[10] = "";
    get_stype(stype, stu.stype);
    printf("type:%s\n", stype);
    char ctype[20] = "";
    get_college(ctype, stu.ctype);
    printf("college:%s\n", ctype);
    printf("major:%s\n", stu.major);
}

void print_stu_travel(Stu_Info stu)
{
    printf("road:%s\n", stu.trafo.road);
    printf("contact:%s\n", stu.trafo.contact);
}

void print_stu_back(Stu_Info stu)
{
    printf("temperature:%.1f\n", stu.bacfo.temperature);
    printf("medical histroy:%s\n", stu.bacfo.medical_h);
    printf("has symptoms?");
    bool_printf(stu.bacfo.symptoms);
    printf("back date:%s\n", stu.bacfo.back_date);
}
