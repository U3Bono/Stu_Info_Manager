#include "../include/tools/printop.h"

void print_logo()
{
    printf("*********************************************************\n");
    printf("*\t\t\t\t\t\t\t*\n");
    printf("*\t\tStudent Information Manager\t\t*\n");
    printf("*\t\t\t\t\t\t\t*\n");
    printf("*\t\t\t\t\tversion:%s\t*\n", SYS_VERSION);
    printf("*\t\t\t\t\tauthor:%s\t*\n", SYS_AUTHOR);
    printf("*\t\t\t\t\t\t\t*\n");
    printf("*********************************************************\n");
}

void print_line(char *title)
{
    printf("--------------------");
    if (title != NULL)
    {
        printf(" %s ", title);
    }
    else
    {
        printf("----------");
    }
    printf("--------------------\n");
}

void print_star(char *title)
{
    printf("********************");
    if (title != NULL)
    {
        printf(" %s ", title);
    }
    else
    {
        printf("**********");
    }
    printf("********************\n");
}

void print_pause(char *notice)
{
    if (notice != NULL)
    {
        printf("%s\n", notice);
    }
    flushiobuf();
    getchar();
}

void bool_printf(int bl)
{
    switch (bl)
    {
    case 0:
        printf("false.\n");
        break;
    default:
        printf("true.\n");
    }
}

void print_user(User_Info user)
{
    printf("user name:%s\n", user.username);
    printf("user type:");
    if (user.type == 0)
    {
        printf("%s", "root");
    }
    else
    {
        printf("%s", "normal");
    }
    printf("(%d)\n", user.type);
}

void print_stu(Stu_Info stu)
{
    print_line("basic");
    print_stu_basic(stu);
    print_line("travel");
    print_stu_travel(stu);
    print_line("back");
    print_stu_travel(stu);
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
    printf("temperature:%f\n", stu.bacfo.temperature);
    printf("medical histroy:%s\n", stu.bacfo.medical_h);
    printf("has symptoms?");
    bool_printf(stu.bacfo.symptoms);
    printf("back date:%s\n", stu.bacfo.back_date);
}

void flushiobuf()
{
    setbuf(stdin, 0);
    setbuf(stdout, 0);
}