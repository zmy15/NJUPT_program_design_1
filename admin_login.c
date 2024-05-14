#define _CRT_SECURE_NO_WARNINGS 1
#include"file.h"
#include"admin.h"
#include<string.h>
#include<stdio.h>
#include<Windows.h>

void admin_login()//管理员登录
{
	ADMIN admin_login;
	ui("admin_login_ui.txt");//绘制UI界面
	//获取用户输入
	printf("请输入姓名：");
	scanf("%s", &admin_login.name);
	Encrypted_input_ADMIN(&admin_login);
	printf("请输入工号：");
	scanf("%s", &admin_login.ID);
	//进行登录
	if (strcmp(admin_login.name, "admin")==0&& strcmp(admin_login.password, "password") == 0&& strcmp(admin_login.ID, "1234") == 0)
	{
		printf("登录成功！");
		system("cls");
		admin_interface();//管理员界面
	}
	else
	{
		printf("账号或密码错误，登录失败！");
		return 1;
	}
	return 0;
}