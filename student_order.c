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

    // ����ԤԼ��¼
    cJSON* reservation_json = cJSON_CreateObject();
    cJSON_AddNumberToObject(reservation_json, "site_id", reservation.site_id);
    cJSON_AddNumberToObject(reservation_json, "facility_id", reservation.facility_id);
    cJSON_AddNumberToObject(reservation_json, "year", reservation.year);
    cJSON_AddNumberToObject(reservation_json, "month", reservation.month);
    cJSON_AddNumberToObject(reservation_json, "day", reservation.day);
    cJSON_AddNumberToObject(reservation_json, "start_hour", reservation.start_hour);
    cJSON_AddNumberToObject(reservation_json, "end_hour", reservation.end_hour);

    // ��ԤԼ��¼��ӵ�ѧ����¼��
    cJSON* student_order = cJSON_GetObjectItem(order_json, reservation.ID);
    if (!student_order) {
        student_order = cJSON_CreateArray();
        cJSON_AddItemToObject(order_json, reservation.ID, student_order);
    }
    cJSON_AddItemToArray(student_order, reservation_json);

    // ���� student_information.json �е�ԤԼ״̬
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

    // д����º�� student_information.json �ļ�
    char* student_data_updated = cJSON_Print(student_json);
    write_file("student_information.json", student_data_updated);

    // д�� student_order.json �ļ�
    char* order_data_updated = cJSON_Print(order_json);
    write_file("student_order.json", order_data_updated);

    // �ͷ� JSON ����
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

    printf("���õ� %s :\n", facility_type);
    cJSON* facility;
    cJSON_ArrayForEach(facility, facilities) {
        int facility_id = cJSON_GetObjectItem(facility, "���ر��")->valueint;
        int status = cJSON_GetObjectItem(facility, "״̬")->valueint;
        if (status == 0) {
            printf("���ر��: %d\n", facility_id);
        }
    }
}

char student_ID[5];
void student_order() {
    STU student_login;
    // ��ȡ������Ϣ
    char* site_data = read_file("site_info.json");
    if (!site_data) return 1;

    cJSON* site_json = cJSON_Parse(site_data);
    free(site_data);

    // ѧ��ѡ�񳡵�����
    int facility_choice;
    printf("��ѡ��ԤԼ��������:\n");
    printf("0. ��ë��\n");
    printf("1. ����\n");
    printf("2. ����\n");
    printf("3. ƹ����\n");
    scanf("%d", &facility_choice);
    system("cls");

    const char* facility_type;
    switch (facility_choice) {
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
        printf("Invalid choice.\n");
        cJSON_Delete(site_json);
        return 1;
    }

    // ��ʾ���г��ر��
    print_available_facilities(site_json, facility_type);

    // ѧ��ѡ�񳡵ر��
    int facility_id;
    printf("������ҪԤԼ�ĳ��ر��: ");
    scanf("%d", &facility_id);

    // ��ȡ��ǰʱ��
    time_t now = time(NULL);
    struct tm* t = localtime(&now);

    // ѧ������ԤԼʱ���
    int start_hour, end_hour;
    printf("�����뿪ʼʱ��: ");
    scanf("%d", &start_hour);
    printf("�����뿪ʼʱ��: ");
    scanf("%d", &end_hour);

    // ����ԤԼ��¼
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