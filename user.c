//user.c
/*
登录，注册，密码修改
权限控制
*/
//账号系统

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "user.h"
#include "file.h"
#include "utils.h"

User users[MAX_USER];
int userCount = 0;

//密码加密
unsigned int hashPassword(const char* password)
{
    unsigned int hash = 0;

    while (*password)
    {
        hash = hash * 131 + *password;
        password++;
    }

    return hash;
}

//注册用户
bool registerUser()
{
    if (userCount >= MAX_USER)
    {
        printf("用户已满！\n");
        return false;
    }

    User newUser;

    printf("选择角色(1管理员 2教师 3学生): ");
    int r;
    r = safeInputInt();

    char key[30];

    if (r == 1)
    {
        printf("输入管理员授权密码: ");
        fgets(key, 30, stdin);
        key[strcspn(key, "\n")] = 0;

        if (strcmp(key, "admin123") != 0)
        {
            printf("管理员授权密码错误！\n");
            return false;
        }

        strcpy(newUser.role, "admin");
    }
    else if (r == 2)
    {
        printf("输入教师授权密码: ");
        fgets(key, 30, stdin);
        key[strcspn(key, "\n")] = 0;

        if (strcmp(key, "teacher123") != 0)
        {
            printf("教师授权密码错误！\n");
            return false;
        }

        strcpy(newUser.role, "teacher");
    }
    else
    {
        strcpy(newUser.role, "student");
    }

    printf("输入用户名: ");
    fgets(newUser.username, MAX_USERNAME, stdin);
    newUser.username[strcspn(newUser.username, "\n")] = 0;

    //检查用户名是否为空或重复
    for (int i = 0; i < userCount; i++)
    {
        if (strlen(newUser.username) == 0)
        {
            printf("用户名不能为空\n");
            return false;
        }

        if (strcmp(users[i].username, newUser.username) == 0)
        {
            printf("用户名已存在！\n");
            return false;
        }
    }

    //密码设置（加密）
    char pwd[MAX_PASSWORD];

    printf("输入密码: ");
    fgets(pwd, MAX_PASSWORD, stdin);
    pwd[strcspn(pwd, "\n")] = 0;

    newUser.passwordHash = hashPassword(pwd);

    users[userCount++] = newUser;

    saveUsers();

    printf("注册成功！\n");

    return true;
}

//登录
bool loginUser(LoginStatus* status)
{
    char name[MAX_USERNAME];
    char pwd[MAX_PASSWORD];

    printf("用户名: ");
    fgets(name, MAX_USERNAME, stdin);
    name[strcspn(name, "\n")] = 0;

    printf("密码: ");
    fgets(pwd, MAX_PASSWORD, stdin);
    pwd[strcspn(pwd, "\n")] = 0;

    unsigned int inputHash = hashPassword(pwd);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, name) == 0 &&
            users[i].passwordHash == inputHash)
        {
            status->logged = true;
            status->current = users[i];

            printf("登录成功！\n");
            return true;
        }
    }

    printf("账号或密码错误！\n");
    return false;  // 提前返回
}

//注销
void logoutUser(LoginStatus* status)
{
    status->logged = false;
    printf("已注销\n");
}

//修改密码
bool changePassword(LoginStatus* status)
{
    char oldPwd[MAX_PASSWORD];

    printf("输入旧密码: ");
    fgets(oldPwd, MAX_PASSWORD, stdin);
    oldPwd[strcspn(oldPwd, "\n")] = 0;

    unsigned int oldHash = hashPassword(oldPwd);

    if (oldHash != status->current.passwordHash)
    {
        printf("旧密码错误！\n");
        return false;
    }

    char newPwd[MAX_PASSWORD];

    printf("输入新密码: ");
    fgets(newPwd, MAX_PASSWORD, stdin);
    newPwd[strcspn(newPwd, "\n")] = 0;

    unsigned int newHash = hashPassword(newPwd);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, status->current.username) == 0)
        {
            users[i].passwordHash = newHash;
            status->current.passwordHash = newHash;
            break;
        }
    }

    saveUsers();
    printf("修改成功！\n");

    return true;
}

//找回密码（改为提示管理员重置）
bool findPassword()
{
    char name[MAX_USERNAME];

    printf("输入用户名找回密码: ");
    fgets(name, MAX_USERNAME, stdin);
    name[strcspn(name, "\n")] = 0;

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, name) == 0)
        {
            printf("密码已加密存储，请联系管理员重置密码\n");
            return true;
        }
    }

    printf("未找到该账号！\n");
    return false;
}

//管理员重置任意用户密码
void resetUserPassword(LoginStatus* status)
{
    if (strcmp(status->current.role, "admin") != 0)
    {
        printf("权限不足！\n");
        return;
    }

    char username[MAX_USERNAME];

    printf("输入要重置密码的用户名: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = 0;

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            char newPwd[MAX_PASSWORD];

            printf("输入新密码: ");
            fgets(newPwd, MAX_PASSWORD, stdin);
            newPwd[strcspn(newPwd, "\n")] = 0;

            users[i].passwordHash = hashPassword(newPwd);

            saveUsers();

            printf("密码重置成功！\n");
            return;
        }
    }

    printf("未找到该用户！\n");
}