#define _CRT_SECURE_NO_WARNINGS 1
#include"main.h"
#include<stdio.h>
#include"cJSON.h"
#include<Windows.h>

void student_login()
{
	FILE* stu, * fp;
	int n;
	char ui[50];
	STU student;
	fp = fopen("student_login_ui.txt", "r");
	stu = fopen("student.json", "a+");
	if ((stu == NULL) || (fp == NULL))
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
	return 0;
}