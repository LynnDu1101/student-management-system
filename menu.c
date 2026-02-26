#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "student.h"
#include "user.h"
#include "file.h"


/* ===== 学生成绩分析 ===== */
void studentScoreAnalysis(Student* head, const char* studentId)
{
    Student* s = findById(head, studentId);
    if (!s)
    {
        printf("未找到学生信息！\n");
        return;
    }

    int count = 0;
    int better = 0;
    Student* p = head;

    while (p)
    {
        count++;
        if (p->score > s->score)
            better++;
        p = p->next;
    }

    float percent = 100.0f * (count - better) / count;

    printf("\n===== 成绩分析 =====\n");
    printf("姓名：%s\n", s->name);
    printf("成绩：%.2f\n", s->score);
    printf("超过 %.2f%% 的同学\n", percent);
}

/* ===== 查询班级成绩 ===== */
void studentViewClassScores(Student* head, const char* studentId)
{
    Student* self = findById(head, studentId);

    if (!self)
    {
        printf("未找到学生信息！\n");
        return;
    }

    printf("\n===== 本班成绩 =====\n");
    printf("班级：%s\n\n", self->className);

    Student* p = head;
    int found = 0;

    while (p)
    {
        if (strcmp(p->className, self->className) == 0)
        {
            printf("%s  %s  %.2f\n",
                p->id,
                p->name,
                p->score);

            found = 1;
        }
        p = p->next;
    }

    if (!found)
        printf("暂无班级数据\n");
}

/* ===== 从文件录入用户 ===== */
void importUsersFromFile()
{
    FILE* fp = fopen("users.txt", "r");
    if (!fp)
    {
        printf("无法打开 users.txt 文件\n");
        return;
    }

    User temp;

    while (fscanf(fp, "%s %s %s",
        temp.username,
        temp.password,
        temp.role) == 3)
    {
        if (userCount < MAX_USER)
        {
            users[userCount++] = temp;
        }
    }

    fclose(fp);
    saveUsers();

    printf("用户导入完成！\n");
}

/* ===== 学生菜单 ===== */
void studentMenu(LoginStatus* status)
{
    int choice;

    while (1)
    {
        printf("\n===== 学生菜单 =====\n");
        printf("1. 查询自己成绩\n");
        printf("2. 查询本班成绩\n");
        printf("3. 成绩分析\n");
        printf("0. 返回\n");

        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            searchStudent(head);
            break;

        case 2:
            studentViewClassScores(head, status->current.username);
            break;

        case 3:
            studentScoreAnalysis(head, status->current.username);
            break;

        case 4:
            submitAppeal();
            break;

        case 0:
            return;
        }
    }
}

/* ===== 教师菜单 ===== */
void teacherMenu(LoginStatus* status)
{
    int choice;

    while (1)
    {
        printf("\n===== 教师菜单 =====\n");
        printf("1. 添加学生\n");
        printf("2. 修改学生\n");
        printf("3. 删除学生\n");
        printf("4. 查询学生\n");
        printf("5. 班级成绩查看\n");
        printf("6. 班级成绩分析\n");
        printf("7. 导出班级学生\n");
        printf("0. 返回\n");

        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            addStudent(&head);
            break;
        case 2:
            modifyStudent(head);
            break;
        case 3:
            deleteStudent(&head);
            break;
        case 4:
            searchStudent(head);
            break;
        case 5:
            showAllStudents(head);
            break;
        case 6:
            statisticsStudents(head);
            break;
        case 7:
            exportStudentsToTxt(head);
            break;
        case 0:
            return;
        }
    }
}

/* ===== 管理员菜单 ===== */
void adminMenu(LoginStatus* status)
{
    int choice;

    while (1)
    {
        printf("\n===== 管理员菜单 =====\n");
        printf("1. 添加学生\n");
        printf("2. 删除学生\n");
        printf("3. 修改学生\n");
        printf("4. 查询学生\n");
        printf("5. 成绩统计\n");
        printf("6. 导入用户\n");
        printf("7. 导出全部学生\n");
        printf("8. 处理成绩申诉\n");
        printf("9. 修改教师信息\n");
        printf("0. 返回\n");

        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            addStudent(&head);
            break;
        case 2:
            deleteStudent(&head);
            break;
        case 3:
            modifyStudent(head);
            break;
        case 4:
            searchStudent(head);
            break;
        case 5:
            statisticsStudents(head);
            break;
        case 6:
            importUsersFromFile();
            break;
        case 7:
            exportAllStudents(head);
            break;
        case 8:
            processAppeal();
            break;
        case 9:
            modifyTeacherInfo(status);  // 管理员修改教师信息
            break;
        case 0:
            return;
        default:
            printf("无效选择！\n");
        }
    }
}

/* ===== 主菜单 ===== */
void mainMenu(LoginStatus* status)
{
    int choice;

    while (1)
    {
        printf("\n===== 主菜单 =====\n");

        if (status->logged == false)
        {
            printf("1. 注册\n");
            printf("2. 登录\n");
            printf("3. 找回密码\n");
            printf("0. 退出\n");

            printf("请选择: ");
            scanf("%d", &choice);
            getchar();

            switch (choice)
            {
            case 1:
                registerUser();
                break;

            case 2:
                loginUser(status);
                break;

            case 3:
                findPassword();
                break;

            case 0:
                return;

            default:
                printf("无效选择！\n");
            }
        }
        else
        {
            printf("当前用户: %s (%s)\n", status->current.username, status->current.role);
            //strcmp为字符串比较函数
            if (strcmp(status->current.role, "admin") == 0)
            {
                printf("1. 进入功能菜单\n");
                printf("2. 修改密码\n");
                printf("3. 注销\n");
                printf("4. 修改教师信息\n");  // 管理员可修改教师信息
            }
            else if (strcmp(status->current.role, "teacher") == 0)
            {
                printf("1. 进入教师菜单\n");
                printf("2. 修改密码\n");
                printf("3. 注销\n");
            }
            else
            {
                printf("1. 进入学生菜单\n");
                printf("2. 修改密码\n");
                printf("3. 注销\n");
            }

            printf("请选择: ");
            scanf("%d", &choice);
            getchar();

            switch (choice)
            {
            case 1:
                if (strcmp(status->current.role, "admin") == 0)
                    adminMenu(status);
                else if (strcmp(status->current.role, "teacher") == 0)
                    teacherMenu(status);
                else
                    studentMenu(status);
                break;
            case 2:
                changePassword(status);
                break;

            case 3:
                logoutUser(status);//注销
                break;

            case 4:
                if (strcmp(status->current.role, "admin") == 0)
                {
                    modifyTeacherInfo(status);
                }  // 管理员修改教师信息
                else
                {
                    printf("无效选择！\n");
                }
                break;

            default:
                printf("无效选择！\n");
            }
        }
    }
}