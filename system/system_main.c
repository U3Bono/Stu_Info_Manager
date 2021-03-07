#include "../include/system/system_main.h"

void system_main()
{
    Buf_Stu buff;
    init_buf(&buff);
    get_list(&buff);

    char *op_arr[] = {"exit", "logout", "search", "add", "delect", "modify", "clear", "print", "output"};
    void (*fun_arr[])(Buf_Stu * buff) = {exit_sys, exit_login, search_stu, add_stu, delect_stu, modify_stu, clear_list, print_list, output_info};
    int power = (user.type == 0) ? sizeof(op_arr) / sizeof(*op_arr) : 3;
L1:
    system("clear");
    print_star("User Info");
    print_user(user);
    print_star(" Options ");
    for (int i = 0; i < power; i++)
    {
        printf("%d.%s\n", i, op_arr[i]);
    }
    print_star(" Select ");
    int op;
    scanf("%d", &op);
    fun_arr[op](&buff);

    print_pause("Please input any key to continum...");
    goto L1;
}

void exit_sys(Buf_Stu *buff)
{
    if (buff == NULL)
    {
        return;
    }
    set_list(buff);    //回写磁盘
    destroy_buf(buff); //清理缓存
    system("clear");
    exit(0);
}

void exit_login(Buf_Stu *buff)
{
    if (buff == NULL)
    {
        return;
    }
    set_list(buff);    //回写磁盘
    destroy_buf(buff); //清理缓存
    login_main();      //退出登陆
}

void search_stu(Buf_Stu *buff)
{
    if (buff == NULL)
    {
        return;
    }
    system("clear");
    print_star(" Search ");
    char *op_arr[] = {"number", "name", "id", "back"};
    for (int i = 0; i < 4; i++)
    {
        printf("%d.%s\n", i, op_arr[i]);
    }

    print_star(NULL);
    printf("select:");
    Stu_Info search_stu; //学生信息
    Search_Op op;        //查询操作
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

    if (search_info(buff, &search_stu, op) == -1)
    {
        printf("No student.(2)\n");
    }
    else
    {
        print_stu(search_stu);
    }
}

void add_stu(Buf_Stu *buff)
{
    if (buff == NULL)
    {
        return;
    }
    Stu_Info student;
    input_info(&student);

    switch_buff(buff, student.ctype);

    int free_buf = -1; //空闲缓存位置
    Stu_Info *sp;
    for (int i = 0; i < buff->length; i++)
    {
        sp = *(buff->stu_map + i);
        if (sp == NULL)
        {
            free_buf = i;
        }
        else
        {
            if (sp->num == student.num || sp->id == student.id)
            {
                printf("Existed!\n");
                return;
            }
        }
    }

    if (free_buf == -1) //没有空闲
    {
        free_buf = buff->length;
        get_buf(buff, 10); //扩充映射表
    }

    sp = malloc(sizeof(Stu_Info)); //分配内存
    *(sp) = student;
    *(buff->stu_map + free_buf) = sp; //写入映射表

    printf("Add success!\n");
}

void delect_stu(Buf_Stu *buff)
{
    if (buff == NULL)
    {
        return;
    }
    Stu_Info student;
    printf("id:"); //id
    scanf("%lld", &student.id);
    printf("college(0-11):"); //院校
    scanf("%d", &student.ctype);

    switch_buff(buff, student.ctype);

    int position = search_info(buff, &student, ID);
    if (position == -1)
    {
        printf("No student.(3)\n");
        return;
    }

    free(*(buff->stu_map + position));
    *(buff->stu_map + position) = NULL;
    printf("Delect success!\n");
}

void modify_stu(Buf_Stu *buff)
{
    if (buff == NULL)
    {
        return;
    }
    Stu_Info student;
    init_stu(&student);
    printf("id:"); //id
    scanf("%lld", &student.id);
    printf("college(0-11):"); //院校
    scanf("%d", &student.ctype);

    switch_buff(buff, student.ctype);

    int position = search_info(buff, &student, ID); //查询记录学生信息
    if (position == -1)
    {
        printf("No student.(4)\n");
        return;
    }

    print_stu(student); //打印信息
    char *options[] = {"number", "name", "type", "major",
                       "road", "contact", "temperature", "medical histroy", "has symptoms?", "back date"};
    print_star(" Options ");
    for (int i = 0; i < 10; i++) //打印选项
    {
        printf("%d.%s\n", i, *(options + i));
    }
    print_star("Select");
    int op;
    scanf("%d", &op);
    if (op == 9)
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
        if (search_info(buff, &student, NUMBER) != -1)
        {
            printf("Existed!\n");
            return;
        }
        break;
    case 1:
        scanf("%s", student.name);
        break;
    case 2:
        scanf("%d", &(student.stype));
        break;
    case 3:
        scanf("%s", student.major);
        break;
    case 4:
        scanf("%s", student.trafo.road);
        break;
    case 5:
        scanf("%s", student.trafo.contact);
        break;
    case 6:
        scanf("%f", &(student.bacfo.temperature));
        break;
    case 7:
        scanf("%s", student.bacfo.medical_h);
        break;
    case 8:
        scanf("%d", &(student.bacfo.symptoms));
        break;
    case 9:
        scanf("%s", student.bacfo.back_date);
        break;
    default:
        break;
    }

    **(buff->stu_map + position) = student;
    printf("Modify success!\n");
}

void clear_list(Buf_Stu *buff)
{
    if (buff == NULL)
    {
        return;
    }

    Col_Type col_type;
    printf("college(0-11):"); //院校
    scanf("%d", &col_type);

    switch_buff(buff, col_type);

    if (clean_buff(buff))
    {
        printf("Clear success!\n");
    }
    else
    {
        printf("Failed!\n");
    }
}

void print_list(Buf_Stu *buff)
{
    if (buff == NULL)
    {
        return;
    }

    Col_Type col_type;
    printf("college(0-11):"); //院校
    scanf("%d", &col_type);

    switch_buff(buff, col_type);

    print_star("Information");
    Stu_Info *sp;
    for (int i = 0; i < buff->length; i++)
    {
        sp = *(buff->stu_map + i);
        if (sp != NULL)
        {
            print_stu_basic(*sp);
            print_line(NULL);
        }
    }
}

void output_info(Buf_Stu *buff)
{
    if (buff == NULL)
    {
        return;
    }

    Col_Type col_type;
    printf("college(0-11):"); //院校
    scanf("%d", &col_type);

    switch_buff(buff, col_type);

    char fname[30];
    printf("File name:");
    scanf("%s", fname);
    if (save_list(buff, fname))
    {
        printf("Save success!\n");
    }
    else
    {
        printf("Failed.\n");
    }
}
