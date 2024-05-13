#define _CRT_SECURE_NO_WARNINGS 1
#include"main.h"
#include"file.h"

void admin_login()
{
	ADMIN admin_login;
	ui("admin_login_ui.txt");
	printf("请输入姓名：");
	scanf("%s", &admin_login.name);
	printf("请输入密码：");
	scanf("%s", &admin_login.password);
	printf("请输入工号：");
	scanf("%s", &admin_login.ID);

	return 0;
}