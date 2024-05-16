#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include "file.h"
#include <Windows.h>

int is_duplicate_student(cJSON* root, const char* student_id) {
    cJSON* student = cJSON_GetObjectItem(root, student_id);
    return student != NULL;
}

void student_sign_up() { //ѧ��ע��
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
        // ��ȡ�û�����
        printf("ѧ��ע��\n");
        printf("������������");
        scanf("%s", student_sign_up.name);
        Encrypted_input_STU(&student_sign_up);
        printf("������ѧ�ţ�");
        scanf("%s", student_sign_up.ID);

        // ���ѧ���Ƿ��ظ�
        if (is_duplicate_student(root, student_sign_up.ID)) {
            system("cls");
            printf("ѧ���Ѵ��ڣ����������룡\n");
            duplicate = 1;
            continue;
        }

        // �����ѧ���� JSON ��
        addStudentToJSON(root, &student_sign_up);

        // �����º�� JSON ����д���ļ�
        char* updated_file_content = cJSON_Print(root);
        write_file("student_information.json", updated_file_content);
        cJSON_free(updated_file_content);

        printf("ע��ɹ�����1���ص�¼����\n");
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
