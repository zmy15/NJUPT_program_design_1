#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include "file.h"
#include"student.h"

#define SITE_INFO_FILE "site_info.json"
#define STUDENT_ORDER_FILE "student_order.json"
extern STU student_login;

// 读取场地信息
cJSON* read_site_info(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* data = (char*)malloc(length + 1);
    fread(data, 1, length, file);
    fclose(file);

    cJSON* json = cJSON_Parse(data);
    free(data);
    return json;
}

// 写入场地信息
void write_site_info(const char* filename, cJSON* json) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return;
    }
    char* data = cJSON_Print(json);
    fputs(data, file);
    fclose(file);
    free(data);
}

// 读取学生订单信息
char* _read_file(const char* filename) {
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

// 写入学生订单信息
void _write_file(const char* filename, const char* content) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }

    fprintf(file, "%s", content);
    fclose(file);
}

// 预约功能
void make_reservation(cJSON* site_info, cJSON* student_order, Reservation reservation) {
    // 根据预约信息更新场地信息
    char date_key[20];
    sprintf(date_key, "%d-%02d-%02d", reservation.year, reservation.month, reservation.day);
    cJSON* date_obj = cJSON_GetObjectItem(site_info, date_key);
    if (!date_obj) {
        printf("Error: No information available for the specified date.\n");
        return;
    }

    char time_key[10];
    sprintf(time_key, "%02d-%02d", reservation.start_hour, reservation.end_hour);
    cJSON* time_obj = cJSON_GetObjectItem(date_obj, time_key);
    if (!time_obj) {
        printf("Error: No information available for the specified time slot.\n");
        return;
    }

    cJSON* site_arr = NULL;
    char site_str[13];
    switch (reservation.site_id) {
    case 0:
        site_arr = cJSON_GetObjectItem(time_obj, "badminton");
        strcpy(site_str, "羽毛球场");
        break;
    case 1:
        site_arr = cJSON_GetObjectItem(time_obj, "tennis");
        strcpy(site_str, "网球场");
        break;
    case 2:
        site_arr = cJSON_GetObjectItem(time_obj, "basketball");
        strcpy(site_str, "篮球场");
        break;
    case 3:
        site_arr = cJSON_GetObjectItem(time_obj, "pingpang");
        strcpy(site_str, "乒乓球场");
        break;
    default:
        printf("Error: Invalid site ID.\n");
        return;
    }

    if (!site_arr) {
        printf("Error: No information available for the specified site.\n");
        return;
    }

    int facility_id = -1;
    cJSON* facility = NULL;
    int i = 0;
    for (i = 0; i < cJSON_GetArraySize(site_arr); i++) {
        facility = cJSON_GetArrayItem(site_arr, i);
        if (cJSON_GetNumberValue(facility) == 0)
        {
            facility_id = 1;
            printf("可用的%s编号：%d\n", site_str, i + 1);
        }
        else {
            continue;
        }
    }

    if (facility_id == -1) {
        printf("Error: No available facilities for reservation.\n");
        return;
    }

    printf("输入要预约的场地编号:");
    scanf("%d", &facility_id);
    facility = cJSON_GetArrayItem(site_arr, facility_id - 1);
    cJSON_SetNumberValue(facility, 1); // 设置场地为占用状态

    // 计算费用
    double price_per_hour = 0;
    switch (reservation.site_id) {
    case 0:
        price_per_hour = 5.0;
        break;
    case 1:
        price_per_hour = 8.0;
        break;
    case 2:
        price_per_hour = 10.0;
        break;
    case 3:
        price_per_hour = 15.0;
        break;
    default:
        break;
    }

    reservation.fee = price_per_hour * (reservation.end_hour - reservation.start_hour);
    printf("预约费用: %.2f. 是否预约? (输入1确认，0取消): ", reservation.fee);
    int confirm;
    scanf("%d", &confirm);
    if (confirm == 1)
    {
        cJSON* order_json = student_order ? cJSON_Parse(student_order) : cJSON_CreateObject();
        free(student_order);
        // 更新学生订单信息
        cJSON* reservation_json = cJSON_CreateObject();
        cJSON_AddNumberToObject(reservation_json, "site_id", reservation.site_id);
        cJSON_AddNumberToObject(reservation_json, "facility_id", facility_id);
        cJSON_AddNumberToObject(reservation_json, "year", reservation.year);
        cJSON_AddNumberToObject(reservation_json, "month", reservation.month);
        cJSON_AddNumberToObject(reservation_json, "day", reservation.day);
        cJSON_AddNumberToObject(reservation_json, "start_hour", reservation.start_hour);
        cJSON_AddNumberToObject(reservation_json, "end_hour", reservation.end_hour);
        cJSON_AddNumberToObject(reservation_json, "fee", reservation.fee);

        cJSON* order_data = cJSON_GetObjectItem(order_json, reservation.ID);
        if (!order_data) {
            order_data = cJSON_CreateArray();
            cJSON_AddItemToObject(order_json, reservation.ID, order_data);
        }
        cJSON_AddItemToArray(order_data, reservation_json);

        // 更新文件中的学生订单信息
        char* order_data_updated = cJSON_Print(order_json);
        _write_file("student_order.json", order_data_updated);
        cJSON_Delete(order_json);

        // 更新文件中的场地信息
        write_site_info(SITE_INFO_FILE, site_info);
        system("cls");
        printf("预约成功！.\n");
    }
    else {
        system("cls");
        printf("预约取消！\n");
    }
}

// 取消预约功能
void cancel_reservation(char* student_id, int site_id, int facility_id, int year, int month, int day, int start_hour, int end_hour) {
    char* site_data = _read_file("site_info.json");
    if (!site_data) {
        return;
    }

    char* order_data = _read_file("student_order.json");
    if (!order_data) {
        free(site_data);
        return;
    }
    cJSON* site_info = cJSON_Parse(site_data);
    cJSON* order_json = cJSON_Parse(order_data);
    free(site_data);
    free(order_data);
    // 获取学生的预约记录
    cJSON* student_order = cJSON_GetObjectItem(order_json, student_id);
    if (!student_order) {
        system("cls");
        printf("学号%s的预约信息没有找到：\n", student_id);
        return;
    }
    // 获取当前时间
    time_t t = time(NULL);
    struct tm* current_time = localtime(&t);
    struct tm reservation_time = { 0 };
    reservation_time.tm_year = year - 1900;
    reservation_time.tm_mon = month - 1;
    reservation_time.tm_mday = day;

    double seconds = difftime(mktime(&reservation_time), mktime(current_time));

    // 如果预约日期为当天或已过，不允许取消
    if (seconds < 0 || seconds < 24 * 60 * 60) {
        system("cls");
        printf("预约不能被取消.\n");
        return;
    }

    int found = 0;
    cJSON* reservation;
    cJSON_ArrayForEach(reservation, student_order) {
        int r_site_id = cJSON_GetObjectItem(reservation, "site_id")->valueint;
        int r_facility_id = cJSON_GetObjectItem(reservation, "facility_id")->valueint;
        int r_year = cJSON_GetObjectItem(reservation, "year")->valueint;
        int r_month = cJSON_GetObjectItem(reservation, "month")->valueint;
        int r_day = cJSON_GetObjectItem(reservation, "day")->valueint;
        int r_start_hour = cJSON_GetObjectItem(reservation, "start_hour")->valueint;
        int r_end_hour = cJSON_GetObjectItem(reservation, "end_hour")->valueint;

        if (r_site_id == site_id && r_facility_id == facility_id && r_year == year && r_month == month && r_day == day && r_start_hour == start_hour && r_end_hour == end_hour) {
            cJSON_DeleteItemFromArray(student_order, cJSON_GetArraySize(student_order) - 1);
            found = 1;
            break;
        }
    }
    if (!found) {
        system("cls");
        printf("没有匹配的预约.\n");
        cJSON_Delete(order_json);
        return;
    }
    char date_key[20];
    sprintf(date_key, "%d-%02d-%02d", year, month, day);
    cJSON* date_obj = cJSON_GetObjectItem(site_info, date_key);
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

    cJSON* site_arr = NULL;
    char site_str[13];
    switch (site_id) {
    case 0:
        site_arr = cJSON_GetObjectItem(time_obj, "badminton");
        strcpy(site_str, "羽毛球场");
        break;
    case 1:
        site_arr = cJSON_GetObjectItem(time_obj, "tennis");
        strcpy(site_str, "网球场");
        break;
    case 2:
        site_arr = cJSON_GetObjectItem(time_obj, "basketball");
        strcpy(site_str, "篮球场");
        break;
    case 3:
        site_arr = cJSON_GetObjectItem(time_obj, "pingpang");
        strcpy(site_str, "乒乓球场");
        break;
    default:
        printf("Error: Invalid site ID.\n");
        return;
    }

    if (!site_arr) {
        printf("Error: No information available for the specified site.\n");
        return;
    }

    cJSON* facility = NULL;

    facility = cJSON_GetArrayItem(site_arr, facility_id - 1);
    cJSON_SetNumberValue(facility, 0); // 设置场地为空闲状态

    // 写入更新后的 site_info.json 文件
    char* site_data_updated = cJSON_Print(site_info);
    write_file("site_info.json", site_data_updated);

    // 写入 student_order.json 文件
    char* order_data_updated = cJSON_Print(order_json);
    write_file("student_order.json", order_data_updated);

    // 释放 JSON 对象
    cJSON_Delete(site_info);
    cJSON_Delete(order_json);
    free(site_data_updated);
    free(order_data_updated);
    system("cls");
    printf("取消预约成功！\n");
}

void print_available_facilities(cJSON* site_json, int year, int month, int day, int site_id, int start_hour, int end_hour) {
    const char* site_type;
    char* site_str;
    switch (site_id) {
    case 0:
        site_type = "badminton";
        site_str = "羽毛球场";
        break;
    case 1:
        site_type = "tennis";
        site_str = "网球场";
        break;
    case 2:
        site_type = "basketball";
        site_str = "篮球场";
        break;
    case 3:
        site_type = "pingpang";
        site_str = "乒乓球场";
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

    printf("从 %d 时到 %d 时的空闲 %s:\n", start_hour, end_hour, site_str);
    int array_size = cJSON_GetArraySize(facility_obj);
    for (int i = 0; i < array_size; ++i) {
        cJSON* element = cJSON_GetArrayItem(facility_obj, i);
        if (cJSON_IsNumber(element) && cJSON_GetNumberValue(element) == 0) {
            printf("%d ", i + 1); // 输出可用的场地编号
        }
    }
    printf("\n");
}

void print_daily_schedule(cJSON* site_json, int year, int month, int day, int start_hour, int end_hour) {
    char date_str[11];
    sprintf(date_str, "%d-%02d-%02d", year, month, day);
    printf("Daily schedule for %s from %d:00 to %d:00:\n", date_str, start_hour, end_hour);
    for (int site_id = 0; site_id < 4; ++site_id) {
        print_available_facilities(site_json, year, month, day, site_id, start_hour, end_hour);
    }
}

// 交互模式
void interactive_mode(cJSON* site_info, char* student_order) {
    while (1)
    {
        int choice;
        int site_id;
        int facility_id;
        int start_hour, end_hour;
        int year, month, day;
        printf("\n=== 预约系统菜单 ===\n");
        printf("1. 场地预约\n");
        printf("2. 取消预约\n");
        printf("3. 查看可用场地\n");
        printf("4. 返回上一级\n");
        printf("5. 退出系统\n");
        printf("输入选项: ");
        scanf("%d", &choice);
        system("cls");
        switch (choice) {
        case 1: {
            // 输入预约信息
            Reservation new_reservation;
            strcpy(new_reservation.ID, student_login.ID);
            printf("输入预约日期 (YYYY-MM-DD): ");
            scanf("%d-%d-%d", &new_reservation.year, &new_reservation.month, &new_reservation.day);
            printf("输入预约时间段 (HH-HH): ");
            scanf("%d-%d", &new_reservation.start_hour, &new_reservation.end_hour);
            printf("选择场地 (0: 羽毛球场, 1: 网球场, 2: 篮球场, 3: 乒乓球场): ");
            scanf("%d", &new_reservation.site_id);

            // 判断日期格式是否合法
            if (new_reservation.year < 0 || new_reservation.month < 1 || new_reservation.month > 12 ||
                new_reservation.day < 1 || new_reservation.day > 31 || new_reservation.start_hour < 0 ||
                new_reservation.start_hour > 23 || new_reservation.end_hour < 0 || new_reservation.end_hour > 23 ||
                new_reservation.start_hour >= new_reservation.end_hour) {
                printf("Error: Invalid date or time slot.\n");
                break;
            }

            // 判断场地ID是否合法
            if (new_reservation.site_id < 0 || new_reservation.site_id > 3) {
                printf("Error: Invalid site ID.\n");
                break;
            }

            // 执行预约
            make_reservation(site_info, student_order, new_reservation);
            break;
        }
        case 2: {
            printf("选择场地 (0: 羽毛球场, 1: 网球场, 2: 篮球场, 3: 乒乓球场): ");
            scanf("%d", &site_id);
            printf("学号");
            scanf("%s", student_login.ID);
            cJSON* order_json = cJSON_Parse(student_order);
            cJSON* student_order = cJSON_GetObjectItem(order_json, student_login.ID);
            if (!student_order) {
                printf("没有预约信息 %s\n", student_login.ID);
                cJSON_Delete(order_json);
                return 1;
            }
            printf("学号%s的预约信息:\n", student_login.ID);
            cJSON* reservation;
            cJSON_ArrayForEach(reservation, student_order) {
                int r_site_id = cJSON_GetObjectItem(reservation, "site_id")->valueint;
                int r_facility_id = cJSON_GetObjectItem(reservation, "facility_id")->valueint;
                int r_year = cJSON_GetObjectItem(reservation, "year")->valueint;
                int r_month = cJSON_GetObjectItem(reservation, "month")->valueint;
                int r_day = cJSON_GetObjectItem(reservation, "day")->valueint;
                int r_start_hour = cJSON_GetObjectItem(reservation, "start_hour")->valueint;
                int r_end_hour = cJSON_GetObjectItem(reservation, "end_hour")->valueint;
                if (r_site_id == site_id) {
                    printf("%d-%d-%d %d时-%d时预约的场地: %d\n", r_year, r_month, r_day, r_start_hour, r_end_hour, r_facility_id);
                }
            }

            printf("输入预约日期 (YYYY-MM-DD): ");
            scanf("%d-%d-%d", &year, &month, &day);
            printf("输入预约时间 (HH-HH): ");
            scanf("%d-%d", &start_hour, &end_hour);
            printf("输入场地编号: ");
            scanf("%d", &facility_id);
            cancel_reservation(student_login.ID, site_id, facility_id, year, month, day, start_hour, end_hour);
            cJSON_Delete(order_json);
            break;
        }
        case 3:
            printf("输入日期 (YYYY-MM-DD): ");
            scanf("%d-%d-%d", &year, &month, &day);
            printf("输入开始时间 (9-20): ");
            scanf("%d", &start_hour);
            while (start_hour < 9 || start_hour > 20) {
                printf("Invalid start hour. Please enter again (9-20): ");
                scanf("%d", &start_hour);
            }

            printf("输入时间 (10-21): ");
            scanf("%d", &end_hour);
            while (end_hour < 10 || end_hour > 21) {
                printf("Invalid end hour. Please enter again (10-21): ");
                scanf("%d", &end_hour);
            }

            print_daily_schedule(site_info, year, month, day, start_hour, end_hour);
            break;
        case 4:
            break;
        case 5:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

}

void student_order() {
    // 读取场地信息
    cJSON* site_info = read_site_info(SITE_INFO_FILE);
    if (!site_info) {
        return 1;
    }

    // 读取学生订单信息
    char* order_data = _read_file("student_order.json");
    if (!order_data) {
        return 1;
    }

    // 进入交互模式
    interactive_mode(site_info, order_data);

    cJSON_Delete(site_info);
    return 0;
}
