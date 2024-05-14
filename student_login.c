#define _CRT_SECURE_NO_WARNINGS 1
#include"main.h"
#include<stdio.h>
#include"cJSON.h"
#include"file.h"
#include"student.h"
#include<Windows.h>
#include<string.h>

#define MAX_STUDENT 100

void student_login()  //ѧ����¼
{
	int n, i = -1;
	STU student_login;
	STU student[MAX_STUDENT];
	int num_student = 0;
	ui("student_login_ui.txt");  //UI����
	printf("������������");
	//ѧ��������Ϣ
	scanf("%s", &student_login.name);
	Encrypted_input(&student_login);
	printf("������ѧ�ţ�");
	scanf("%s", &student_login.ID);
	//�����ļ���Ϣ���ṹ������
	cJSON* root = readJSONFile("student_information.json");
	if (root == NULL) {
		printf("Error reading JSON file!\n");
		return 1;
	}
	cJSON* student_json = NULL;
	cJSON_ArrayForEach(student_json, root) {
		if (num_student >= MAX_STUDENT) {
			printf("Maximum number of persons reached!\n");
			break;
		}

		cJSON* name = cJSON_GetObjectItemCaseSensitive(student_json, "name");
		cJSON* password = cJSON_GetObjectItemCaseSensitive(student_json, "password");
		cJSON* ID = cJSON_GetObjectItemCaseSensitive(student_json, "ID");

		if (!cJSON_IsString(name) || !cJSON_IsString(password) || !cJSON_IsString(ID)) {
			printf("Invalid JSON format!\n");
			continue;
		}

		strncpy(student[num_student].name, name->valuestring, sizeof(student[num_student].name));
		strncpy(student[num_student].password, password->valuestring, sizeof(student[num_student].password));
		strncpy(student[num_student].ID, ID->valuestring, sizeof(student[num_student].ID));

		num_student++;
	}
	//�ж��˺������Ƿ���ȷ
	do
	{
		if (i <= num_student)
		{
			i++;
		}
		else
		{
			printf("�˺Ż�������󣬵�¼ʧ�ܣ�");
			cJSON_Delete(root);
			return 1;
		}
	} while (!(strcmp(student_login.name,student[i].name)==0 && strcmp(student_login.password,student[i].password)==0 && strcmp(student_login.ID, student[i].ID)== 0));
	printf("��¼�ɹ���");

	cJSON_Delete(root);
	system("cls");
	student_interface();    //��¼�ɹ���ת��ѧ������
	return 0;
}