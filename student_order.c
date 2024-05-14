#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cJSON.h"
#include"main.h"


// 读取文件内容到字符串
char* read_file_order(const char* filename) {
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
void write_file_order(const char* filename, const char* content) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }

    fprintf(file, "%s", content);
    fclose(file);
}

// 添加学生预约详情到JSON文件
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

// 获取当前日期和时间
void get_current_time(int* year, int* month, int* day, int* hour) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    *year = tm.tm_year + 1900;
    *month = tm.tm_mon + 1;
    *day = tm.tm_mday;
    *hour = tm.tm_hour;
}

// 处理学生预约和场地占用状态的关联
void process_reservation(cJSON* facility_status, cJSON* student_data, Reservation* reservation) {
    int current_year, current_month, current_day, current_hour;
    get_current_time(&current_year, &current_month, &current_day, &current_hour);

    // 检查是否在预约日期的7天内
    if (reservation->year < current_year ||
        (reservation->year == current_year && reservation->month < current_month) ||
        (reservation->year == current_year && reservation->month == current_month && reservation->day <= current_day + 7)) {

        // 检查场地状态
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
                        // 场地空闲，可以预约
                        add_reservation(student_data, reservation);
                        printf("学生ID %d 成功预约了场地ID %d\n", reservation->student_id, reservation->facility_id);
                    }
                    else {
                        printf("场地ID %d 已被占用\n", reservation->facility_id);
                    }
                    return;
                }
            }
            printf("未找到场地ID %d\n", reservation->facility_id);
        }
        else {
            printf("未找到场地信息\n");
        }
    }
    else {
        printf("只能提前7天内预约场地\n");
    }
}
