#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include"file.h"

void student_l_s()
{
	int n;
	ui("student_l_s_ui.txt");
	scanf("%d", &n);
	switch (n)
	{
	case 1:
		_student_login();
		break;
	case 2:
		student_sign_up();
		break;
	case 3:
		return 0;
		break;
	default:
		break;
	}
	return 0;
}