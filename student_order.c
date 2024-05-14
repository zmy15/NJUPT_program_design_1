#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cJSON.h"
#include"main.h"


// ��ȡ�ļ����ݵ��ַ���
char* read_file_order(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("�޷����ļ�\n");
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

// д���ַ������ݵ��ļ�
void write_file_order(const char* filename, const char* content) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return;
    }

    fprintf(file, "%s", content);
    fclose(file);
}

// ���ѧ��ԤԼ���鵽JSON�ļ�
void add_reservation(cJSON* root, const Reservation* reservation) {
    cJSON* reservations = cJSON_GetObjectItem(root, "reservations");
    if (reservations == NULL) {
        reservations = cJSON_CreateArray();
        cJSON_AddItemToObject(root, "reservations", reservations);
    }

    cJSON* reservation_obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(reservation_obj, "student_id", reservation->student_id);
    cJSON_AddNumberToObject(reservation_obj, "facility_id", reservation->facility_id);
    cJSON_AddNumberToObject(reservation_obj, "year", reservation->year);
    cJSON_AddNumberToObject(reservation_obj, "month", reservation->month);
    cJSON_AddNumberToObject(reservation_obj, "day", reservation->day);
    cJSON_AddNumberToObject(reservation_obj, "start_hour", reservation->start_hour);
    cJSON_AddNumberToObject(reservation_obj, "end_hour", reservation->end_hour);

    cJSON_AddItemToArray(reservations, reservation_obj);
}

// ��ȡ��ǰ���ں�ʱ��
void get_current_time(int* year, int* month, int* day, int* hour) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    *year = tm.tm_year + 1900;
    *month = tm.tm_mon + 1;
    *day = tm.tm_mday;
    *hour = tm.tm_hour;
}

// ����ѧ��ԤԼ�ͳ���ռ��״̬�Ĺ���
void process_reservation(cJSON* facility_status, cJSON* student_data, Reservation* reservation) {
    int current_year, current_month, current_day, current_hour;
    get_current_time(&current_year, &current_month, &current_day, &current_hour);

    // ����Ƿ���ԤԼ���ڵ�7����
    if (reservation->year < current_year ||
        (reservation->year == current_year && reservation->month < current_month) ||
        (reservation->year == current_year && reservation->month == current_month && reservation->day <= current_day + 7)) {

        // ��鳡��״̬
        cJSON* facility_array = cJSON_GetObjectItem(facility_status, "facility");
        if (facility_array) {
            int count = cJSON_GetArraySize(facility_array);
            for (int i = 0; i < count; i++) {
                cJSON* court = cJSON_GetArrayItem(facility_array, i);
                int id = cJSON_GetObjectItem(court, "id")->valueint;
                if (id == reservation->facility_id) {
                    cJSON* status_item = cJSON_GetObjectItem(court, "status");
                    int status = status_item->valueint;
                    if (status == 0) {
                        // ���ؿ��У�����ԤԼ
                        add_reservation(student_data, reservation);
                        printf("ѧ��ID %d �ɹ�ԤԼ�˳���ID %d\n", reservation->student_id, reservation->facility_id);
                    }
                    else {
                        printf("����ID %d �ѱ�ռ��\n", reservation->facility_id);
                    }
                    return;
                }
            }
            printf("δ�ҵ�����ID %d\n", reservation->facility_id);
        }
        else {
            printf("δ�ҵ�������Ϣ\n");
        }
    }
    else {
        printf("ֻ����ǰ7����ԤԼ����\n");
    }
}
