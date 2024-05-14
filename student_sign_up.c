#define _CRT_SECURE_NO_WARNINGS 1
#include"main.h"
#include<stdio.h>
#include"cJSON.h"
#include"file.h"
#include<Windows.h>

void student_sign_up()//学生注册
{
	STU student_sign_up;
	int n;
	ui("student_sign_up_ui.txt");//绘制UI界面
	//获取用户输入
	printf("请输入姓名：");
	scanf("%s", &student_sign_up.name);
	Encrypted_input(&student_sign_up);
	printf("请输入学号：");
	scanf("%s", &student_sign_up.ID);
	// 读取和写入已有的 JSON 文件内容
	cJSON* root = readJSONFile("student_information.json");
	if (root == NULL) {
		printf("Error reading JSON file!\n");
		return 1;
	}
	cJSON* student_add = cJSON_CreateObject();
	cJSON_AddStringToObject(student_add, "name", student_sign_up.name);
	cJSON_AddStringToObject(student_add, "password", student_sign_up.password);
	cJSON_AddStringToObject(student_add, "ID", student_sign_up.ID);
	cJSON_AddItemToArray(root, student_add);
	if (writeJSONFile("student_information.json", root) != 0) {
		printf("Error writing JSON file!\n");
		cJSON_Delete(root);
		return 1;
	}
	cJSON_Delete(root);
	//输入为1返回登录界面，否则退出
	printf("注册成功！按1返回登录界面\n");
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