/*
程序入口（总控制）
1.登录界面
2.系统启动
3.系统退出保存数据
4.初始化数据
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "student.h"
#include "user.h"
#include "file.h"
#include "utils.h"


int main() {
    
    
    // 加载学生数据和用户数据
    head = loadStudents();//读学生文件
    loadUsers();//读账号文件

    LoginStatus loginStatus = { false }; // 初始化登录状态

    // 显示主菜单，进入系统
    mainMenu(&loginStatus);

    // 退出前保存数据
    saveStudents(head);   // 保存学生数据
    saveUsers();          // 保存用户数据

    printf("程序已退出！\n");

    return 0;
}