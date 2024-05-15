#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "cJSON.h"
#include"main.h"

#define MAX_STUDENTS 100

//读取json文件
cJSON* readJSONFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        cJSON* root = cJSON_CreateObject();
        writeJSONFile(filename, root);
        return root;
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


//写入json文件
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

//读取到结构体数组
int parseJSONToStudents(cJSON* root, STU students[], int max_students) {
    int num_students = 0;
    cJSON* student_id = NULL;

    cJSON_ArrayForEach(student_id, root) {
        if (num_students >= max_students) {
            printf("Maximum number of students reached!\n");
            break;
        }

        cJSON* password = cJSON_GetObjectItemCaseSensitive(student_id, "password");
        cJSON* name = cJSON_GetObjectItemCaseSensitive(student_id, "name");

        if (!cJSON_IsString(password) || !cJSON_IsString(name) ) {
            printf("Invalid JSON format for student ID: %s\n", student_id->string);
            continue;
        }

        strncpy(students[num_students].ID, student_id->string, sizeof(students[num_students].ID));
        strncpy(students[num_students].password, password->valuestring, sizeof(students[num_students].password));
        strncpy(students[num_students].name, name->valuestring, sizeof(students[num_students].name));

        num_students++;
    }

    return num_students;
}

//添加学生信息
void addStudentToJSON(cJSON* root, const STU* student) {
    cJSON* info = cJSON_CreateObject();
    cJSON_AddStringToObject(info, "password", student->password);
    cJSON_AddStringToObject(info, "name", student->name);
    cJSON_AddItemToObject(root, student->ID, info);
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
void Encrypted_input_STU(STU *student)
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

void Encrypted_input_ADMIN(ADMIN* admin)
{
    char ch;
    int i = 0;
    printf("请输入密码：");
    while (1) {
        ch = _getch();
        if (ch == '\r') {
            admin->password[i] = '\0'; // 在输入完毕后，将密码字符串的末尾置为'\0'
            break;
        }
        else if (ch == '\b' && i > 0) {
            printf("\b \b"); // 如果是退格键，删除上一个字符，并将光标位置移回一个位置
            i--;
        }
        else {
            printf("*"); // 打印*字符来代替实际输入内容
            admin->password[i++] = ch; // 将输入的字符保存到密码字符串中
        }
    }
    printf("\n");
}


char* read_file(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("无法打开文件\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = (char*)malloc(length + 1);
    if (content) {
        fread(content, 1, length, file);
        content[length] = '\0';
    }

    fclose(file);
    return content;
}

// 写入字符串内容到文件
void write_file(const char* filename, const char* content) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }

    fprintf(file, "%s", content);
    fclose(file);
}

void generate_student_files() {
    FILE* file;

    // 检查 student_information.json 文件是否存在，不存在则生成
    if ((file = fopen("student_information.json", "r")) == NULL) {
        printf("警告：student_information.json 文件不存在，将自动生成。\n");
        file = fopen("student_information.json", "w");
        if (file) {
            fputs("{}", file);
            fclose(file);
        }
        else {
            printf("无法生成 student_information.json 文件，请检查权限或磁盘空间。\n");
            exit(1);
        }
    }
    else {
        fclose(file);
    }

    // 检查 student_order.json 文件是否存在，不存在则生成
    if ((file = fopen("student_order.json", "r")) == NULL) {
        printf("警告：student_order.json 文件不存在，将自动生成。\n");
        file = fopen("student_order.json", "w");
        if (file) {
            fputs("{}", file);
            fclose(file);
        }
        else {
            printf("无法生成 student_order.json 文件，请检查权限或磁盘空间。\n");
            exit(1);
        }
    }
    else {
        fclose(file);
    }
}

int file_exists(const char* filename) 
{
    FILE* file;
    if ((file = fopen(filename, "r")) == NULL) {
        return 0;
    }
    fclose(file);
    return 1;
}