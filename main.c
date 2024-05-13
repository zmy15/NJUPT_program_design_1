#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<Windows.h>
#include"main.h"
#include"file.h"

int main()
{
	int n;
	ui("login_ui.txt");
	scanf("%d",&n);
	system("cls");
	switch (n)
	{
	case 1:
		student_login();
		break;
	case 2:
		student_sign_up();
		break;
	case 3:
		admin_login();
		break;
	case 4:
		return 1;
		break;
	default:
		return 1;
		break;
	}
	return 0;
}