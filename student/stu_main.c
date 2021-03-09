#include "../include/student/stu_main.h"

void choose_itype(Info_Type itype)
{
    info_type = itype;
}

void get_itype(char *s)
{
    switch (info_type)
    {
    case EPIDEMIC:
        strcat(s, "epidemic");
        break;

    default:
        break;
    }
}

int get_ssize()
{
    int size = sizeof(Stu_Basic);

    switch (info_type)
    {
    case EPIDEMIC:
        size += sizeof(Stu_Epid);
        break;

    default:
        break;
    }
    return size;
}

int init_stu(Stu_Basic *stu)
{
    if (stu == NULL)
    {
        return 0;
    }

    init_stu_basic(stu);

    switch (info_type)
    {
    case EPIDEMIC:
        init_stu_epid((void *)stu + sizeof(Stu_Basic));
        break;

    default:
        break;
    }

    return 1;
}

int input_info(Stu_Basic *stu)
{
    if (stu == NULL)
    {
        return 0;
    }

    input_info_basic(stu);

    switch (info_type)
    {
    case EPIDEMIC:
        input_info_epid((void *)stu + sizeof(Stu_Basic));
        break;

    default:
        break;
    }

    return 1;
}

int modify_info(Stu_Basic *stu)
{
    if (stu == NULL)
    {
        return 0;
    }

    print_star(" Options ");
    printf("0.basic info\n");
    char iname[20] = "";
    get_itype(iname);
    strcat(iname, " info");
    printf("1.%s\n", iname);
    int op;
    print_star("Select");
    do
    {
        scanf("%d", &op);
    } while (op != 0 && op != 1);

    if (op == 0)
    {
        modify_info_basic(stu);
    }
    else
    {
        switch (info_type)
        {
        case EPIDEMIC:
            modify_info_epid((void *)stu + sizeof(Stu_Basic));
            break;

        default:
            break;
        }
    }

    return 1;
}

void print_stu(Stu_Basic *stu)
{
    print_line("basic");

    print_stu_basic(*(Stu_Basic *)stu);

    switch (info_type)
    {
    case EPIDEMIC:
        print_line("epidemic");
        print_stu_epid(*(Stu_Epid *)((void *)stu + sizeof(Stu_Basic)));
        break;

    default:
        break;
    }

    print_line(NULL);
}

int save_stu_title(FILE *fp)
{
    if (fp == NULL)
    {
        return 0;
    }
    save_stu_basic_title(fp);

    switch (info_type)
    {
    case EPIDEMIC:
        save_stu_epid_title(fp);
        break;

    default:
        break;
    }

    return 1;
}

int save_stu_value(FILE *fp, Stu_Basic *stu)
{
    if (fp == NULL || stu == NULL)
    {
        return 0;
    }
    save_stu_basic_value(fp, stu);

    switch (info_type)
    {
    case EPIDEMIC:
        save_stu_epid_value(fp, (void *)stu + sizeof(Stu_Basic));
        break;

    default:
        break;
    }

    return 1;
}

int search_info(Stu_Basic **stu_map, int length, Stu_Basic *stu, Search_Op op)
{
    if (stu_map == NULL || stu == NULL)
    {
        return -1;
    }

    int stu_size = sizeof(Stu_Basic);
    switch (info_type)
    {
    case EPIDEMIC:
        stu_size += sizeof(Stu_Epid);
        break;

    default:
        break;
    }

    int position = search_info_basic(stu_map, length, stu, op);
    if (position != -1)
    {
        memcpy(stu, *(stu_map + position), stu_size);
    }

    return position;
}