#include "../include/system/system_main.h"

void system_main()
{
    char *options[] = {"exit", "search", "add", "delect", "modify"};
    int power = (user.type == 0) ? 5 : 2;
L1:
    system("clear");
    print_star("User Info");
    print_user(user);
    print_star(" Options ");
    for (int i = 0; i < power; i++)
    {
        printf("%d.%s\n", i, *(options + i));
    }
    print_star(" Select ");
    int op;
    scanf("%d", &op);
    switch (op)
    {
    case 0:
        exit_login();
        break;
    case 1:
        search_stu();
        break;
    case 2:
        add_stu();
        break;
    case 3:
        delect_stu();
        break;
    case 4:
        modify_stu();
        break;
    default:
        break;
    }
    goto L1;
}

static void exit_login()
{
    login_main();
}

static void search_stu()
{
    system("clear");
    print_star(" Search ");
    char *options[] = {"back", "name", "number", "id"};
    for (int i = 0; i < 3; i++)
    {
        printf("%d.%s\n", i, *(options + i));
    }

    print_star(" Select ");
    int op;
    scanf("%d", &op);
    switch (op)
    {
    case 0:
        break;
    case 1:

        break;
    case 2:

        break;
    case 3:

        break;
    default:
        break;
    }
}

static void add_stu()
{
    printf("student information:\n");

    Stu_Info student;
    printf("number:");
    scanf("%d", &student.num);
    printf("\nname:");
    scanf("%s", student.name);
    printf("\nID card:");
    scanf("%d", &student.id);
    while (1)
    {
        printf("\nstudent type(0-2):");
        scanf("%d", &student.stype);
        if (student.stype > -1 && student.stype < 3)
        {
            break;
        }
    }
    while (1)
    {
        printf("\ncollege(0-11):");
        scanf("%d", &student.ctype);
        if (student.ctype > -1 && student.ctype < 12)
        {
            break;
        }
    }
    printf("\nmajor:");
    scanf("%s", student.major);

    printf("\nroad(xx-xx-xx):");
    printf("%s", student.trafo.road);
    printf("\ncontact(xx,xx,xx):");
    printf("%s", student.trafo.contact);

    printf("\ntemperature:");
    printf("%d", student.bacfo.temperature);
    printf("\nmedical history:");
    printf("%s", student.bacfo.medical_h);
    printf("\nhas symptoms(0,1)?");
    printf("%d", student.bacfo.symptoms);
    printf("\nback date(xxxx-xx-xx):");
    printf("%s", student.bacfo.back_date);
}

static void delect_stu()
{
}

static void modify_stu()
{
}