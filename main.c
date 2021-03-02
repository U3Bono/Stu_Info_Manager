#include "include/tools/printop.h"
#include "include/login/login_main.h"

int main(int argc, const char *argv[])
{
    system("clear");

    print_logo();

    printf("\nPlease input any key to enter...");
    getchar();

    login_main();

    return 0;
}
