#define _CRT_SECURE_NO_WARNINGS 1
#include"file.h"
#include"admin.h"
#include<string.h>
#include<stdio.h>
#include<Windows.h>

void admin_login()//����Ա��¼
{
	ADMIN admin_login;
	ui("admin_login_ui.txt");//����UI����
	//��ȡ�û�����
	printf("������������");
	scanf("%s", &admin_login.name);
	Encrypted_input_ADMIN(&admin_login);
	printf("�����빤�ţ�");
	scanf("%s", &admin_login.ID);
	//���е�¼
	if (strcmp(admin_login.name, "admin")==0&& strcmp(admin_login.password, "password") == 0&& strcmp(admin_login.ID, "1234") == 0)
	{
		printf("��¼�ɹ���");
		system("cls");
		admin_interface();//����Ա����
	}
	else
	{
		printf("�˺Ż�������󣬵�¼ʧ�ܣ�");
		return 1;
	}
	return 0;
}