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
		site_maintenance();//����ά��
		break;
	case 2:
		site_info();//����ʹ�����
		break;
	case 3:
		stu_order_info();//ԤԼѧ����Ϣ
		break;
	case 4:
		site_statistics_info();//��Ϣͳ��
		break;
	case 5:
		return 0;
		break;
	default:
		return 0;
	}
}