#define _CRT_SECURE_NO_WARNINGS 1
#include"main.h"
#include"file.h"

void admin_login()
{
	ADMIN admin_login;
	ui("admin_login_ui.txt");
	printf("������������");
	scanf("%s", &admin_login.name);
	printf("���������룺");
	scanf("%s", &admin_login.password);
	printf("�����빤�ţ�");
	scanf("%s", &admin_login.ID);

	return 0;
}