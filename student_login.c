#define _CRT_SECURE_NO_WARNINGS 1
#include"main.h"
#include<stdio.h>
#include"cJSON.h"
#include"file.h"
#include"student.h"
#include<Windows.h>
#include<string.h>

#define MAX_STUDENTS 100

void student_login()  //ѧ����¼
{
	int n, i = -1;
	STU student_login;
	STU student[MAX_STUDENTS];
	int num_student;
	ui("student_login_ui.txt");  //UI����
	printf("������������");
	//ѧ��������Ϣ
	scanf("%s", &student_login.name);
	Encrypted_input(&student_login);
	printf("������ѧ�ţ�");
	scanf("%s", &student_login.ID);

	//�����ļ���Ϣ���ṹ������
	cJSON* root = readJSONFile("student_information.json");
	if (root != NULL) {
		num_student = parseJSONToStudents(root, student, MAX_STUDENTS);
		cJSON_Delete(root);
	}
	//�ж��˺������Ƿ���ȷ
	do
	{
		if (i < num_student)
		{
			i++;
		}
		else
		{
			printf("�˺Ż�������󣬵�¼ʧ�ܣ�");
			return 1;
		}
	} while (!(strcmp(student_login.name,student[i].name)==0 && strcmp(student_login.password,student[i].password)==0 && strcmp(student_login.ID, student[i].ID)== 0));
	printf("��¼�ɹ���");
	system("cls");
	student_interface();    //��¼�ɹ���ת��ѧ������
	return 0;
}