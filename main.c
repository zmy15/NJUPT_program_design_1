#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<Windows.h>
#include"main.h"
#include"file.h"

int main()
{
	int n;
	ui("login_ui.txt"); //绘制主界面UI
	scanf("%d",&n);
	system("cls");
	//处理用户选择功能
	switch (n)
	{
	case 1:
		student_login();//学生登录
		break;
	case 2:
		student_sign_up();//学生注册
		break;
	case 3:
		admin_login();//管理员登录
		break;
	case 4:
		return 1;//退出系统
		break;
	default:
		return 1;
		break;
	}
	return 0;
}