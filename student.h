//学生模块接口定义
#ifndef STUDENT_H//防止一段代码被重复包含
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_ID 20
#define MAX_MAJOR 50
#define MAX_CLASS 30
#define MAX_PHONE 20
#define MAX_EMAIL 50

typedef struct Student {
    char id[MAX_ID];
    char name[MAX_NAME];
    int age;
    char gender[10];
    char major[MAX_MAJOR];
    char className[MAX_CLASS];
    float score;
    char phone[MAX_PHONE];
    char email[MAX_EMAIL];
    struct Student* next;
} Student;

typedef struct Appeal
{
    char studentId[20];
    char reason[100];
    int processed;
    struct Appeal* next;
} Appeal;

extern Appeal* appealHead;

void submitAppeal();
void processAppeal();


extern Student* head;     // 声明全局变量head，声明

Student* createStudent();
void addStudent(Student** head);
void deleteStudent(Student** head);
void modifyStudent(Student* head);//修改
void searchStudent(Student* head);
void showAllStudents(Student* head);
void sortStudents(Student** head);
void statisticsStudents(Student* head);//统计学生
void freeStudents(Student* head);
Student* findById(Student* head, const char* id);

#endif
