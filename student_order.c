#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include "file.h"
#include"student.h"

double fee_rates[] = { 50.0, 40.0, 30.0, 20.0 }; // ���ֳ��ص��շѱ�׼
void update_site_status(cJSON* site_json, int site_id, int facility_id, int status) {
    const char* site_type;
    switch (site_id) {
    case 0:
        site_type = "badminton";
        break;
    case 1:
        site_type = "tennis";
        break;
    case 2:
        site_type = "basketball";
        break;
    case 3:
        site_type = "pingpang";
        break;
    default:
        return;
    }

    cJSON* facilities = cJSON_GetObjectItem(site_json, site_type);
    if (!facilities) return;

    cJSON* facility;
    cJSON_ArrayForEach(facility, facilities) {
        int current_facility_id = cJSON_GetObjectItem(facility, "facility_id")->valueint;
        if (current_facility_id == facility_id) {
            cJSON_ReplaceItemInObject(facility, "status", cJSON_CreateNumber(status)); // ����״̬
            break;
        }
    }
}

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
    cJSON_AddNumberToObject(reservation_json, "fee", reservation.fee);

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

    // ���� site_info.json �еĳ���״̬
    update_site_status(site_json, reservation.site_id, reservation.facility_id, 1);

    // д����º�� student_information.json �ļ�
    char* student_data_updated = cJSON_Print(student_json);
    write_file("student_information.json", student_data_updated);

    // д����º�� site_info.json �ļ�
    char* site_data_updated = cJSON_Print(site_json);
    write_file("site_info.json", site_data_updated);

    // д�� student_order.json �ļ�
    char* order_data_updated = cJSON_Print(order_json);
    write_file("student_order.json", order_data_updated);

    // �ͷ� JSON ����
    cJSON_Delete(student_json);
    cJSON_Delete(site_json);
    cJSON_Delete(order_json);
    free(student_data_updated);
    free(site_data_updated);
    free(order_data_updated);
}

void cancel_reservation(const char* student_id, int site_id, int facility_id, int year, int month, int day) {
    char* student_data = read_file("student_information.json");
    if (!student_data) return;

    char* site_data = read_file("site_info.json");
    if (!site_data) {
        free(student_data);
        return;
    }

    char* order_data = read_file("student_order.json");
    if (!order_data) {
        free(student_data);
        free(site_data);
        return;
    }

    cJSON* student_json = cJSON_Parse(student_data);
    cJSON* site_json = cJSON_Parse(site_data);
    cJSON* order_json = cJSON_Parse(order_data);

    free(student_data);
    free(site_data);
    free(order_data);

    // ��ȡѧ����ԤԼ��¼
    cJSON* student_order = cJSON_GetObjectItem(order_json, student_id);
    if (!student_order) {
        system("cls");
        printf("ѧ��%s��ԤԼ��Ϣû���ҵ���\n", student_id);
        return;
    }

    // ��ȡ��ǰʱ��
    time_t t = time(NULL);
    struct tm* current_time = localtime(&t);
    struct tm reservation_time = { 0 };
    reservation_time.tm_year = year - 1900;
    reservation_time.tm_mon = month - 1;
    reservation_time.tm_mday = day;

    double seconds = difftime(mktime(&reservation_time), mktime(current_time));

    // ���ԤԼ����Ϊ������ѹ���������ȡ��
    if (seconds < 0 || seconds < 24 * 60 * 60) {
        system("cls");
        printf("ԤԼ���ܱ�ȡ��.\n");
        return;
    }

    // ���Ҳ�ɾ��ԤԼ��¼
    int found = 0;
    cJSON* reservation;
    cJSON_ArrayForEach(reservation, student_order) {
        int r_site_id = cJSON_GetObjectItem(reservation, "site_id")->valueint;
        int r_facility_id = cJSON_GetObjectItem(reservation, "facility_id")->valueint;
        int r_year = cJSON_GetObjectItem(reservation, "year")->valueint;
        int r_month = cJSON_GetObjectItem(reservation, "month")->valueint;
        int r_day = cJSON_GetObjectItem(reservation, "day")->valueint;

        if (r_site_id == site_id && r_facility_id == facility_id && r_year == year && r_month == month && r_day == day) {
            cJSON_DeleteItemFromArray(student_order, cJSON_GetArraySize(student_order) - 1);
            found = 1;
            break;
        }
    }

    if (!found) {
        system("cls");
        printf("û��ƥ���ԤԼ.\n");
        cJSON_Delete(student_json);
        cJSON_Delete(site_json);
        cJSON_Delete(order_json);
        return;
    }

    // ���� student_information.json �е�ԤԼ״̬
    cJSON* student_info = cJSON_GetObjectItem(student_json, student_id);
    if (student_info) {
        switch (site_id) {
        case 0:
            cJSON_ReplaceItemInObject(student_info, "badminton", cJSON_CreateNumber(0));
            break;
        case 1:
            cJSON_ReplaceItemInObject(student_info, "tennis", cJSON_CreateNumber(0));
            break;
        case 2:
            cJSON_ReplaceItemInObject(student_info, "basketball", cJSON_CreateNumber(0));
            break;
        case 3:
            cJSON_ReplaceItemInObject(student_info, "pingpang", cJSON_CreateNumber(0));
            break;
        default:
            break;
        }
    }

    // ���� site_info.json �еĳ���״̬
    update_site_status(site_json, site_id, facility_id, 0);

    // д����º�� student_information.json �ļ�
    char* student_data_updated = cJSON_Print(student_json);
    write_file("student_information.json", student_data_updated);

    // д����º�� site_info.json �ļ�
    char* site_data_updated = cJSON_Print(site_json);
    write_file("site_info.json", site_data_updated);

    // д�� student_order.json �ļ�
    char* order_data_updated = cJSON_Print(order_json);
    write_file("student_order.json", order_data_updated);

    // �ͷ� JSON ����
    cJSON_Delete(student_json);
    cJSON_Delete(site_json);
    cJSON_Delete(order_json);
    free(student_data_updated);
    free(site_data_updated);
    free(order_data_updated);
    system("cls");
    printf("ȡ��ԤԼ�ɹ���\n");
}

void print_available_facilities(cJSON* site_json, int site_id) {
    const char* site_type;
    switch (site_id) {
    case 0:
        site_type = "badminton";
        break;
    case 1:
        site_type = "tennis";
        break;
    case 2:
        site_type = "basketball";
        break;
    case 3:
        site_type = "pingpang";
        break;
    default:
        return;
    }

    cJSON* facilities = cJSON_GetObjectItem(site_json, site_type);
    if (!facilities) return;

    printf("���õ�%s:\n", site_type);
    cJSON* facility;
    cJSON_ArrayForEach(facility, facilities) {
        int facility_id = cJSON_GetObjectItem(facility, "facility_id")->valueint;
        int status = cJSON_GetObjectItem(facility, "status")->valueint;
        if (status == 0) {
            printf("���ر��: %d\n", facility_id);
        }
    }
}

void print_daily_schedule(cJSON* site_json, int year, int month, int day) {
    char date_str[11];
    sprintf(date_str, "%d-%02d-%02d", year, month, day);
    printf("%s�Ŀ��ó���:\n", date_str);
    for (int site_id = 0; site_id < 4; ++site_id) {
        print_available_facilities(site_json, site_id);
    }
}

void print_facility_ID(cJSON* site_json, int site_id, int year, int month, int day) {
    char date_str[11];
    sprintf(date_str, "%d-%02d-%02d", year, month, day);
    printf("%s�Ŀ��ó��أ�\n", date_str);
    print_available_facilities(site_json, site_id);
}

extern STU student_login;
void student_order() {
    int choice;
    int site_id;
    int facility_id;
    int start_hour, end_hour;
    int year, month, day;

    time_t current_time = time(NULL);
    struct tm* current_tm = localtime(&current_time);
    int current_year = current_tm->tm_year + 1900;
    int current_month = current_tm->tm_mon + 1;
    int current_day = current_tm->tm_mday;
    int current_hour = current_tm->tm_hour;

    // ��ȡԤԼ��¼�ļ�
    char* order_data = read_file("student_order.json");
    cJSON* order_json = cJSON_Parse(order_data);
    free(order_data);

    if (order_json) {
        cJSON* student_id_item;
        cJSON_ArrayForEach(student_id_item, order_json) {
            const char* student_id = student_id_item->string;
            cJSON* student_order = cJSON_GetObjectItem(order_json, student_id);
            if (student_order) {
                int array_size = cJSON_GetArraySize(student_order);
                for (int i = 0; i < array_size; ++i) {
                    cJSON* reservation_json = cJSON_GetArrayItem(student_order, i);
                    int reservation_year = cJSON_GetObjectItem(reservation_json, "year")->valueint;
                    int reservation_month = cJSON_GetObjectItem(reservation_json, "month")->valueint;
                    int reservation_day = cJSON_GetObjectItem(reservation_json, "day")->valueint;
                    int reservation_end_hour = cJSON_GetObjectItem(reservation_json, "end_hour")->valueint;

                    // ���ԤԼ�����ڵ�ǰ����֮ǰ�����ǵ�ǰ���ڣ�������ʱ���ѹ����������ԤԼ
                    if ((reservation_year < current_year) ||
                        (reservation_year == current_year && reservation_month < current_month) ||
                        (reservation_year == current_year && reservation_month == current_month && reservation_day <= current_day && reservation_end_hour <= current_hour)) {
                        int site_id = cJSON_GetObjectItem(reservation_json, "site_id")->valueint;
                        int facility_id = cJSON_GetObjectItem(reservation_json, "facility_id")->valueint;
                        cJSON_DeleteItemFromArray(student_order, i); // ��ԤԼ��¼���Ƴ���ԤԼ

                        // ��ȡ student_information.json �ļ�
                        char* student_data = read_file("student_information.json");
                        if (!student_data) return;
                        cJSON* student_json = cJSON_Parse(student_data);

                        // ���� student_information.json �е�ԤԼ��Ϣ
                        cJSON* student_info = cJSON_GetObjectItem(student_json, student_login.ID);
                        if (student_info) {
                            switch (site_id) {
                            case 0:
                                cJSON_ReplaceItemInObject(student_info, "badminton", cJSON_CreateNumber(0));
                                break;
                            case 1:
                                cJSON_ReplaceItemInObject(student_info, "tennis", cJSON_CreateNumber(0));
                                break;
                            case 2:
                                cJSON_ReplaceItemInObject(student_info, "basketball", cJSON_CreateNumber(0));
                                break;
                            case 3:
                                cJSON_ReplaceItemInObject(student_info, "pingpang", cJSON_CreateNumber(0));
                                break;
                            default:
                                break;
                            }
                        }

                        // �����º�� student_information.json д���ļ�
                        char* student_data_updated = cJSON_Print(student_json);
                        write_file("student_information.json", student_data_updated);
                        free(student_data_updated);

                        // �ͷ� cJSON ����
                        cJSON_Delete(student_json);
                        free(student_data);

                        // ��ȡ site_info.json �ļ�
                        char* site_data = read_file("site_info.json");
                        if (!site_data) return;
                        cJSON* site_json = cJSON_Parse(site_data);

                        // ���� site_info.json �е�ԤԼ��Ϣ
                        update_site_status(site_json, site_id, facility_id, 0); // ����Ӧ���ص�״̬����ΪδԤԼ

                        // �����º�� site_info.json д���ļ�
                        char* site_data_updated = cJSON_Print(site_json);
                        write_file("site_info.json", site_data_updated);
                        free(site_data_updated);

                        // �ͷ� cJSON ����
                        cJSON_Delete(site_json);
                        free(site_data);
                    }
                }
            }
        }
    }
    while (1) {
        printf("\n1. ԤԼ����\n2. ȡ��ԤԼ\n3. �鿴���ó���\n4. ������һ��\n5. �˳�ϵͳ\n");
        printf("���������: ");
        scanf("%d", &choice);

        if (choice == 4) break;
        if (choice == 5) return 0;
        char* site_data = read_file("site_info.json");
        if (!site_data) return 1;

        cJSON* site_json = cJSON_Parse(site_data);
        free(site_data);

        switch (choice) {
        case 1:
            printf("ѡ�񳡵� (0: ��ë��, 1: ����, 2: ����, 3: ƹ����): ");
            scanf("%d", &site_id);

            printf("����ԤԼ���� (YYYY MM DD): ");
            scanf("%d %d %d", &year, &month, &day);

            print_facility_ID(site_json, site_id, year, month, day);

            printf("����ԤԼ���ر��: ");
            scanf("%d", &facility_id);
            do {
                printf("���뿪ʼʱ�� (9-20): ");
                scanf("%d", &start_hour);
            } while (start_hour < 9 || start_hour > 20);

            do {
                printf("�������ʱ�� (10-21): ");
                scanf("%d", &end_hour);
            } while (end_hour < 10 || end_hour > 21);

            double fee = fee_rates[site_id] * (end_hour - start_hour);

            printf("ԤԼ����: %.2f. �Ƿ�ԤԼ? (����1ȷ�ϣ�0ȡ��): ", fee);
            int confirm;
            scanf("%d", &confirm);

            if (confirm == 1) {
                Reservation reservation = {
                    .site_id = site_id,
                    .facility_id = facility_id,
                    .year = year,
                    .month = month,
                    .day = day,
                    .start_hour = start_hour,
                    .end_hour = end_hour,
                    .fee = fee
                };
                strcpy(reservation.ID, student_login.ID);
                add_reservation(reservation);
                system("cls");
                printf("ԤԼ�ɹ���\n");
            }
            else {
                system("cls");
                printf("ԤԼȡ����\n");
            }
            break;

        case 2:
            printf("ѡ�񳡵� (0: ��ë��, 1: ����, 2: ����, 3: ƹ����): ");
            scanf("%d", &site_id);

            // ��ʾ��ѧ����ԤԼ�Ķ�Ӧ���ͳ��صĳ��ر��
            char* order_data = read_file("student_order.json");
            if (!order_data) {
                cJSON_Delete(site_json);
                return 1;
            }
            cJSON* order_json = cJSON_Parse(order_data);
            free(order_data);

            cJSON* student_order = cJSON_GetObjectItem(order_json, student_login.ID);
            if (!student_order) {
                printf("û��ԤԼ��Ϣ %s\n", student_login.ID);
                cJSON_Delete(order_json);
                cJSON_Delete(site_json);
                return 1;
            }

            printf("ѧ��%s��ԤԼ��Ϣ:\n", student_login.ID);
            cJSON* reservation;
            cJSON_ArrayForEach(reservation, student_order) {
                int r_site_id = cJSON_GetObjectItem(reservation, "site_id")->valueint;
                int r_facility_id = cJSON_GetObjectItem(reservation, "facility_id")->valueint;
                int r_year = cJSON_GetObjectItem(reservation, "year")->valueint;
                int r_month = cJSON_GetObjectItem(reservation, "month")->valueint;
                int r_day = cJSON_GetObjectItem(reservation, "day")->valueint;
                if (r_site_id == site_id) {
                    printf("%d-%d-%dԤԼ�ĳ��ر��: %d\n", r_year, r_month, r_day,r_facility_id );
                }
            }

            printf("����ԤԼʱ�� (YYYY MM DD): ");
            scanf("%d %d %d", &year, &month, &day);
            printf("���볡�ر��: ");
            scanf("%d", &facility_id);

            cancel_reservation(student_login.ID, site_id, facility_id, year, month, day);
            cJSON_Delete(order_json);
            break;

        case 3:
            printf("�������� (YYYY MM DD): ");
            scanf("%d %d %d", &year, &month, &day);
            print_daily_schedule(site_json, year, month, day);
            break;

        default:
            printf("Invalid choice.\n");
            break;
        }

        cJSON_Delete(site_json);
    }
    system("cls");
    student_interface();
    return 0;
}