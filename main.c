#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<Windows.h>
#include"main.h"
#include"file.h"

int main()
{
	int n;
	ui("login_ui.txt"); //����������UI
	scanf("%d",&n);
	system("cls");
	//�����û�ѡ����
	switch (n)
	{
	case 1:
		student_login();//ѧ����¼
		break;
	case 2:
		student_sign_up();//ѧ��ע��
		break;
	case 3:
		admin_login();//����Ա��¼
		break;
	case 4:
		return 1;//�˳�ϵͳ
		break;
	default:
		return 1;
		break;
	}
	return 0;
}