#define _CRT_SECURE_NO_WARNINGS 1
#include"student.h"
#include<stdio.h>
#include"file.h"
#include<Windows.h>

void report_error() {

    int site_id;
    int facility_id;
    int n;

    printf("选择场地 (0: 羽毛球场, 1: 网球场, 2: 篮球场, 3: 乒乓球场):  ");
    scanf("%d", &site_id);

    printf("输入场地编号: ");
    scanf("%d", &facility_id);

    char* site_data = read_file("site_info.json");
    if (!site_data) return 1;

    cJSON* site_json = cJSON_Parse(site_data);
    free(site_data);

    // 更新 site_info.json 中的场地状态为 2（需要维修）
    update_site_status(site_json, site_id, facility_id, 2);

    // 将更新后的 site_info.json 写入文件
    char* site_data_updated = cJSON_Print(site_json);
    write_file("site_info.json", site_data_updated);
    free(site_data_updated);

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
        return 0;
    }
    return 0;
}