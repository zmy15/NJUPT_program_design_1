#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "cJSON.h"
#include"main.h"

#define MAX_STUDENT 100

// 读取 JSON 文件并返回 cJSON 对象
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

// 将 cJSON 对象写入 JSON 文件
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

//绘制UI界面
void ui(char *file)
{
    FILE* fp;
    char ui[50];
    fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("学生信息文件错误，系统退出!");
        return 1;
    }
    while (fgets(ui, sizeof(ui), fp) != NULL)
    {
        printf("%s", ui);
    }
    printf("\n");
    fclose(fp);
}

//密码密文输入
void Encrypted_input(STU *student)
{
    char ch;
    int i = 0;
    printf("请输入密码：");
    while (1) {
        ch = _getch();
        if (ch == '\r') {
            student->password[i] = '\0'; // 在输入完毕后，将密码字符串的末尾置为'\0'
            break;
        }
        else if (ch == '\b' && i > 0) {
            printf("\b \b"); // 如果是退格键，删除上一个字符，并将光标位置移回一个位置
            i--;
        }
        else {
            printf("*"); // 打印*字符来代替实际输入内容
            student->password[i++] = ch; // 将输入的字符保存到密码字符串中
        }
    }
    printf("\n");
}