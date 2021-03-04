#include "../include/system/system_main.h"

void system_main()
{
    char *options[] = {"exit", "search", "add", "delect", "modify", "print"};
    int power = (user.type == 0) ? 6 : 2;
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
    case 5:
        print_list();
        break;
    default:
        break;
    }
    print_pause("Please input any key to continum...");
    goto L1;
}

void exit_login()
{
    login_main();
}

void search_stu()
{
    system("clear");
    print_star(" Search ");
    char *options[] = {"number", "name", "id", "back"};
    for (int i = 0; i < 4; i++)
    {
        printf("%d.%s\n", i, *(options + i));
    }

    print_star(NULL);
    printf("select:");
    Stu_Info search_stu; //学生信息
    init_stu(&search_stu);
    Search_Op op; //查询操作
    scanf("%d", &op);
    switch (op)
    {
    case NUMBER:
        printf("number:");
        scanf("%d", &search_stu.num);
        break;
    case NAME:
        printf("name:");
        scanf("%s", search_stu.name);
        break;
    case ID:
        printf("id:");
        scanf("%lld", &search_stu.id);
        break;
    default:
        return;
    }
    printf("college(0-11):"); //院校
    scanf("%d", &search_stu.ctype);

    FILE *fp;
    char fname[30] = "info_";
    get_college(fname, search_stu.ctype);
    if ((fp = fopen(fname, "rb")) == NULL)
    {
        print_pause("No student.(1)");
        return;
    }
    if (search_info(fp, &search_stu, op) == -1)
    {
        printf("No student.(2)\n");
    }
    else
    {
        print_stu(search_stu);
    }
    fclose(fp);
}

void add_stu()
{
    Stu_Info student;
    input_info(&student);

    FILE *fp;
    char fname[30] = "info_";
    get_college(fname, student.ctype);
    if ((fp = fopen(fname, "ab+")) == NULL)
    {
        return;
    }
    if (search_info(fp, &student, ID) == -1)
    {
        if (search_info(fp, &student, NUMBER) == -1)
        {
            fwrite(&student, sizeof(Stu_Info), 1, fp);
            printf("Add success!\n");
        }
        else
        {
            printf("Number error!\n");
        }
    }
    else
    {
        printf("Existed!\n");
    }
    fclose(fp);
}

void delect_stu()
{
    Stu_Info student;
    init_stu(&student);
    printf("id:");
    scanf("%lld", &student.id);
    printf("college(0-11):"); //院校
    scanf("%d", &student.ctype);

    FILE *fp;
    char fname[30] = "info_";
    get_college(fname, student.ctype);
    if ((fp = fopen(fname, "rb+")) == NULL)
    {
        return;
    }
    int position = search_info(fp, &student, ID);
    if (position == -1)
    {
        printf("No student.(3)\n");
    }
    else
    {
        int flag = -student.num;
        fseek(fp, sizeof(Stu_Info) * position, 0);
        fwrite(&flag, sizeof(int), 1, fp);
        printf("Delect success!\n");
    }
    fclose(fp);
}

void modify_stu()
{
    Stu_Info student;
    init_stu(&student);
    printf("id:");
    scanf("%lld", &student.id);
    printf("college(0-11):"); //院校
    scanf("%d", &student.ctype);

    FILE *fp;
    char fname[30] = "info_";
    get_college(fname, student.ctype);
    if ((fp = fopen(fname, "rb+")) == NULL)
    {
        return;
    }
    int position = search_info(fp, &student, ID);
    if (position == -1)
    {
        printf("No student.(4)\n");
    }
    else
    {
        print_stu(student);
        char *options[] = {"number", "name", "id", "type", "major",
                           "road", "contact", "temperature", "medical histroy", "has symptoms?", "back date"};
        print_star(" Options ");
        for (int i = 0; i < 11; i++)
        {
            printf("%d.%s\n", i, *(options + i));
        }
        print_star("Select");
        int op;
        scanf("%d", &op);
        if (op == 10)
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
            scanf("%d", &(student.num));
            if (search_info(fp, &student, NUMBER) == -1)
            {
                printf("Existed!\n");
                return;
            }
            break;
        case 1:
            scanf("%s", student.name);
            break;
        case 2:
            scanf("%lld", &(student.id));
            if (search_info(fp, &student, ID) == -1)
            {
                printf("Existed!\n");
                return;
            }
            break;
        case 3:
            scanf("%d", &(student.stype));
            break;
        case 4:
            scanf("%s", student.major);
            break;
        case 5:
            scanf("%s", student.trafo.road);
            break;
        case 6:
            scanf("%s", student.trafo.contact);
            break;
        case 7:
            scanf("%f", &(student.bacfo.temperature));
            break;
        case 8:
            scanf("%s", student.bacfo.medical_h);
            break;
        case 9:
            scanf("%d", &(student.bacfo.symptoms));
            break;
        case 10:
            scanf("%s", student.bacfo.back_date);
            break;
        default:
            break;
        }

        fseek(fp, sizeof(Stu_Info) * position, 0);
        fwrite(&student, sizeof(Stu_Info), 1, fp);
        printf("Modify success!\n");
    }
    fclose(fp);
}

void print_list()
{
    Stu_Info stu;
    printf("college(0-11):"); //院校
    scanf("%d", &stu.ctype);

    FILE *fp;
    char fname[30] = "info_";
    get_college(fname, stu.ctype);
    print_star("basic");
    if ((fp = fopen(fname, "rb")) == NULL)
    {
        print_pause("No student.(4)");
        return;
    }

    while ((fread(&stu, sizeof(Stu_Info), 1, fp)) == 1)
    {
        if (stu.num > 0)
        {
            print_stu_basic(stu);
            print_line(NULL);
        }
    }

    fclose(fp);
}