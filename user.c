/*
登录，注册，密码修改
密码找回，权限控制
*/
//账号系统
#define _CRT_SECURE_NO_WARNINGS     
#include <stdio.h>
#include <string.h>
#include "user.h"
#include "file.h"

User users[MAX_USER];
int userCount = 0;

//注册用户
bool registerUser() {
    if (userCount >= MAX_USER) {
        printf("用户已满！\n");
        return false;
    }

    User newUser;

    printf("输入用户名: ");
    fgets(newUser.username, MAX_USERNAME, stdin);
    newUser.username[strcspn(newUser.username, "\n")] = 0;

    // 判断是否重复
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, newUser.username) == 0) {
            printf("用户名已存在！\n");
            return false;
        }
    }

    printf("输入密码: ");
    fgets(newUser.password, MAX_PASSWORD, stdin);
    newUser.password[strcspn(newUser.password, "\n")] = 0;

    printf("选择角色(1管理员 2教师 3学生): ");
    int r;
    scanf("%d", &r);
    getchar();

    if (r == 1) strcpy(newUser.role, "admin");
    else if (r == 2) strcpy(newUser.role, "teacher");
    else strcpy(newUser.role, "student");

    users[userCount++] = newUser;

    saveUsers();

    printf("注册成功！\n");
    return true;
}

bool loginUser(LoginStatus* status) {
    char name[MAX_USERNAME];
    char pwd[MAX_PASSWORD];

    printf("用户名: ");
    fgets(name, MAX_USERNAME, stdin);
    name[strcspn(name, "\n")] = 0;

    printf("密码: ");
    fgets(pwd, MAX_PASSWORD, stdin);
    pwd[strcspn(pwd, "\n")] = 0;

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, name) == 0 && strcmp(users[i].password, pwd) == 0) {
            status->logged = true;
            status->current = users[i];

            printf("登录成功！\n");
            return true;
        }
    }

    printf("账号或密码错误！\n");
    return false;
}

void logoutUser(LoginStatus* status) {
    status->logged = false;
    printf("已注销\n");
}

bool changePassword(LoginStatus* status) {
    char oldPwd[MAX_PASSWORD];

    printf("输入旧密码: ");
    fgets(oldPwd, MAX_PASSWORD, stdin);
    oldPwd[strcspn(oldPwd, "\n")] = 0;

    if (strcmp(oldPwd, status->current.password) != 0) {
        printf("旧密码错误！\n");
        return false;
    }

    char newPwd[MAX_PASSWORD];

    printf("输入新密码: ");
    fgets(newPwd, MAX_PASSWORD, stdin);
    newPwd[strcspn(newPwd, "\n")] = 0;

    // 修改数组中用户密码
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, status->current.username) == 0) {
            strcpy(users[i].password, newPwd);
            strcpy(status->current.password, newPwd);
            break;
        }
    }

    saveUsers();
    printf("修改成功！\n");

    return true;
}

bool findPassword() {
    char name[MAX_USERNAME];

    printf("输入用户名找回密码: ");
    fgets(name, MAX_USERNAME, stdin);
    name[strcspn(name, "\n")] = 0;

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, name) == 0) {
            printf("密码为: %s\n", users[i].password);
            return true;
        }
    }

    printf("未找到该账号！\n");
    return false;
}

// 修改教师信息 - 管理员使用
void modifyTeacherInfo(LoginStatus* status)
{
    if (strcmp(status->current.role, "admin") != 0)
    {
        printf("权限不足！\n");
        return;
    }

    char username[MAX_USERNAME];
    printf("请输入要修改的教师用户名: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = 0;

    // 查找教师用户
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("找到教师：%s\n", users[i].username);

            // 修改教师信息（如密码）
            char new_password[MAX_PASSWORD];
            printf("请输入新密码: ");
            fgets(new_password, MAX_PASSWORD, stdin);
            new_password[strcspn(new_password, "\n")] = 0;

            strcpy(users[i].password, new_password);
            saveUsers();
            printf("教师信息修改成功！\n");
            return;
        }
    }

    printf("未找到教师信息！\n");
}