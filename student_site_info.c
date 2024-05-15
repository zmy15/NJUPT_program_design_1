#define _CRT_SECURE_NO_WARNINGS 1
#include"student.h"
#include<stdio.h>
#include"file.h"
#include"student.h"
#include<Windows.h>

void student_site_info() {

    int year, month, day;
    int n;
    char* site_data = read_file("site_info.json");
    if (!site_data) return 1;

    cJSON* site_json = cJSON_Parse(site_data);
    free(site_data);
    printf("输入日期 (YYYY MM DD): ");
    scanf("%d %d %d", &year, &month, &day);
    print_daily_schedule(site_json, year, month, day);
    printf("1.返回上一级\n2.退出系统");
    scanf("%d", &n);
    if (n == 1) {
        system("cls");
        student_interface();
    }
    else {
        return 0;
    }
}