#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<Windows.h>
#include"file.h"
#include"admin.h"

void admin_interface()         //管理员界面
{
	ui("admin_ui.txt");
	int n;
	scanf("%d", &n);
	system("cls");
	//选择功能
	switch (n)
	{
	case 1:
		site_info();//场地使用情况维护
		break;
	case 2:
		stu_order_info();//预约学生信息
		break;
	case 3:
		site_statistics_info();//信息统计
		break;
	case 4:
		return 0;
		break;
	default:
		return 0;
	}
}