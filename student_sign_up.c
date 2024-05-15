#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include"file.h"
#include<Windows.h>

void student_sign_up()//学生注册
{
	STU student_sign_up;
	//获取用户输入
	printf("学生注册\n");
	printf("请输入姓名：");
	scanf("%s", &student_sign_up.name);
	Encrypted_input_STU(&student_sign_up);
	printf("请输入学号：");
	scanf("%s", &student_sign_up.ID);
	// 读取和写入已有的 JSON 文件内容
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
	//输入为1返回登录界面，否则退出
	printf("注册成功！按1返回登录界面\n");
	cJSON_Delete(root);
	int i;
	scanf("%d", &i);
	if (i == 1)
	{
		system("cls");
		_student_login();
	}
	else
	{
		return 0;
	}
	return 0;
}