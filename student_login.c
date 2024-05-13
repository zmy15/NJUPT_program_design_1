#define _CRT_SECURE_NO_WARNINGS 1
#include"main.h"
#include<stdio.h>
#include"cJSON.h"
#include<Windows.h>
#include<string.h>

#define MAX_STUDENT 100

void student_login()
{
	int n, i = -1;
	STU student_login;
	STU student[MAX_STUDENT];
	int num_student = 0;
	ui("student_login_ui.txt");
	printf("ÇëÊäÈëÐÕÃû£º");
	scanf("%s", &student_login.name);
	printf("ÇëÊäÈëÃÜÂë£º");
	scanf("%s", &student_login.password);
	printf("ÇëÊäÈëÑ§ºÅ£º");
	scanf("%s", &student_login.ID);
	cJSON* root = readJSONFile("student.json");
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
	do
	{
		if (i <= num_student)
		{
			i++;
		}
		else
		{
			printf("ÕËºÅ»òÃÜÂë´íÎó£¬µÇÂ¼Ê§°Ü£¡");
			cJSON_Delete(root);
			return 1;
		}
	} while (!(strcmp(student_login.name,student[i].name)==0 && strcmp(student_login.password,student[i].password)==0 && strcmp(student_login.ID, student[i].ID)== 0));
	printf("µÇÂ¼³É¹¦£¡");
	cJSON_Delete(root);
	return 0;
}