#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include"file.h"
#include<Windows.h>

void student_sign_up()//ѧ��ע��
{
	STU student_sign_up;
	int n;
	ui("student_sign_up_ui.txt");//����UI����
	//��ȡ�û�����
	printf("������������");
	scanf("%s", &student_sign_up.name);
	Encrypted_input_STU(&student_sign_up);
	printf("������ѧ�ţ�");
	scanf("%s", &student_sign_up.ID);
	student_sign_up.basketball = 0;
	student_sign_up.badminton = 0;
	student_sign_up.pingpang = 0;
	// ��ȡ��д�����е� JSON �ļ�����
	cJSON* root = readJSONFile("student_information.json");
	if (root == NULL) {
		printf("Error reading JSON file!\n");
		return 1;
	}
	addStudentToJSON(root, &student_sign_up);
	if (writeJSONFile("student_information.json", root) != 0) {
		printf("Error writing JSON file!\n");
		cJSON_Delete(root);
		return 1;
	}
	//����Ϊ1���ص�¼���棬�����˳�
	printf("ע��ɹ�����1���ص�¼����\n");
	cJSON_Delete(root);
	scanf("%d", &n);
	if (n == 1)
	{
		system("cls");
		student_login();
	}
	else 
	{
		return 0;
	}
	return 0;
}