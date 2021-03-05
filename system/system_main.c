#include "../include/system/system_main.h"

void system_main()
{
    Buf_Stu buff;
    init_buf(&buff);
    get_list(&buff);

    char *options[] = {"exit", "search", "add", "delect", "modify", "print", "save"};
    int power = (user.type == 0) ? 7 : 2;
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
        exit_login(&buff);
        break;
    case 1:
        search_stu(&buff);
        break;
    case 2:
        add_stu(&buff);
        break;
    case 3:
        delect_stu(&buff);
        break;
    case 4:
        modify_stu(&buff);
        break;
    case 5:
        print_list(&buff);
        break;
    case 6:
        save_info(&buff);
        break;
    default:
        break;
    }
    print_pause("Please input any key to continum...");
    goto L1;
}

void exit_login(Buf_Stu *buff)
{
    set_list(buff);    //回写磁盘
    destroy_buf(buff); //清理缓存
    login_main();      //退出登陆
}

void search_stu(Buf_Stu *buff)
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
    Stu_Info student;
    input_info(&student);

    if (buff->col_type != student.ctype)
    {
        switch_buff(buff, student.ctype);
    }

    int free_buf = -1; //空闲缓存位置
    Stu_Info search_stu;
    for (int i = 0; i < buff->length; i++)
    {
        search_stu = *(buff->stu_list + i);
        if (search_stu.num > 0)
        {
            if (search_stu.num == student.num || search_stu.id == student.id)
            {
                printf("Existed!\n");
                return;
            }
        }
        else
        {
            free_buf = i;
        }
    }

    if (free_buf == -1) //没有空闲
    {
        free_buf = buff->length;
        enlarge_buf(buff, 10); //扩充缓存
    }

    *(buff->stu_list + free_buf) = student; //写入新增数据到缓存
    printf("Add success!\n");
}

void delect_stu(Buf_Stu *buff)
{
    Stu_Info student;
    printf("id:"); //id
    scanf("%lld", &student.id);
    printf("college(0-11):"); //院校
    scanf("%d", &student.ctype);

    if (student.ctype != buff->col_type) //不同院校
    {
        switch_buff(buff, student.ctype);
    }

    int position = search_info(buff, &student, ID);
    if (position == -1)
    {
        printf("No student.(3)\n");
        return;
    }

    (buff->stu_list + position)->num *= -1;
    printf("Delect success!\n");
}

void modify_stu(Buf_Stu *buff)
{
    Stu_Info student;
    init_stu(&student);
    printf("id:"); //id
    scanf("%lld", &student.id);
    printf("college(0-11):"); //院校
    scanf("%d", &student.ctype);

    if (student.ctype != buff->col_type) //不同院校
    {
        switch_buff(buff, student.ctype);
    }

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

    *(buff->stu_list + position) = student;
    printf("Modify success!\n");
}

void print_list(Buf_Stu *buff)
{
    Stu_Info stu;
    for (int i = 0; i < buff->length; i++)
    {
        stu = *(buff->stu_list + i);
        if (stu.num > 0)
        {
            print_stu_basic(stu);
            print_line(NULL);
        }
    }
}

void save_info(Buf_Stu *buff)
{
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
