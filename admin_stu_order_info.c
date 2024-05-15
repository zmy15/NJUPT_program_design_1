#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include"file.h"


void stu_order_info ()
{
    // 读取 student_information.json 文件
    char* student_data = read_file("student_information.json");
    if (!student_data) return;
    cJSON* student_json = cJSON_Parse(student_data);
    free(student_data);

    // 读取 student_order.json 文件
    char* order_data = read_file("student_order.json");
    if (!order_data) return;
    cJSON* order_json = cJSON_Parse(order_data);
    free(order_data);

    // 遍历学生信息
    cJSON* student_item;
    cJSON_ArrayForEach(student_item, student_json) {
        const char* student_id = student_item->string;
        cJSON* student_info = cJSON_GetObjectItem(student_json, student_id);
        const char* student_name = cJSON_GetObjectItem(student_info, "name")->valuestring;
        const char* student_password = cJSON_GetObjectItem(student_info, "password")->valuestring;

        // 输出学生信息
        printf("学号: %s\n姓名: %s\n密码: %s\n", student_id, student_name, student_password);

        // 查找学生的预约信息
        cJSON* student_order = cJSON_GetObjectItem(order_json, student_id);
        if (student_order) {
            int array_size = cJSON_GetArraySize(student_order);
            if (array_size > 0) {
                printf("预约时间及场地:\n");
                for (int i = 0; i < array_size; ++i) {
                    cJSON* reservation_json = cJSON_GetArrayItem(student_order, i);
                    int year = cJSON_GetObjectItem(reservation_json, "year")->valueint;
                    int month = cJSON_GetObjectItem(reservation_json, "month")->valueint;
                    int day = cJSON_GetObjectItem(reservation_json, "day")->valueint;
                    int start_hour = cJSON_GetObjectItem(reservation_json, "start_hour")->valueint;
                    int end_hour = cJSON_GetObjectItem(reservation_json, "end_hour")->valueint;
                    int facility_id = cJSON_GetObjectItem(reservation_json, "facility_id")->valueint;
                    const char* facility_type;
                    switch (cJSON_GetObjectItem(reservation_json, "site_id")->valueint) {
                    case 0:
                        facility_type = "羽毛球场";
                        break;
                    case 1:
                        facility_type = "网球场";
                        break;
                    case 2:
                        facility_type = "篮球场";
                        break;
                    case 3:
                        facility_type = "乒乓球场";
                        break;
                    default:
                        facility_type = "未知";
                        break;
                    }
                    printf("%d-%02d-%02d %d:00-%d:00, %s%d\n", year, month, day, start_hour, end_hour, facility_type, facility_id);
                }
            }
            else {
                printf("未预约\n");
            }
        }
        else {
            printf("未预约\n");
        }
        printf("\n");
    }
    // 释放 cJSON 对象
    cJSON_Delete(student_json);
    cJSON_Delete(order_json);
    printf("1.返回上一级\n2.退出系统\n");
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
