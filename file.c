//file.c
//文件存储读写

/*
从文件导入导出数据
导出数据(教师端，管理员端？)
数据备份
学生、用户数据读写
*/

#define _CRT_SECURE_NO_WARNINGS
#include "file.h"
#include "student.h"
#include "utils.h"

//把当前内存里的学生数据保存到文件中
void saveStudents(Student* head) {
    FILE* fp = fopen("students.dat", "wb");//二进制读写，创建新文件
    if (fp == NULL) {
        printf("学生文件保存失败！\n");
        return;
    }

    Student* p = head;
    while (p) {
        fwrite(p, sizeof(Student), 1, fp);
        p = p->next;
    }

    fclose(fp);
}

//从student.dat文件中读取学生数据，并恢复成链表，最后返回链表头指针
Student* loadStudents() {
    FILE* fp = fopen("students.dat", "rb");//二进制读写，文件必须存在
    if (fp == NULL) {
        return NULL;
    }

    Student temp;
    Student* head = NULL;
    Student* tail = NULL;

    //fread二进制输入，从文件读取指定数量的数据块
    while (fread(&temp, sizeof(Student), 1, fp)) {
        Student* newNode = (Student*)malloc(sizeof(Student));
        if (!newNode) {
            printf("内存分配失败");
            return NULL;
        }
        *newNode = temp;
        newNode->next = NULL;

        if (head == NULL) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    fclose(fp);
    return head;
}

//把当前内存中的账号数据保存到文件
void saveUsers() {
    FILE* fp = fopen("users.dat", "wb");
    if (fp == NULL) {
        printf("用户文件保存失败！\n");
        return;
    }

    fwrite(&userCount, sizeof(int), 1, fp);
    fwrite(users, sizeof(User), userCount, fp);
    fclose(fp);
}

//从文件读取账号数据到内存
void loadUsers() {
    FILE* fp = fopen("users.dat", "rb");
    if (fp == NULL) {
        return;
    }

    fread(&userCount, sizeof(int), 1, fp);
    fread(users, sizeof(User), userCount, fp);
    fclose(fp);
}

//教师导出班级学生信息
void exportStudentsToTxt(Student* head)
{
    char className[50];

    printf("输入要导出的班级：");
    fgets(className, 50, stdin);
    className[strcspn(className, "\n")] = 0;  // 去掉输入的换行符

    FILE* fp = fopen("class_students.txt", "w");

    if (!fp)
    {
        printf("文件创建失败\n");
        return;
    }

    Student* p = head;

    while (p)
    {
        if (strcmp(p->className, className) == 0)
        {
            fprintf(fp, "%s %s %.2f\n", p->id, p->name, p->score);
        }
        p = p->next;
    }

    fclose(fp);
    printf("导出完成\n");
}

//管理员导出全部学生
void exportAllStudents(Student* head)
{
    FILE* fp = fopen("all_students.txt", "w");

    if (!fp)
    {
        printf("文件创建失败\n");
        return;
    }

    Student* p = head;

    while (p)
    {
        fprintf(fp, "%s %s %s %.2f\n",
            p->id,
            p->name,
            p->className,
            p->score);
        p = p->next;
    }

    fclose(fp);
    printf("全部导出完成\n");
}

//从txt导入用户（管理员）
void importUsersFromFile()
{
    FILE* fp = fopen("users.txt", "r");

    if (!fp)
    {
        return;
    }

    User temp;
    char pwd[MAX_PASSWORD];   //读取明文密码

    while (fscanf(fp, "%s %s %s",
        temp.username,
        pwd,
        temp.role) == 3)
    {
        if (userCount < MAX_USER)
        {
            //转换为加密密码
            temp.passwordHash = hashPassword(pwd);

            users[userCount++] = temp;
        }
    }

    fclose(fp);

    saveUsers();

    printf("用户导入成功\n");
}