#define _CRT_SECURE_NO_WARNINGS 1
#include"main.h"
#include<stdio.h>

void student_sign_up()
{
	FILE* stu, * fp;
	char ui[50];
	STU student;
	fp = fopen("student_sign_up_ui.txt", "r");
	stu = fopen("student.txt", "w");
	if ((stu == NULL)|| (fp == NULL))
	{
		printf("学生信息文件错误，系统退出!");
		return 0;
	}
	while (fgets(ui, sizeof(ui), fp) != NULL)
	{
		printf("%s", ui);
	}
	printf("\n");
	printf("请输入姓名：");
	scanf("%s", &student.name);
	printf("请输入密码：");
	scanf("%s", &student.password);
	printf("请输入学号：");
	scanf("%s", &student.ID);
	fprintf(stu, "name:%s\n", student.name);
	fprintf(stu, "password:%s\n", student.password);
	fprintf(stu, "ID:%s\n", student.ID);
	fclose(fp);
	fclose(stu);
	return 0;
}