#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<Windows.h>
#include"file.h"
#include"admin.h"

void admin_interface()         //����Ա����
{
	ui("admin_ui.txt");
	int n;
	scanf("%d", &n);
	system("cls");
	//ѡ����
	switch (n)
	{
	case 1:
		site_info();//����ʹ�����ά��
		break;
	case 2:
		stu_order_info();//ԤԼѧ����Ϣ
		break;
	case 3:
		site_statistics_info();//��Ϣͳ��
		break;
	case 4:
		return 0;
		break;
	default:
		return 0;
	}
}