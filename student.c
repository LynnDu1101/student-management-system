/*
学生端：成绩查询，分析，排名
教师端：增删改查学生，成绩统计
缺：学生信息下载至文件
*/
//学生数据管理
#define _CRT_SECURE_NO_WARNINGS     
#include "student.h"

Appeal* appealHead = NULL;

//学生提交申诉
void submitAppeal()
{
    Appeal* a = malloc(sizeof(Appeal));

    printf("输入学号:");
    fgets(a->studentId, 20, stdin);
    a->studentId[strcspn(a->studentId, "\n")] = 0;

    printf("申诉理由:");
    fgets(a->reason, 100, stdin);
    a->reason[strcspn(a->reason, "\n")] = 0;

    a->processed = 0;   //标记是否处理
    a->next = appealHead;
    appealHead = a;

    printf("申诉已提交\n");
}

//管理员处理申诉
void processAppeal()
{
    Appeal* p = appealHead;

    if (!p)
    {
        printf("暂无申诉\n");
        return;
    }

    while (p)
    {
        if (!p->processed)
        {
            printf("学号:%s\n理由:%s\n",
                p->studentId,
                p->reason);

            printf("是否处理(1是):");

            int c;
            scanf("%d", &c);
            getchar();

            if (c == 1)
                p->processed = 1;
        }
        p = p->next;
    }
}

Student* createStudent() {
    Student* s = (Student*)malloc(sizeof(Student));
    printf("学号: ");
    fgets(s->id, MAX_ID, stdin);
    s->id[strcspn(s->id, "\n")] = 0;

    printf("姓名: ");
    fgets(s->name, MAX_NAME, stdin);
    s->name[strcspn(s->name, "\n")] = 0;

    printf("年龄: ");
    scanf("%d", &s->age);
    getchar();

    printf("性别: ");
    fgets(s->gender, 10, stdin);
    s->gender[strcspn(s->gender, "\n")] = 0;

    printf("专业: ");
    fgets(s->major, MAX_MAJOR, stdin);
    s->major[strcspn(s->major, "\n")] = 0;

    printf("班级: ");
    fgets(s->className, MAX_CLASS, stdin);
    s->className[strcspn(s->className, "\n")] = 0;

    printf("成绩: ");
    scanf("%f", &s->score);
    getchar();

    printf("电话: ");
    fgets(s->phone, MAX_PHONE, stdin);
    s->phone[strcspn(s->phone, "\n")] = 0;

    printf("邮箱: ");
    fgets(s->email, MAX_EMAIL, stdin);
    s->email[strcspn(s->email, "\n")] = 0;

    s->next = NULL;
    return s;
}

void addStudent(Student** head) {
    Student* newS = createStudent();
    newS->next = *head;
    *head = newS;
    printf("添加成功！\n");
}

Student* findById(Student* head, const char* id) {
    while (head) {
        if (strcmp(head->id, id) == 0) return head;
        head = head->next;
    }
    return NULL;
}

void deleteStudent(Student** head) {
    char id[MAX_ID];
    printf("输入删除学号: ");
    fgets(id, MAX_ID, stdin);
    id[strcspn(id, "\n")] = 0;

    Student* p = *head, * pre = NULL;

    while (p) {
        if (strcmp(p->id, id) == 0) {
            if (pre) pre->next = p->next;
            else *head = p->next;
            free(p);
            printf("删除成功\n");
            return;
        }
        pre = p;
        p = p->next;
    }
    printf("未找到学生\n");
}

void modifyStudent(Student* head) {
    char id[MAX_ID];
    printf("输入修改学号: ");
    fgets(id, MAX_ID, stdin);
    id[strcspn(id, "\n")] = 0;

    Student* s = findById(head, id);
    if (!s) {
        printf("未找到\n");
        return;
    }

    printf("新姓名: ");
    fgets(s->name, MAX_NAME, stdin);
    s->name[strcspn(s->name, "\n")] = 0;

    printf("新成绩: ");
    scanf("%f", &s->score);
    getchar();

    printf("修改完成\n");
}

void searchStudent(Student* head) {
    char id[MAX_ID];
    printf("输入学号查询: ");
    fgets(id, MAX_ID, stdin);
    id[strcspn(id, "\n")] = 0;

    Student* s = findById(head, id);
    if (!s) {
        printf("未找到\n");
        return;
    }

    printf("学号:%s 姓名:%s 成绩:%.2f\n", s->id, s->name, s->score);
}

void showAllStudents(Student* head) {
    printf("\n====学生列表====\n");
    while (head) {
        printf("%s %s %.2f\n", head->id, head->name, head->score);
        head = head->next;
    }
}

void sortStudents(Student** head) {
    if (!*head) return;  // 如果链表为空，返回

    int swapped;
    Student* ptr;
    Student* lptr = NULL;

    do {
        swapped = 0;
        ptr = *head;

        // 遍历链表
        while (ptr->next != lptr) {
            // 如果当前节点的成绩小于下一个节点，交换它们
            if (ptr->score < ptr->next->score) {
                // 交换节点的指针，而不是数据
                Student* temp = ptr->next;  // 保存当前节点的下一个节点
                ptr->next = temp->next;     // 当前节点指向下一个节点的下一个节点
                temp->next = *head;         // 下一个节点指向链表的头节点
                *head = temp;               // 更新头指针，指向新交换的节点

                swapped = 1;
            }
            ptr = ptr->next;
        }
        lptr = ptr;  // 更新已排序区域的指针
    } while (swapped);

    printf("排序完成\n");
}


//统计数据
void statisticsStudents(Student* head) {
    if (!head) return;

    int count = 0;
    float sum = 0, max = head->score, min = head->score;
    Student* p = head;
    while (p) {
        count++;
        sum += p->score;
        if (p->score > max) max = p->score;
        if (p->score < min) min = p->score;
        p = p->next;
    }

    printf("人数:%d\n", count);
    printf("平均成绩:%.2f\n", sum / count);
    printf("最高:%.2f 最低:%.2f\n", max, min);
}

void freeStudents(Student* head) {
    Student* p;
    while (head) {
        p = head;
        head = head->next;
        free(p);
    }
}