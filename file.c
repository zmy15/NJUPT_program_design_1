#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "cJSON.h"
#include"main.h"

#define MAX_STUDENT 100

// ��ȡ JSON �ļ������� cJSON ����
cJSON* readJSONFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* json_str = (char*)malloc(file_size + 1);
    fread(json_str, 1, file_size, file);
    fclose(file);

    cJSON* root = cJSON_Parse(json_str);
    free(json_str);

    if (root == NULL) {
        printf("Error parsing JSON!\n");
        return NULL;
    }

    return root;
}

// �� cJSON ����д�� JSON �ļ�
int writeJSONFile(const char* filename, cJSON* root) {
    char* json_str = cJSON_Print(root);
    if (json_str == NULL) {
        printf("Error converting cJSON to string!\n");
        return 1;
    }

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        free(json_str);
        return 1;
    }

    fprintf(file, "%s\n", json_str);
    fclose(file);

    free(json_str);

    return 0;
}

//����UI����
void ui(char *file)
{
    FILE* fp;
    char ui[50];
    fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("ѧ����Ϣ�ļ�����ϵͳ�˳�!");
        return 1;
    }
    while (fgets(ui, sizeof(ui), fp) != NULL)
    {
        printf("%s", ui);
    }
    printf("\n");
    fclose(fp);
}

//������������
void Encrypted_input(STU *student)
{
    char ch;
    int i = 0;
    printf("���������룺");
    while (1) {
        ch = _getch();
        if (ch == '\r') {
            student->password[i] = '\0'; // ��������Ϻ󣬽������ַ�����ĩβ��Ϊ'\0'
            break;
        }
        else if (ch == '\b' && i > 0) {
            printf("\b \b"); // ������˸����ɾ����һ���ַ����������λ���ƻ�һ��λ��
            i--;
        }
        else {
            printf("*"); // ��ӡ*�ַ�������ʵ����������
            student->password[i++] = ch; // ��������ַ����浽�����ַ�����
        }
    }
    printf("\n");
}