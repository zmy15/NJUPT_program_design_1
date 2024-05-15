#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<Windows.h>
#include"file.h"
#include"admin.h"

// ״̬ת��Ϊ����
const char* status_to_string(int status) {
    switch (status) {
    case 0: return "����";
    case 1: return "ռ��";
    case 2: return "����";
    default: return "δ֪";
    }
}

// ��ʾ������Ϣ
void display_facilities(cJSON* root, const char* facility_name) {
    cJSON* facility_array = cJSON_GetObjectItem(root, facility_name);
    if (facility_array) {
        printf("%s:\n", facility_name);
        int count = cJSON_GetArraySize(facility_array);
        for (int i = 0; i < count; i++) {
            cJSON* court = cJSON_GetArrayItem(facility_array, i);
            int id = cJSON_GetObjectItem(court, "facility_id")->valueint;
            int status = cJSON_GetObjectItem(court, "status")->valueint;
            printf("  ���ر��: %d, ״̬: %s\n", id, status_to_string(status));
        }
    }
    else {
        printf("δ�ҵ��������� %s\n", facility_name);
    }
}

// ���ĳ���״̬
void change_status(cJSON* root, const char* facility_name, int court_id, int new_status) {
    cJSON* facility_array = cJSON_GetObjectItem(root, facility_name);
    if (facility_array) {
        int count = cJSON_GetArraySize(facility_array);
        for (int i = 0; i < count; i++) {
            cJSON* court = cJSON_GetArrayItem(facility_array, i);
            int id = cJSON_GetObjectItem(court, "facility_id")->valueint;
            if (id == court_id) {
                cJSON* status_item = cJSON_GetObjectItem(court, "status");
                status_item->valueint = new_status;
                printf("%s %d ��״̬�Ѹ���Ϊ %s\n", facility_name, court_id, status_to_string(new_status));
                return;
            }
        }
        printf("δ�ҵ� %s ���Ϊ %d �ĳ���\n", facility_name, court_id);
    }
    else {
        printf("δ�ҵ��������� %s\n", facility_name);
    }
}

void site_info()
{
    char* json_string = read_file("site_info.json");
    if (json_string == NULL) {
        return 1;
    }

    // ����JSON�ַ���
    cJSON* root = cJSON_Parse(json_string);
    if (root == NULL) {
        printf("JSON����ʧ��\n");
        free(json_string);
        return 1;
    }

    // ��ʾ�˵����û�����
    int choice;
    int court_id, new_status;
    const char* facility_names[] = { "badminton", "tennis", "basketball", "pingpang" };
    //const char* facility_names[] = { "��ë��", "����", "����", "ƹ����" };
    int facility_count = sizeof(facility_names) / sizeof(facility_names[0]);

    while (1) {
        printf("\n��ѡ�񳡵�����:\n");
        for (int i = 0; i < facility_count; i++) {
            printf("%d. %s\n", i + 1, facility_names[i]);
        }
        printf("%d. ������һ���˵�\n", facility_count + 1);
        printf("ѡ��һ��ѡ��: ");
        scanf("%d", &choice);
        system("cls");

        if (choice >= 1 && choice <= facility_count) {
            const char* facility_name = facility_names[choice - 1];
            display_facilities(root, facility_name);

            while (1) {
                printf("\n1. ���ĳ���״̬\n");
                printf("2. ������һ���˵�\n");
                printf("ѡ��һ��ѡ��: ");
                scanf("%d", &choice);
                system("cls");

                if (choice == 1) {
                    printf("���볡�ر��: ");
                    scanf("%d", &court_id);
                    printf("������״̬ (0: ����, 1: ռ��, 2: ����): ");
                    scanf("%d", &new_status);
                    change_status(root, facility_name, court_id, new_status);
                    display_facilities(root, facility_name);
                }
                else if (choice == 2) {
                    break;
                }
                else {
                    printf("��Чѡ��\n");
                }
            }

        }
        else if (choice == facility_count + 1) {
            // ���º��JSON�ַ���
            char* updated_json_string = cJSON_Print(root);
            // �����º��JSON�ַ���д���ļ�
            write_file("sports_facility_status.json", updated_json_string);
            // �ͷ��ڴ�
            free(updated_json_string);
            cJSON_Delete(root);
            free(json_string);
            break;
        }
        else {
            printf("��Чѡ��\n");
        }
    }
    admin_interface();
}