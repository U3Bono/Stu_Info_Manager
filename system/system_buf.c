#include "../include/system/system_buf.h"

void init_buf(Buf_Stu *buff)
{
    buff->stu_map = NULL;
    buff->length = 0;
    buff->col_type = 0;
    buff->stu_size = get_ssize();
}

void destroy_buf(Buf_Stu *buff)
{
    if (buff == NULL | buff->stu_map == NULL)
    {
        return;
    }
    void *sp;
    for (int i = 0; i < buff->length; i++)
    {
        sp = *(buff->stu_map + i);
        free(sp); //清理学生信息缓存
    }
    free(buff->stu_map); //清理映射表
    init_buf(buff);
}

int get_buf(Buf_Stu *buff, int length)
{
    if (buff == NULL)
    {
        return 0;
    }
    int new_length = buff->length + length;                 //扩展长度
    void **new_table = malloc(sizeof(void *) * new_length); //分配内存
    if (new_table == NULL)
    {
        return 0;
    }

    for (int i = 0; i < new_length; i++)
    {
        if (i < buff->length)
        {
            *(new_table + i) = *(buff->stu_map + i); //复制地址
        }
        else
        {
            *(new_table + i) = NULL; //初始化新地址
        }
    }

    free(buff->stu_map);
    buff->length = new_length; //更新长度
    buff->stu_map = new_table; //更新映射表

    return 1;
}

int get_list(Buf_Stu *buff)
{
    if (buff == NULL)
    {
        return 0;
    }
    FILE *fp;
    char fname[40] = "info_";
    get_college(fname, buff->col_type);
    strcat(fname, "_");
    get_itype(fname);
    if ((fp = fopen(fname, "rb")) == NULL)
    {
        return 0;
    }
    fread(&buff->length, sizeof(int), 1, fp);              //读入总数
    buff->stu_map = malloc(sizeof(void *) * buff->length); //分配映射表
    void *sp;
    for (int i = 0; i < buff->length; i++)
    {
        sp = malloc(buff->stu_size);      //分配缓存
        fread(sp, buff->stu_size, 1, fp); //读入到缓存
        *(buff->stu_map + i) = sp;        //地址存放入映射表
    }
    fclose(fp);

    return 1;
}

int set_list(Buf_Stu *buff)
{
    if (buff == NULL | buff->stu_map == NULL)
    {
        return 0;
    }
    FILE *fp;
    char fname[40] = "info_";
    get_college(fname, buff->col_type);
    strcat(fname, "_");
    get_itype(fname);
    if ((fp = fopen(fname, "wb")) == NULL)
    {
        return 0;
    }
    int total = 0;
    fwrite(&total, sizeof(int), 1, fp); //初始化总数
    void *sp;
    for (int i = 0; i < buff->length; i++)
    {
        sp = *(buff->stu_map + i);
        if (sp != NULL) //未被标记删除的数据
        {
            total++;                           //统计总数
            fwrite(sp, buff->stu_size, 1, fp); //写入学生信息
        }
    }
    rewind(fp);
    fwrite(&total, sizeof(int), 1, fp); //更新总数
    fclose(fp);
    return 1;
}

int switch_buff(Buf_Stu *buff, Col_Type s_ctype)
{
    if (buff == NULL | buff->col_type == s_ctype)
    {
        return 0;
    }

    if (buff->stu_map != NULL) //数据不为空
    {
        set_list(buff);    //回写数据
        destroy_buf(buff); //清空缓存
    }
    buff->col_type = s_ctype; //切换院校
    if (!get_list(buff))      //未读取到数据
    {
        destroy_buf(buff); //清空缓存
    }

    return 1;
}

int save_list(Buf_Stu *buff, char *fname)
{
    if (buff == NULL)
    {
        return 0;
    }
    FILE *fp;
    if ((fp = fopen(fname, "w")) == NULL)
    {
        return 0;
    }

    save_stu_title(fp);

    void *sp;
    for (int i = 0; i < buff->length; i++)
    {
        sp = *(buff->stu_map + i);
        if (sp != NULL)
        {
            save_stu_value(fp, sp);
        }
    }

    fclose(fp);
    return 1;
}

int clean_buff(Buf_Stu *buff)
{
    if (buff == NULL | buff->stu_map == NULL)
    {
        return 0;
    }

    void *sp;
    int last = buff->length - 1; //指向最后一个有数据的地方
    for (int i = 0; i < last + 1; i++)
    {
        sp = *(buff->stu_map + i);
        if (sp == NULL) //清理空闲缓存
        {
            while (i < last)
            {
                if ((sp = *(buff->stu_map + last)) != NULL) //填入最后一个数据
                {
                    *(buff->stu_map + i) = sp;
                    *(buff->stu_map + last) = NULL;
                    last--;
                    break;
                }
                last--;
            }
            if (sp == NULL) //之后的缓存都为空，整理完成
            {
                break;
            }
        }

        if (i > 0) //插入排序
        {
            if ((((Stu_Basic *)sp)->num < ((Stu_Basic *)*(buff->stu_map + i - 1))->num))
            {
                *(buff->stu_map + i) = *(buff->stu_map + i - 1);
                for (int j = i - 1; j > 0; j--)
                {
                    if (((Stu_Basic *)sp)->num >= ((Stu_Basic *)*(buff->stu_map + j - 1))->num) //大于等于上一个数
                    {
                        *(buff->stu_map + j) = sp;
                        break;
                    }

                    *(buff->stu_map + j) = *(buff->stu_map + j - 1); //上一个数后移
                }
            }
        }
    }
    return 1;
}
