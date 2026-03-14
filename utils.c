#include <stdio.h>
#include "utils.h"

//安全输入整数
int safeInputInt()
{
    int x;

    while (scanf("%d", &x) != 1)
    {
        printf("输入无效，请重新输入数字: ");

        while (getchar() != '\n');  // 清空错误输入
    }

    while (getchar() != '\n');      // 清空换行

    return x;
}

int safeInputFloat()
{
    int x;

    while (scanf("%d", &x) != 1)
    {
        printf("输入无效，请重新输入数字: ");

        while (getchar() != '\n');  // 清空错误输入
    }

    while (getchar() != '\n');      // 清空换行

    return x;
}