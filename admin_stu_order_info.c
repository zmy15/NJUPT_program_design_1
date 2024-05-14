#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include"file.h"


void stu_order_info ()
{
    // 读取场地占用状态和学生数据
    char* facility_status_string = read_file_order("site_info.json");
    char* student_data_string = read_file("student_information.json");

    // 解析JSON字符串
    cJSON* facility_status = cJSON_Parse(facility_status_string);
    cJSON* student_data = cJSON_Parse(student_data_string);

    // 释放内存
    free(facility_status_string);
    free(student_data_string);

    // 模拟一个学生预约场地
    Reservation reservation = { 123, 1, 2024, 5, 20, 10, 11 };
    process_reservation(facility_status, student_data, &reservation);

    // 更新后的学生数据JSON字符串
    char* updated_student_data_string = cJSON_Print(student_data);
    // 将更新后的学生数据JSON字符串写入文件
    write_file_order("order_information.json", updated_student_data_string);

    // 释放内存
    free(updated_student_data_string);
    cJSON_Delete(facility_status);
    cJSON_Delete(student_data);

    return 0;
}
