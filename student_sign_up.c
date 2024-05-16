#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include "file.h"
#include <Windows.h>

int is_duplicate_student(cJSON* root, const char* student_id) {
    cJSON* student = cJSON_GetObjectItem(root, student_id);
    return student != NULL;
}

void student_sign_up() { //学生注册
    STU student_sign_up;
    int duplicate;
    cJSON* root;

    // Load existing student data from the JSON file
    char* file_content = read_file("student_information.json");
    if (file_content == NULL) {
        printf("Error reading JSON file!\n");
        return;
    }
    root = cJSON_Parse(file_content);
    free(file_content);
    if (root == NULL) {
        printf("Error parsing JSON file!\n");
        return;
    }

    do {
        duplicate = 0;
        // 获取用户输入
        printf("学生注册\n");
        printf("请输入姓名：");
        scanf("%s", student_sign_up.name);
        Encrypted_input_STU(&student_sign_up);
        printf("请输入学号：");
        scanf("%s", student_sign_up.ID);

        // 检查学号是否重复
        if (is_duplicate_student(root, student_sign_up.ID)) {
            system("cls");
            printf("学号已存在，请重新输入！\n");
            duplicate = 1;
            continue;
        }

        // 添加新学生到 JSON 中
        addStudentToJSON(root, &student_sign_up);

        // 将更新后的 JSON 数据写回文件
        char* updated_file_content = cJSON_Print(root);
        write_file("student_information.json", updated_file_content);
        cJSON_free(updated_file_content);

        printf("注册成功！按1返回登录界面\n");
        int i;
        scanf("%d", &i);
        if (i == 1) {
            system("cls");
            _student_login();
        }
        else {
            cJSON_Delete(root);
            return;
        }
    } while (duplicate);

    cJSON_Delete(root);
    return;
}
