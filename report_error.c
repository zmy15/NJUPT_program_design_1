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
            cJSON* facility = cJSON_GetObjectItem(time_key, "badminton"); // 获取指定场地类型的数组
            if (!facility) {
                printf("Error: Unable to retrieve facility information.\n");
                continue;
            }

            cJSON_SetNumberValue(cJSON_GetArrayItem(facility, facility_id), 2); // 设置场地状态为故障
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

    printf("选择场地 (0: 羽毛球场, 1: 网球场, 2: 篮球场, 3: 乒乓球场): ");
    scanf("%d", &site_id);

    printf("输入场地编号: ");
    scanf("%d", &facility_id);

    char* site_data = read_file("site_info.json");
    if (!site_data) return;

    cJSON* site_json = cJSON_Parse(site_data);
    free(site_data);

    // 更新 site_info.json 中的场地状态为 2（需要维修）
    mark_facilities_as_faulty(site_json, site_id, facility_id);

    // 将更新后的 site_info.json 写入文件
    char* site_data_updated = cJSON_Print(site_json);
    write_file("site_info.json", site_data_updated);
    free(site_data_updated);

    // 记录故障信息到 error.txt 中
    record_error(site_id, facility_id);

    // 释放 cJSON 对象
    cJSON_Delete(site_json);

    printf("已报告场地故障！\n");
    printf("1.返回上一级\n2.退出系统\n");
    scanf("%d", &n);
    if (n == 1) {
        system("cls");
        student_interface();
    }
    else {
        exit(0);
    }
}
