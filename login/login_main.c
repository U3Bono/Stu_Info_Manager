#include "../include/login/login_main.h"

void login_main()
{
    init_user();
    User_Info login_user;
    system("clear");
    print_star("LOGIN");
L1:
    printf("username:");
    scanf("%s", login_user.username);
    printf("password:");
    scanf("%s", login_user.password);

    if (login(&login_user))
    {
        user = login_user;
        system_main();
    }
    else
    {
        printf("failed!\n");
        goto L1;
    }
}

int login(User_Info *login_user)
{
    if (login_user == NULL)
    {
        return 0;
    }
    FILE *fp;
    char fname[] = "data/info_user";
    User_Info read_user;
    if ((fp = fopen(fname, "rb+")) == NULL) //无用户表，创建用户表
    {
        if ((fp = fopen(fname, "wb")) == NULL)
        {
            return 0;
        }
        login_user->type = 0; //root用户
        fwrite(login_user, sizeof(User_Info), 1, fp);
    }
    else
    {
        while (fread(&read_user, sizeof(User_Info), 1, fp) == 1) //读取用户信息
        {
            if (strcmp(login_user->username, read_user.username) == 0) //用户名匹配
            {
                if (strcmp(login_user->password, read_user.password) == 0) //密码匹配登陆
                {
                    login_user->type = read_user.type;
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
        }

        fseek(fp, 0, 2);
        login_user->type = 1;
        fwrite(login_user, sizeof(User_Info), 1, fp); //未匹配到用户则创建用户
    }
    fclose(fp);
    return 1;
}

void init_user()
{
    strcat(user.username, "");
    strcat(user.password, "");
    user.type = -1;
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