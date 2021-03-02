#include "../include/tools/printop.h"

void print_logo()
{
    printf("**************************************************\n");
    printf("*                                                *\n");
    printf("*        Student Information Manager 1.0         *\n");
    printf("*                                                *\n");
    printf("*                             by U3_Bono         *\n");
    printf("*                                                *\n");
    printf("**************************************************\n");
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

void print_user(User_Info user)
{
    printf("User name:");
    
    printf("%s", user.username);
    printf("\nUser type:");
    if(user.type == 0)
    {
        printf("%s", "root");
    }
    else
    {
        printf("%s", "normal");
    }
    printf("(%d)", user.type);
    printf("\n");
}