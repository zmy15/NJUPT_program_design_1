#define _CRT_SECURE_NO_WARNINGS 1
#include"student.h"
#include<stdio.h>
#include"file.h"
#include<Windows.h>

void student_interface()         //�û�����
{
	ui("student_ui.txt");
	int n;
	scanf("%d", &n);
	system("cls");
	//ѡ����
	switch (n)
	{
	case 1:
		student_site_info();
		break;
	case 2:
		student_order();
		break;
	case 3:
		report_error();
		break;
	case 4:
		return 0;
		break;
	default:
		return 0;
	}
}
