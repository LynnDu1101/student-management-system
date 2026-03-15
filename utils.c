#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "utils.h"

// 安全输入通用函数，使用格式化字符串和指针来处理输入
int safeInput(const char* format, void* x) {
    while (scanf(format, x) != 1) {
        printf("输入无效，请重新输入: ");
        while (getchar() != '\n');  // 清空错误输入
    }

    // 清空换行符，避免影响后续输入
    while (getchar() != '\n');
    return 1;
}

// 安全输入整数
int safeInputInt() {
    int x;
    safeInput("%d", &x);  // 使用通用的输入函数
    return x;
}

// 安全输入浮动数
float safeInputFloat() {
    float x;
    safeInput("%f", &x);  // 使用通用的输入函数
    return x;
}
