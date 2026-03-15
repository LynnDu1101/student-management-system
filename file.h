//file.h
//文件模块接口

#ifndef FILE_H
#define FILE_H

#include "student.h"
#include "user.h"

void saveStudents(Student* head);//把当前内存里的学生数据保存到文件中
Student* loadStudents();  //从student.dat文件中读取学生数据至内存中

void saveUsers();//把当前内存中的账号数据保存到文件
void loadUsers();//从文件读取账号数据到内存

void exportStudentsToTxt(Student* head);     // 教师导出
void exportAllStudents(Student* head);       // 管理员导出
void importUsersFromFile();                  // 管理员导入

#endif
