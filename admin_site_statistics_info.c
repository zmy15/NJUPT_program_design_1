#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<Windows.h>
#include"file.h"
#include"admin.h"

double fee_rates[4] = {5,8,10,15}; // ���ֳ��ص��շѱ�׼
void count_daily_usage(int year, int month, int day) {
    // ��ȡ student_order.json �ļ�
    char* order_data = read_file("student_order.json");
    if (!order_data) return;
    cJSON* order_json = cJSON_Parse(order_data);
    free(order_data);

    // ��ȡ site_info.json �ļ�
    char* site_data = read_file("site_info.json");
    if (!site_data) {
        cJSON_Delete(order_json);
        return;
    }
    cJSON* site_json = cJSON_Parse(site_data);
    free(site_data);

    // ��ʼ������ʹ������ͷ��ü�����
    int usage_count[4] = { 0 }; // 0: Badminton, 1: Tennis, 2: Basketball, 3: PingPang
    double total_fee = 0.0;

    // ����ԤԼ��¼
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

    // ���ͳ�ƽ�����ļ� count.txt
    FILE* file = fopen("count.txt", "a+");
    if (!file) {
        perror("Cannot open file");
        cJSON_Delete(order_json);
        cJSON_Delete(site_json);
        return;
    }
    fprintf(file, "ͳ�����ڣ�%d-%02d-%02d\n\n", year, month, day);
    fprintf(file, "����ʹ�����ͳ�ƣ�\n");
    fprintf(file, "��ë�򳡣� %d��\n", usage_count[0]);
    fprintf(file, "���򳡣� %d��\n", usage_count[1]);
    fprintf(file, "���򳡣� %d��\n", usage_count[2]);
    fprintf(file, "ƹ���򳡣� %d��\n\n", usage_count[3]);

    fprintf(file, "�������ͳ�ƣ�\n");
    fprintf(file, "�ܷ��ã� %.2f\n", total_fee);

    fclose(file);

    cJSON_Delete(order_json);
    cJSON_Delete(site_json);
    printf("ͳ�����ڣ�%d-%02d-%02d\n\n", year, month, day);
    printf("����ʹ�����ͳ�ƣ�\n");
    printf("��ë�򳡣� %d��\n", usage_count[0]);
    printf("���򳡣� %d��\n", usage_count[1]);
    printf("���򳡣� %d��\n", usage_count[2]);
    printf("ƹ���򳡣� %d��\n\n", usage_count[3]);

    printf("�������ͳ�ƣ�\n");
    printf("�ܷ��ã� %.2f\n", total_fee);
}

void site_statistics_info()
{
    int year, month, day;
    printf("����ͳ������ (YYYY MM DD): ");
    scanf("%d %d %d", &year, &month, &day);
    count_daily_usage(year, month, day);
    printf("1.������һ��\n2.�˳�ϵͳ\n");
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