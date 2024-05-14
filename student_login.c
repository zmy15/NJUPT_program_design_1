#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include"file.h"
#include"student.h"
#include<Windows.h>
#include<string.h>

#define MAX_STUDENTS 100

void _student_login()  //学生登录
{
	int n, i = -1;
	STU student[MAX_STUDENTS];
	STU student_login;
	int num_student;
	ui("student_login_ui.txt");  //UI界面
	printf("请输入姓名：");
	//学生输入信息
	scanf("%s", &student_login.name);
	Encrypted_input_STU(&student_login);
	printf("请输入学号：");
	scanf("%s", &student_login.ID);

	//加载文件信息到结构体数组
	cJSON* root = readJSONFile("student_information.json");
	if (root != NULL) {
		num_student = parseJSONToStudents(root, student, MAX_STUDENTS);
		cJSON_Delete(root);
	}
	//判断账号密码是否正确
	do
	{
		if (i < num_student)
		{
			i++;
		}
		else
		{
			printf("账号或密码错误，登录失败！");
			return 1;
		}
	} while (!(strcmp(student_login.name,student[i].name)==0 && strcmp(student_login.password,student[i].password)==0 && strcmp(student_login.ID, student[i].ID)== 0));
	printf("登录成功！");
	copy_ID(&student_login.ID);
	system("cls");
	student_interface();    //登录成功跳转到学生界面
	return 0;
}