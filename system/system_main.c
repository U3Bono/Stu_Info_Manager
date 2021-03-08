#include "../include/system/system_main.h"

void system_main()
{
    choose_itype(EPIDEMIC);
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
    char *op_arr[] = {"back", "number", "name", "id"};
    for (int i = 0; i < 4; i++)
    {
        printf("%d.%s\n", i, op_arr[i]);
    }

    print_star(NULL);
    printf("select:");
    void *stu = malloc(buff->stu_size); //学生信息
    Search_Op op;                       //查询操作
    scanf("%d", &op);
    switch (op)
    {
    case NUMBER:
        printf("number:");
        scanf("%d", &((Stu_Basic *)stu)->num);
        break;
    case NAME:
        printf("name:");
        scanf("%s", ((Stu_Basic *)stu)->name);
        break;
    case ID:
        printf("id:");
        scanf("%lld", &((Stu_Basic *)stu)->id);
        break;
    default:
        return;
    }
    printf("college(0-11):"); //院校
    scanf("%d", &((Stu_Basic *)stu)->ctype);

    switch_buff(buff, ((Stu_Basic *)stu)->ctype);

    if (search_info(buff->stu_map, buff->length, stu, op) == -1)
    {
        printf("No student.(2)\n");
    }
    else
    {
        print_stu(stu);
    }
    free(stu);
}

void add_stu(Buf_Stu *buff)
{
    if (buff == NULL)
    {
        return;
    }
    void *stu = malloc(buff->stu_size); //学生信息
    input_info(stu);

    switch_buff(buff, (*(Stu_Basic *)stu).ctype);

    int free_buf = -1; //空闲缓存位置
    void *sp;
    for (int i = 0; i < buff->length; i++)
    {
        sp = *(buff->stu_map + i);
        if (sp == NULL)
        {
            free_buf = i;
        }
        else
        {
            if (((Stu_Basic *)sp)->num == ((Stu_Basic *)stu)->num || ((Stu_Basic *)sp)->id == ((Stu_Basic *)stu)->id)
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

    sp = malloc(buff->stu_size); //分配内存
    memcpy(sp, stu, buff->stu_size);
    *(buff->stu_map + free_buf) = sp; //写入映射表
    free(stu);

    printf("Add success!\n");
}

void delect_stu(Buf_Stu *buff)
{
    if (buff == NULL)
    {
        return;
    }
    void *stu = malloc(buff->stu_size); //学生信息
    printf("id:");                      //id
    scanf("%lld", &((Stu_Basic *)stu)->id);
    printf("college(0-11):"); //院校
    scanf("%d", &((Stu_Basic *)stu)->ctype);

    switch_buff(buff, ((Stu_Basic *)stu)->ctype);

    int position = search_info(buff->stu_map, buff->length, stu, ID);
    if (position == -1)
    {
        printf("No student.(3)\n");
        return;
    }

    free(*(buff->stu_map + position));
    *(buff->stu_map + position) = NULL;
    free(stu);
    printf("Delect success!\n");
}

void modify_stu(Buf_Stu *buff)
{
    if (buff == NULL)
    {
        return;
    }
    void *stu = malloc(buff->stu_size); //学生信息
    init_stu(stu);
    printf("id:"); //id
    scanf("%lld", &((Stu_Basic *)stu)->id);
    printf("college(0-11):"); //院校
    scanf("%d", &((Stu_Basic *)stu)->ctype);

    switch_buff(buff, ((Stu_Basic *)stu)->ctype);

    int position = search_info(buff->stu_map, buff->length, stu, ID); //查询记录学生信息
    if (position == -1)
    {
        printf("No student.(4)\n");
        return;
    }
    if (modify_info(stu))
    {
        memcpy(*(buff->stu_map + position), stu, buff->stu_size);
        free(stu);
        printf("Modify success!\n");
    }
    else
    {
        free(stu);
        printf("Failed!\n");
    }
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

    if (buff->length == 0)
    {
        printf("No student.(5)\n");
        return;
    }

    print_star("Information");
    void *sp;
    for (int i = 0; i < buff->length; i++)
    {
        sp = *(buff->stu_map + i);
        if (sp != NULL)
        {
            print_stu_basic(*(Stu_Basic *)sp);
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
