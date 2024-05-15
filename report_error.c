#define _CRT_SECURE_NO_WARNINGS 1
#include"student.h"
#include<stdio.h>
#include"file.h"
#include<Windows.h>

void report_error() {

    int site_id;
    int facility_id;
    int n;

    printf("ѡ�񳡵� (0: ��ë��, 1: ����, 2: ����, 3: ƹ����):  ");
    scanf("%d", &site_id);

    printf("���볡�ر��: ");
    scanf("%d", &facility_id);

    char* site_data = read_file("site_info.json");
    if (!site_data) return 1;

    cJSON* site_json = cJSON_Parse(site_data);
    free(site_data);

    // ���� site_info.json �еĳ���״̬Ϊ 2����Ҫά�ޣ�
    update_site_status(site_json, site_id, facility_id, 2);

    // �����º�� site_info.json д���ļ�
    char* site_data_updated = cJSON_Print(site_json);
    write_file("site_info.json", site_data_updated);
    free(site_data_updated);

    // �ͷ� cJSON ����
    cJSON_Delete(site_json);

    printf("�ѱ��泡�ع��ϣ�\n");
    printf("1.������һ��\n2.�˳�ϵͳ\n");
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