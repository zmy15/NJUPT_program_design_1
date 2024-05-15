#define _CRT_SECURE_NO_WARNINGS 1
#include"student.h"
#include<stdio.h>
#include"file.h"
#include"student.h"
#include<Windows.h>

const char* get_site_name(int site_id) {
    switch (site_id) {
    case 0:
        return "羽毛球场";
    case 1:
        return "网球场";
    case 2:
        return "篮球场";
    case 3:
        return "乒乓球场";
    default:
        return "未知场地";
    }
}

void print_student_reservation(cJSON* student_json, const char* student_id) {
    cJSON* reservations = cJSON_GetObjectItem(student_json, student_id);
    if (!reservations || !cJSON_IsArray(reservations)) {
        printf("Error: No reservations found for student ID %s.\n", student_id);
        return;
    }

    printf("学生 %s 的预约情况:\n", student_id);
    int num_reservations = cJSON_GetArraySize(reservations);
    for (int i = 0; i < num_reservations; ++i) {
        cJSON* reservation = cJSON_GetArrayItem(reservations, i);
        if (!reservation) {
            printf("Error: Unable to retrieve reservation information.\n");
            continue;
        }

        Reservation res;
        strcpy(res.ID, student_id);
        res.site_id = cJSON_GetObjectItem(reservation, "site_id")->valueint;
        res.facility_id = cJSON_GetObjectItem(reservation, "facility_id")->valueint;
        res.year = cJSON_GetObjectItem(reservation, "year")->valueint;
        res.month = cJSON_GetObjectItem(reservation, "month")->valueint;
        res.day = cJSON_GetObjectItem(reservation, "day")->valueint;
        res.start_hour = cJSON_GetObjectItem(reservation, "start_hour")->valueint;
        res.end_hour = cJSON_GetObjectItem(reservation, "end_hour")->valueint;
        res.fee = cJSON_GetObjectItem(reservation, "fee")->valuedouble;

        printf("日期：%d-%02d-%02d  时间：%02d:00-%02d:00  场地类型：%s  场地编号：%d  费用：%.2f\n",
            res.year, res.month, res.day, res.start_hour, res.end_hour, get_site_name(res.site_id), res.facility_id, res.fee);
    }
}

extern STU student_login;
void student_site_info() {

    char* order_data = read_file("student_order.json");
    if (!order_data) {
        return 1;
    }
    cJSON* order_json = cJSON_Parse(order_data);
    free(order_data);
    print_student_reservation(order_json, student_login.ID);

    cJSON_Delete(order_json);
    printf("1.返回上一级\n2.退出系统\n");
    int n;
    scanf("%d", &n);
    if (n == 1) {
        system("cls");
        student_interface();
    }
    else {
        return 0;
    }
    return 0;
}