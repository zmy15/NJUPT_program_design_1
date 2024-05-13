#define _CRT_SECURE_NO_WARNINGS 1
#include"main.h"
#include<stdio.h>
#include"cJSON.h"
#include<Windows.h>

void student_sign_up()
{
	FILE* stu, * fp;
	int n;
	char ui[50];
	STU student;
	fp = fopen("student_sign_up_ui.txt", "r");
	stu = fopen("student.json", "a+");
	if ((stu == NULL)|| (fp == NULL))
	{
		printf("ѧ����Ϣ�ļ�����ϵͳ�˳�!");
		return 0;
	}
	while (fgets(ui, sizeof(ui), fp) != NULL)
	{
		printf("%s", ui);
	}
	printf("\n");
	printf("������������");
	scanf("%s", &student.name);
	printf("���������룺");
	scanf("%s", &student.password);
	printf("������ѧ�ţ�");
	scanf("%s", &student.ID);
	// ��ȡ���е� JSON �ļ�����
	cJSON* root = readJSONFile("student.json");
	if (root == NULL) {
		printf("Error reading JSON file!\n");
		return 1;
	}

	// ����µ����ݵ� cJSON ���������
	cJSON* student_add = cJSON_CreateObject();
	cJSON_AddStringToObject(student_add, "name", student.name);
	cJSON_AddStringToObject(student_add, "password", student.password);
	cJSON_AddStringToObject(student_add, "ID", student.ID);
	cJSON_AddItemToArray(root, student_add);

	// �����º�� cJSON ����д�� JSON �ļ�
	if (writeJSONFile("student.json", root) != 0) {
		printf("Error writing JSON file!\n");
		cJSON_Delete(root);
		return 1;
	}

	// �ͷ� cJSON ����
	cJSON_Delete(root);
	printf("ע��ɹ�����1���ص�¼����\n");
	fclose(fp);
	fclose(stu);
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