#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include "file.h"


void add_reservation(Reservation reservation) {
    char* student_data = read_file("student_information.json");
    if (!student_data) return;

    char* site_data = read_file("site_info.json");
    if (!site_data) {
        free(student_data);
        return;
    }

    char* order_data = read_file("student_order.json");

    cJSON* student_json = cJSON_Parse(student_data);
    cJSON* site_json = cJSON_Parse(site_data);
    cJSON* order_json = order_data ? cJSON_Parse(order_data) : cJSON_CreateObject();

    free(student_data);
    free(site_data);
    free(order_data);

    // 创建预约记录
    cJSON* reservation_json = cJSON_CreateObject();
    cJSON_AddNumberToObject(reservation_json, "site_id", reservation.site_id);
    cJSON_AddNumberToObject(reservation_json, "facility_id", reservation.facility_id);
    cJSON_AddNumberToObject(reservation_json, "year", reservation.year);
    cJSON_AddNumberToObject(reservation_json, "month", reservation.month);
    cJSON_AddNumberToObject(reservation_json, "day", reservation.day);
    cJSON_AddNumberToObject(reservation_json, "start_hour", reservation.start_hour);
    cJSON_AddNumberToObject(reservation_json, "end_hour", reservation.end_hour);

    // 将预约记录添加到学生记录中
    cJSON* student_order = cJSON_GetObjectItem(order_json, reservation.ID);
    if (!student_order) {
        student_order = cJSON_CreateArray();
        cJSON_AddItemToObject(order_json, reservation.ID, student_order);
    }
    cJSON_AddItemToArray(student_order, reservation_json);

    // 更新 student_information.json 中的预约状态
    cJSON* student_info = cJSON_GetObjectItem(student_json, reservation.ID);
    if (student_info) {
        switch (reservation.site_id) {
        case 0:
            cJSON_ReplaceItemInObject(student_info, "badminton", cJSON_CreateNumber(reservation.facility_id));
            break;
        case 1:
            cJSON_ReplaceItemInObject(student_info, "tennis", cJSON_CreateNumber(reservation.facility_id));
            break;
        case 2:
            cJSON_ReplaceItemInObject(student_info, "basketball", cJSON_CreateNumber(reservation.facility_id));
            break;
        case 3:
            cJSON_ReplaceItemInObject(student_info, "pingpang", cJSON_CreateNumber(reservation.facility_id));
            break;
        default:
            break;
        }
    }

    // 写入更新后的 student_information.json 文件
    char* student_data_updated = cJSON_Print(student_json);
    write_file("student_information.json", student_data_updated);

    // 写入 student_order.json 文件
    char* order_data_updated = cJSON_Print(order_json);
    write_file("student_order.json", order_data_updated);

    // 释放 JSON 对象
    cJSON_Delete(student_json);
    cJSON_Delete(site_json);
    cJSON_Delete(order_json);
    free(student_data_updated);
    free(order_data_updated);
}

void print_available_facilities(cJSON* site_json, const char* facility_type) {
    cJSON* facilities = cJSON_GetObjectItem(site_json, facility_type);
    if (!facilities) {
        printf("No facilities found for %s.\n", facility_type);
        return;
    }

    printf("可用的 %s :\n", facility_type);
    cJSON* facility;
    cJSON_ArrayForEach(facility, facilities) {
        int facility_id = cJSON_GetObjectItem(facility, "场地编号")->valueint;
        int status = cJSON_GetObjectItem(facility, "状态")->valueint;
        if (status == 0) {
            printf("场地编号: %d\n", facility_id);
        }
    }
}

char student_ID[5];
void student_order() {
    STU student_login;
    // 读取场地信息
    char* site_data = read_file("site_info.json");
    if (!site_data) return 1;

    cJSON* site_json = cJSON_Parse(site_data);
    free(site_data);

    // 学生选择场地类型
    int facility_choice;
    printf("请选择预约场地类型:\n");
    printf("0. 羽毛球场\n");
    printf("1. 网球场\n");
    printf("2. 篮球场\n");
    printf("3. 乒乓球场\n");
    scanf("%d", &facility_choice);
    system("cls");

    const char* facility_type;
    switch (facility_choice) {
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
        printf("Invalid choice.\n");
        cJSON_Delete(site_json);
        return 1;
    }

    // 显示空闲场地编号
    print_available_facilities(site_json, facility_type);

    // 学生选择场地编号
    int facility_id;
    printf("请输入要预约的场地编号: ");
    scanf("%d", &facility_id);

    // 获取当前时间
    time_t now = time(NULL);
    struct tm* t = localtime(&now);

    // 学生输入预约时间段
    int start_hour, end_hour;
    printf("请输入开始时间: ");
    scanf("%d", &start_hour);
    printf("请输入开始时间: ");
    scanf("%d", &end_hour);

    // 创建预约记录
    Reservation reservation;
    strncpy(reservation.ID, student_ID, sizeof(reservation.ID));
    reservation.site_id = facility_choice;
    reservation.facility_id = facility_id;
    reservation.year = t->tm_year + 1900;
    reservation.month = t->tm_mon + 1;
    reservation.day = t->tm_mday;
    reservation.start_hour = start_hour;
    reservation.end_hour = end_hour;

    add_reservation(reservation);

    cJSON_Delete(site_json);
    return 0;
}

void copy_ID(char* ID)
{
    strncpy(student_ID, ID, sizeof(student_ID));
}