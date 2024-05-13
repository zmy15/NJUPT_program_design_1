#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

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

/*int main() {
    // ��ȡ���е� JSON �ļ�����
    cJSON* root = readJSONFile("persons.json");
    if (root == NULL) {
        printf("Error reading JSON file!\n");
        return 1;
    }

    // ����µ����ݵ� cJSON ���������
    cJSON* person = cJSON_CreateObject();
    cJSON_AddStringToObject(person, "name", "Charlie");
    cJSON_AddNumberToObject(person, "age", 40);
    cJSON_AddNumberToObject(person, "salary", 65000.0);
    cJSON_AddItemToArray(root, person);

    // �����º�� cJSON ����д�� JSON �ļ�
    if (writeJSONFile("persons.json", root) != 0) {
        printf("Error writing JSON file!\n");
        cJSON_Delete(root);
        return 1;
    }

    printf("Data updated and written to file (persons.json) successfully!\n");

    // �ͷ� cJSON ����
    cJSON_Delete(root);

    return 0;
}*/
