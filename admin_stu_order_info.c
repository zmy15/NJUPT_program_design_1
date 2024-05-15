#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include"file.h"


void stu_order_info ()
{
    // ��ȡ student_information.json �ļ�
    char* student_data = read_file("student_information.json");
    if (!student_data) return;
    cJSON* student_json = cJSON_Parse(student_data);
    free(student_data);

    // ��ȡ student_order.json �ļ�
    char* order_data = read_file("student_order.json");
    if (!order_data) return;
    cJSON* order_json = cJSON_Parse(order_data);
    free(order_data);

    // ����ѧ����Ϣ
    cJSON* student_item;
    cJSON_ArrayForEach(student_item, student_json) {
        const char* student_id = student_item->string;
        cJSON* student_info = cJSON_GetObjectItem(student_json, student_id);
        const char* student_name = cJSON_GetObjectItem(student_info, "name")->valuestring;
        const char* student_password = cJSON_GetObjectItem(student_info, "password")->valuestring;

        // ���ѧ����Ϣ
        printf("ѧ��: %s\n����: %s\n����: %s\n", student_id, student_name, student_password);

        // ����ѧ����ԤԼ��Ϣ
        cJSON* student_order = cJSON_GetObjectItem(order_json, student_id);
        if (student_order) {
            int array_size = cJSON_GetArraySize(student_order);
            if (array_size > 0) {
                printf("ԤԼʱ�估����:\n");
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
                        facility_type = "��ë��";
                        break;
                    case 1:
                        facility_type = "����";
                        break;
                    case 2:
                        facility_type = "����";
                        break;
                    case 3:
                        facility_type = "ƹ����";
                        break;
                    default:
                        facility_type = "δ֪";
                        break;
                    }
                    printf("%d-%02d-%02d %d:00-%d:00, %s%d\n", year, month, day, start_hour, end_hour, facility_type, facility_id);
                }
            }
            else {
                printf("δԤԼ\n");
            }
        }
        else {
            printf("δԤԼ\n");
        }
        printf("\n");
    }
    // �ͷ� cJSON ����
    cJSON_Delete(student_json);
    cJSON_Delete(order_json);
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
}
