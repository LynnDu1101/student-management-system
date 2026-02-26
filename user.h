// 账号模块接口(声明用户结构与用户函数）

#ifndef USER_H
#define USER_H

#include <stdbool.h>

#define MAX_USER 100
#define MAX_USERNAME 30
#define MAX_PASSWORD 30

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char role[20];  // 角色（例如管理员、教师、学生）
} User;

typedef struct {
    bool logged;  // 登录状态
    User current; // 当前登录的用户信息
} LoginStatus;

extern User users[MAX_USER];   // 用户数组
extern int userCount;          // 用户数量

bool registerUser();           // 注册用户
bool loginUser(LoginStatus* status);  // 用户登录
void logoutUser(LoginStatus* status); // 用户注销
bool changePassword(LoginStatus* status); // 修改密码
bool findPassword();           // 找回密码

#endif