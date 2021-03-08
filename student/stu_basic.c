#include "../include/student/stu_basic.h"

int init_stu_basic(Stu_Basic *stu_basic)
{
    if (stu_basic == NULL)
    {
        return 0;
    }
    stu_basic->num = -1;
    strcat(stu_basic->name, "");
    stu_basic->id = 0;
    stu_basic->stype = 0;
    stu_basic->ctype = 0;
    return 1;
}

int input_info_basic(Stu_Basic *stu_basic)
{
    if (stu_basic == NULL)
    {
        return 0;
    }
    print_line("basic");
    printf("number:");
    scanf("%d", &(stu_basic->num));
    printf("name:");
    scanf("%s", stu_basic->name);
    printf("ID card:");
    scanf("%lld", &(stu_basic->id));
    printf("student type(0-2):");
    scanf("%d", &(stu_basic->stype));
    printf("college(0-11):");
    scanf("%d", &(stu_basic->ctype));
    printf("major:");
    scanf("%s", stu_basic->major);
    return 1;
}

int modify_info_basic(Stu_Basic *stu_basic)
{
    if (stu_basic == NULL)
    {
        return 0;
    }
    char *op_arr[] = {"name", "id", "type", "major"};
    print_star(" Options ");
    for (int i = 0; i < 3; i++) //打印选项
    {
        printf("%d.%s\n", i, op_arr[i]);
    }
    print_star(" Select ");
    int op;
    scanf("%d", &op);
    printf("new:");
    switch (op)
    {
    case 0:
        scanf("%s", stu_basic->name);
        break;
    case 1:
        scanf("%lld", &(stu_basic->id));
        break;
    case 2:
        scanf("%d", &(stu_basic->stype));
        break;
    case 3:
        scanf("%s", stu_basic->major);
        break;
    default:
        break;
    }
    return 1;
}

void print_stu_basic(Stu_Basic stu_basic)
{
    printf("number:%d\n", stu_basic.num);
    printf("name:%s\n", stu_basic.name);
    printf("id:%lld\n", stu_basic.id);
    char stype[10] = "";
    get_stype(stype, stu_basic.stype);
    printf("type:%s\n", stype);
    char ctype[20] = "";
    get_college(ctype, stu_basic.ctype);
    printf("college:%s\n", ctype);
    printf("major:%s\n", stu_basic.major);
}

int save_stu_basic_title(FILE *fp)
{
    if (fp == NULL)
    {
        return 0;
    }
    fprintf(fp, "%6s", "number");
    fprintf(fp, "%16s", "name");
    fprintf(fp, "%6s", "id");
    fprintf(fp, "%16s", "student type");
    fprintf(fp, "%20s", "college");
    fprintf(fp, "%10s", "major");
    return 1;
}

int save_stu_basic_value(FILE *fp, Stu_Basic *stu_basic)
{
    if (fp == NULL || stu_basic == NULL)
    {
        return 0;
    }
    fprintf(fp, "%6d", stu_basic->num);
    fprintf(fp, "%16s", stu_basic->name);
    fprintf(fp, "%6lld", stu_basic->id);
    char stype[10] = "";
    get_stype(stype, stu_basic->stype);
    fprintf(fp, "%16s", stype);
    char ctype[20] = "";
    get_college(ctype, stu_basic->ctype);
    fprintf(fp, "%20s", ctype);
    fprintf(fp, "%10s", stu_basic->major);
    return 1;
}