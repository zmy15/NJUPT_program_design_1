#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<Windows.h>
#include"file.h"
#include"admin.h"
#include"student.h"

void print_facilities(cJSON* site_json, int year, int month, int day, int site_id, int start_hour, int end_hour) {
    const char* site_type;
    char* site_str;
    switch (site_id) {
    case 0:
        site_type = "badminton";
        site_str = "��ë��";
        break;
    case 1:
        site_type = "tennis";
        site_str = "����";
        break;
    case 2:
        site_type = "basketball";
        site_str = "����";
        break;
    case 3:
        site_type = "pingpang";
        site_str = "ƹ����";
        break;
    default:
        return;
    }

    char date_key[20];
    sprintf(date_key, "%d-%02d-%02d", year, month, day);
    cJSON* date_obj = cJSON_GetObjectItem(site_json, date_key);
    if (!date_obj) {
        printf("Error: No information available for the specified date.\n");
        return;
    }

    char time_key[10];
    sprintf(time_key, "%02d-%02d", start_hour, end_hour);
    cJSON* time_obj = cJSON_GetObjectItem(date_obj, time_key);
    if (!time_obj) {
        printf("Error: No information available for the specified time slot.\n");
        return;
    }
    cJSON* facility_obj = cJSON_GetObjectItem(time_obj, site_type);

    printf("�� %d ʱ�� %d ʱ�Ŀ��� %s:", start_hour, end_hour, site_str);
    int array_size = cJSON_GetArraySize(facility_obj);
    for (int i = 0; i < array_size; ++i) {
        cJSON* element = cJSON_GetArrayItem(facility_obj, i);
        if (cJSON_IsNumber(element) && cJSON_GetNumberValue(element) == 0) {
            printf("%d ", i + 1); // ������õĳ��ر��
        }
    }
    printf("\n");
    printf("�� %d ʱ�� %d ʱ��ռ�� %s:", start_hour, end_hour, site_str);
    for (int i = 0; i < array_size; ++i) {
        cJSON* element = cJSON_GetArrayItem(facility_obj, i);
        if (cJSON_GetNumberValue(element) == 1) {
            printf("%d ", i + 1); // ���ռ�õĳ��ر��
        }
    }
    printf("\n");
    printf("�� %d ʱ�� %d ʱ�Ĺ��� %s:", start_hour, end_hour, site_str);
    for (int i = 0; i < array_size; ++i) {
        cJSON* element = cJSON_GetArrayItem(facility_obj, i);
        if (cJSON_GetNumberValue(element) == 2) {
            printf("%d ", i + 1); // ������ϵĳ��ر��
        }
    }
    printf("\n");
}

void print_schedule(cJSON* site_json, int year, int month, int day, int start_hour, int end_hour) {
    char date_str[11];
    sprintf(date_str, "%d-%02d-%02d", year, month, day);
    printf("Daily schedule for %s from %d:00 to %d:00:\n", date_str, start_hour, end_hour);
    for (int site_id = 0; site_id < 4; ++site_id) {
        print_facilities(site_json, year, month, day, site_id, start_hour, end_hour);
    }
}

void remove_error_record(int site_id, int facility_id) {
    FILE* error_file = fopen("error.txt", "r");
    if (!error_file) {
        printf("Error: Unable to open error log file.\n");
        return;
    }

    FILE* temp_file = fopen("temp_error.txt", "w");
    if (!temp_file) {
        printf("Error: Unable to open temporary log file.\n");
        fclose(error_file);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), error_file)) {
        int current_site_id, current_facility_id;
        if (sscanf(line, "Site ID: %d, Facility ID: %d", &current_site_id, &current_facility_id) == 2) {
            if (current_site_id == site_id && current_facility_id == facility_id) {
                continue; // Skip the line corresponding to the fixed facility
            }
        }
        fputs(line, temp_file);
    }

    fclose(error_file);
    fclose(temp_file);

    remove("error.txt");
    rename("temp_error.txt", "error.txt");
}

void mark_facilities(cJSON* site_json, int site_id, int facility_id,int statue) {
    cJSON* date_key;
    cJSON_ArrayForEach(date_key, site_json) {
        cJSON* time_key;
        cJSON_ArrayForEach(time_key, date_key) {
            cJSON* facility = cJSON_GetObjectItem(time_key, "badminton"); // ��ȡָ���������͵�����
            if (!facility) {
                printf("Error: Unable to retrieve information.\n");
                continue;
            }

            cJSON_SetNumberValue(cJSON_GetArrayItem(facility, facility_id), statue); // ���ó���״̬
        }
    }
}

void site_info()
{
    printf("1.��Ϣ��ѯ\n2.����ά��\n3.������һ��\n4.�˳�ϵͳ\n");
    int choice;
    int site_id;
    int facility_id;
    int start_hour, end_hour;
    int year, month, day;
    scanf("%d", &choice);
    system("cls");
    if (choice == 2)
    {
        int site_id;
        int facility_id;
        int n,statue;

        printf("ѡ�񳡵� (0: ��ë��, 1: ����, 2: ����, 3: ƹ����):  ");
        scanf("%d", &site_id);

        printf("���볡�ر��: ");
        scanf("%d", &facility_id);

        printf("���볡��״̬: ");
        scanf("%d", &statue);
        char* site_data = read_file("site_info.json");
        if (!site_data) return 1;

        cJSON* site_json = cJSON_Parse(site_data);
        free(site_data);

        // ���� site_info.json �еĳ���״̬
        mark_facilities(site_json, site_id, facility_id,statue);
        if (statue == 0)
        {
            remove_error_record(site_id, facility_id);
        }
        else if (statue == 2)
        {
            record_error(site_id, facility_id);
        }
        // �����º�� site_info.json д���ļ�
        char* site_data_updated = cJSON_Print(site_json);
        write_file("site_info.json", site_data_updated);
        free(site_data_updated);

        // �ͷ� cJSON ����
        cJSON_Delete(site_json);

        printf("����ɳ��ظ��ģ�\n");
        printf("1.������һ��\n2.�˳�ϵͳ\n");
        scanf("%d", &n);
        if (n == 1) {
            system("cls");
            admin_interface();
        }
        else {
            return 0;
        }
        return 0;
    }
    else if (choice == 1)
    {
        printf("�������� (YYYY-MM-DD): ");
        scanf("%d-%d-%d", &year, &month, &day);
        printf("���뿪ʼʱ�� (9-20): ");
        scanf("%d", &start_hour);
        while (start_hour < 9 || start_hour > 20) {
            printf("Invalid start hour. Please enter again (9-20): ");
            scanf("%d", &start_hour);
        }

        printf("����ʱ�� (10-21): ");
        scanf("%d", &end_hour);
        while (end_hour < 10 || end_hour > 21) {
            printf("Invalid end hour. Please enter again (10-21): ");
            scanf("%d", &end_hour);
        }
        char* site_data = read_file("site_info.json");
        if (!site_data) return 1;

        cJSON* site_json = cJSON_Parse(site_data);
        free(site_data);
        print_schedule(site_json, year, month, day, start_hour, end_hour);
        printf("1.������һ��\n2.�˳�ϵͳ\n");
        int n;
        scanf("%d", &n);
        if (n == 1) {
            system("cls");
            admin_interface();
        }
        else {
            return 0;
        }
    }
    else if (choice == 3)
    {
        admin_interface();
    }
    else {
        return 0;
    }
    return 0;
}