#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<Windows.h>
#include"file.h"

int main()
{
	int n;
	generate_student_files();
	// 检查 site_info.json 文件是否存在，不存在则退出系统
	if (!file_exists("site_info.json")) {
		printf("错误：site_info.json 文件不存在，系统无法启动。\n");
		printf("按任意键退出...");
		getchar(); // 等待用户按下任意键
		return 1;
	}
	update_site_info();
	ui("login_ui.txt"); //绘制主界面UI
	scanf("%d", &n);
	system("cls");
	//处理用户选择功能
	switch (n)
	{
	case 1:
		student_l_s();//学生登录注册
		break;
	case 2:
		admin_login();//管理员登录
		break;
	case 3:
		return 1;//退出系统
		break;
	default:
		return 1;
		break;
	}
	return 0;
}