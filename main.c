#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<Windows.h>
#include"main.h"

int main()
{
	FILE* fp;
	char ui[50];
	int n;
	fp = fopen("login_ui.txt", "r");
	if (fp == NULL)
	{
		printf("ϵͳ��¼�ļ�����ϵͳ�˳�!");
		fclose(fp);
		return 1;
	}
	while (fgets(ui, sizeof(ui), fp) != NULL)
	{
		printf("%s", ui);
	}
	printf("\n");
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
	fclose(fp);
	return 0;
}