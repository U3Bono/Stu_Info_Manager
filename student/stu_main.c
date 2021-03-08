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

int init_stu(void *stu)
{
    if (stu == NULL)
    {
        return 0;
    }

    init_stu_basic(stu);

    switch (info_type)
    {
    case EPIDEMIC:
        init_stu_epid(stu + sizeof(Stu_Basic));
        break;

    default:
        break;
    }

    return 1;
}

int input_info(void *stu)
{
    if (stu == NULL)
    {
        return 0;
    }

    input_info_basic(stu);

    switch (info_type)
    {
    case EPIDEMIC:
        input_info_epid(stu + sizeof(Stu_Basic));
        break;

    default:
        break;
    }

    return 1;
}

int modify_info(void *stu)
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
            modify_info_epid(stu + sizeof(Stu_Basic));
            break;

        default:
            break;
        }
    }

    return 1;
}

void print_stu(void *stu)
{
    print_line("basic");

    print_stu_basic(*(Stu_Basic *)stu);

    switch (info_type)
    {
    case EPIDEMIC:
        print_line("epidemic");
        print_stu_epid(*(Stu_Epid *)(stu + sizeof(Stu_Basic)));
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

int save_stu_value(FILE *fp, void *stu)
{
    if (fp == NULL || stu == NULL)
    {
        return 0;
    }
    save_stu_basic_value(fp, stu);

    switch (info_type)
    {
    case EPIDEMIC:
        save_stu_epid_value(fp, stu + sizeof(Stu_Basic));
        break;
        
    default:
        break;
    }

    return 1;
}

int search_info(void **stu_map, int length, void *stu, Search_Op op)
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

    void *sp;
    for (int i = 0; i < length; i++)
    {
        sp = *(stu_map + i);
        if (sp != NULL)
        {
            switch (op)
            {
            case NUMBER:
                if (((Stu_Basic *)stu)->num == ((Stu_Basic *)sp)->num)
                {
                    memcpy(stu, sp, stu_size);
                    return i;
                }
                break;
            case NAME:
                if (strcmp(((Stu_Basic *)stu)->name, ((Stu_Basic *)sp)->name) == 0)
                {
                    memcpy(stu, sp, stu_size);
                    return i;
                }
                break;
            case ID:
                if (((Stu_Basic *)stu)->id == ((Stu_Basic *)sp)->id)
                {
                    memcpy(stu, sp, stu_size);
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