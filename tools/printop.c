#include "../include/tools/printop.h"

void print_logo()
{
    printf("*********************************************************\n");
    printf("*%55s*\n", " ");
    printf("*%40s%15s*\n", SYS_NAME, " ");
    printf("*%55s*\n", " ");
    printf("*%46s%s%5s*\n", "version:", SYS_VERSION, " ");
    printf("*%45s%s%3s*\n", "author:", SYS_AUTHOR, " ");
    printf("*%55s*\n", " ");
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

void flushiobuf()
{
    setbuf(stdin, 0);
    setbuf(stdout, 0);
}