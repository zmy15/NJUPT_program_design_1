#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<Windows.h>
#include"file.h"

int main()
{
	int n;
	generate_student_files();
	// ��� site_info.json �ļ��Ƿ���ڣ����������˳�ϵͳ
	if (!file_exists("site_info.json")) {
		printf("����site_info.json �ļ������ڣ�ϵͳ�޷�������\n");
		printf("��������˳�...");
		getchar(); // �ȴ��û����������
		return 1;
	}
	update_site_info();
	ui("login_ui.txt"); //����������UI
	scanf("%d", &n);
	system("cls");
	//�����û�ѡ����
	switch (n)
	{
	case 1:
		student_l_s();//ѧ����¼ע��
		break;
	case 2:
		admin_login();//����Ա��¼
		break;
	case 3:
		return 1;//�˳�ϵͳ
		break;
	default:
		return 1;
		break;
	}
	return 0;
}