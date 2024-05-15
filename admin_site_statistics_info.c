#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<Windows.h>
#include"file.h"
#include"admin.h"

double fee_rates[4] = {5,8,10,15}; // 各种场地的收费标准
void count_daily_usage(int year, int month, int day) {
    // 读取 student_order.json 文件
    char* order_data = read_file("student_order.json");
    if (!order_data) return;
    cJSON* order_json = cJSON_Parse(order_data);
    free(order_data);

    // 读取 site_info.json 文件
    char* site_data = read_file("site_info.json");
    if (!site_data) {
        cJSON_Delete(order_json);
        return;
    }
    cJSON* site_json = cJSON_Parse(site_data);
    free(site_data);

    // 初始化场地使用情况和费用计数器
    int usage_count[4] = { 0 }; // 0: Badminton, 1: Tennis, 2: Basketball, 3: PingPang
    double total_fee = 0.0;

    // 遍历预约记录
    cJSON* student_item;
    cJSON_ArrayForEach(student_item, order_json) {
        const char* student_id = student_item->string;
        cJSON* student_order = cJSON_GetObjectItem(order_json, student_id);
        if (student_order) {
            int array_size = cJSON_GetArraySize(student_order);
            for (int i = 0; i < array_size; ++i) {
                cJSON* reservation_json = cJSON_GetArrayItem(student_order, i);
                int reservation_year = cJSON_GetObjectItem(reservation_json, "year")->valueint;
                int reservation_month = cJSON_GetObjectItem(reservation_json, "month")->valueint;
                int reservation_day = cJSON_GetObjectItem(reservation_json, "day")->valueint;
                if (reservation_year == year && reservation_month == month && reservation_day == day) {
                    int site_id = cJSON_GetObjectItem(reservation_json, "site_id")->valueint;
                    int start_hour = cJSON_GetObjectItem(reservation_json, "start_hour")->valueint;
                    int end_hour = cJSON_GetObjectItem(reservation_json, "end_hour")->valueint;
                    double fee = fee_rates[site_id] * (end_hour - start_hour);
                    total_fee += fee;
                    usage_count[site_id]++;
                }
            }
        }
    }

    // 输出统计结果到文件 count.txt
    FILE* file = fopen("count.txt", "a+");
    if (!file) {
        perror("Cannot open file");
        cJSON_Delete(order_json);
        cJSON_Delete(site_json);
        return;
    }
    fprintf(file, "统计日期：%d-%02d-%02d\n\n", year, month, day);
    fprintf(file, "场地使用情况统计：\n");
    fprintf(file, "羽毛球场： %d次\n", usage_count[0]);
    fprintf(file, "网球场： %d次\n", usage_count[1]);
    fprintf(file, "篮球场： %d次\n", usage_count[2]);
    fprintf(file, "乒乓球场： %d次\n\n", usage_count[3]);

    fprintf(file, "费用情况统计：\n");
    fprintf(file, "总费用： %.2f\n", total_fee);

    fclose(file);

    cJSON_Delete(order_json);
    cJSON_Delete(site_json);
    printf("统计日期：%d-%02d-%02d\n\n", year, month, day);
    printf("场地使用情况统计：\n");
    printf("羽毛球场： %d次\n", usage_count[0]);
    printf("网球场： %d次\n", usage_count[1]);
    printf("篮球场： %d次\n", usage_count[2]);
    printf("乒乓球场： %d次\n\n", usage_count[3]);

    printf("费用情况统计：\n");
    printf("总费用： %.2f\n", total_fee);
}

void site_statistics_info()
{
    int year, month, day;
    printf("输入统计日期 (YYYY MM DD): ");
    scanf("%d %d %d", &year, &month, &day);
    count_daily_usage(year, month, day);
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
	return 0;
}