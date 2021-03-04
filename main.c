#include "main.h"

int main(int argc, const char *argv[])
{

    printf_info();
    login_main();

    return 0;
}

void printf_info()
{
    system("clear");
    print_logo();
    printf("\n");
    print_pause("Please input any key to enter...");
}
