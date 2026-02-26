//菜单接口

#ifndef MENU_H
#define MENU_H

#include "user.h"

void mainMenu(LoginStatus* status);
void adminMenu(LoginStatus* status);
void teacherMenu(LoginStatus* status);
void studentMenu(LoginStatus* status);

#endif