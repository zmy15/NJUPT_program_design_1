#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include"file.h"


void stu_order_info ()
{
    // ��ȡ����ռ��״̬��ѧ������
    char* facility_status_string = read_file_order("site_info.json");
    char* student_data_string = read_file("student_information.json");

    // ����JSON�ַ���
    cJSON* facility_status = cJSON_Parse(facility_status_string);
    cJSON* student_data = cJSON_Parse(student_data_string);

    // �ͷ��ڴ�
    free(facility_status_string);
    free(student_data_string);

    // ģ��һ��ѧ��ԤԼ����
    Reservation reservation = { 123, 1, 2024, 5, 20, 10, 11 };
    process_reservation(facility_status, student_data, &reservation);

    // ���º��ѧ������JSON�ַ���
    char* updated_student_data_string = cJSON_Print(student_data);
    // �����º��ѧ������JSON�ַ���д���ļ�
    write_file_order("order_information.json", updated_student_data_string);

    // �ͷ��ڴ�
    free(updated_student_data_string);
    cJSON_Delete(facility_status);
    cJSON_Delete(student_data);

    return 0;
}
