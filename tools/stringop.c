#include "../include/tools/stringop.h"

char *safe_strcat(char *s1, char *s2)
{
    if (s1 == NULL || s2 == NULL)
    {
        return NULL;
    }
    int i = 0;
    int j = 0;
    while (*(s1 + i) != '\0' || *(s2 + j) != '\0') //统计字符串长度,时间复杂度:O(m)
    {
        if (*(s1 + i) != '\0')
        {
            i++;
        }
        if (*(s2 + j) != '\0')
        {
            j++;
        }
    }
    int size = i + j + 1;
    char *buf = malloc(sizeof(char) * size); //分配缓冲大小,时间复杂度:O(m)
    int s1_length = i;
    *(buf + size - 1) = '\0';
    while (i != 0 || j != 0) //拷贝字符串到缓冲区
    {
        if (i != 0)
        {
            i--;
            *(buf + i) = *(s1 + i);
        }
        if (j != 0)
        {
            j--;
            *(buf + s1_length + j) = *(s2 + j);
        }
    }
    return buf;
}