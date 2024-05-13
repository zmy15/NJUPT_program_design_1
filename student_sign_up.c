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
	// 读取已有的 JSON 文件内容
	cJSON* root = readJSONFile("student.json");
	if (root == NULL) {
		printf("Error reading JSON file!\n");
		return 1;
	}

	// 添加新的数据到 cJSON 数组对象中
	cJSON* student_add = cJSON_CreateObject();
	cJSON_AddStringToObject(student_add, "name", student.name);
	cJSON_AddStringToObject(student_add, "password", student.password);
	cJSON_AddStringToObject(student_add, "ID", student.ID);
	cJSON_AddItemToArray(root, student_add);

	// 将更新后的 cJSON 对象写入 JSON 文件
	if (writeJSONFile("student.json", root) != 0) {
		printf("Error writing JSON file!\n");
		cJSON_Delete(root);
		return 1;
	}

	// 释放 cJSON 对象
	cJSON_Delete(root);
	printf("注册成功！按1返回登录界面\n");
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