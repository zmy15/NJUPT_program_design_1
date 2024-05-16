#define _CRT_SECURE_NO_WARNINGS 1
#include "student.h"
#include "file.h"
#include <stdio.h>
#include <Windows.h>
#include <time.h>

void mark_facilities_as_faulty(cJSON* site_json, int site_id, int facility_id) {
    cJSON* date_key;
    cJSON_ArrayForEach(date_key, site_json) {
        cJSON* time_key;
        cJSON_ArrayForEach(time_key, date_key) {
            cJSON* facility = cJSON_GetObjectItem(time_key, "badminton"); // ��ȡָ���������͵�����
            if (!facility) {
                printf("Error: Unable to retrieve facility information.\n");
                continue;
            }

            cJSON_SetNumberValue(cJSON_GetArrayItem(facility, facility_id), 2); // ���ó���״̬Ϊ����
        }
    }
}

void record_error(int site_id, int facility_id) {
    FILE* error_file = fopen("error.txt", "a");
    if (!error_file) {
        printf("Error: Unable to open error log file.\n");
        return;
    }

    time_t now = time(NULL);
    struct tm* local_time = localtime(&now);

    fprintf(error_file, "Site ID: %d, Facility ID: %d, Reported at: %02d-%02d-%04d %02d:%02d:%02d\n",
        site_id, facility_id, local_time->tm_mday, local_time->tm_mon + 1,
        local_time->tm_year + 1900, local_time->tm_hour, local_time->tm_min,
        local_time->tm_sec);

    fclose(error_file);
}

void report_error() {
    int site_id;
    int facility_id;
    int n;

    printf("ѡ�񳡵� (0: ��ë��, 1: ����, 2: ����, 3: ƹ����): ");
    scanf("%d", &site_id);

    printf("���볡�ر��: ");
    scanf("%d", &facility_id);

    char* site_data = read_file("site_info.json");
    if (!site_data) return;

    cJSON* site_json = cJSON_Parse(site_data);
    free(site_data);

    // ���� site_info.json �еĳ���״̬Ϊ 2����Ҫά�ޣ�
    mark_facilities_as_faulty(site_json, site_id, facility_id);

    // �����º�� site_info.json д���ļ�
    char* site_data_updated = cJSON_Print(site_json);
    write_file("site_info.json", site_data_updated);
    free(site_data_updated);

    // ��¼������Ϣ�� error.txt ��
    record_error(site_id, facility_id);

    // �ͷ� cJSON ����
    cJSON_Delete(site_json);

    printf("�ѱ��泡�ع��ϣ�\n");
    printf("1.������һ��\n2.�˳�ϵͳ\n");
    scanf("%d", &n);
    if (n == 1) {
        system("cls");
        student_interface();
    }
    else {
        exit(0);
    }
}
