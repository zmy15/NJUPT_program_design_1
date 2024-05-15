#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<Windows.h>
#include"file.h"
#include"admin.h"

// 状态转换为文字
const char* status_to_string(int status) {
    switch (status) {
    case 0: return "空闲";
    case 1: return "占用";
    case 2: return "故障";
    default: return "未知";
    }
}

// 显示场地信息
void display_facilities(cJSON* root, const char* facility_name) {
    cJSON* facility_array = cJSON_GetObjectItem(root, facility_name);
    if (facility_array) {
        printf("%s:\n", facility_name);
        int count = cJSON_GetArraySize(facility_array);
        for (int i = 0; i < count; i++) {
            cJSON* court = cJSON_GetArrayItem(facility_array, i);
            int id = cJSON_GetObjectItem(court, "facility_id")->valueint;
            int status = cJSON_GetObjectItem(court, "status")->valueint;
            printf("  场地编号: %d, 状态: %s\n", id, status_to_string(status));
        }
    }
    else {
        printf("未找到场地类型 %s\n", facility_name);
    }
}

// 更改场地状态
void change_status(cJSON* root, const char* facility_name, int court_id, int new_status) {
    cJSON* facility_array = cJSON_GetObjectItem(root, facility_name);
    if (facility_array) {
        int count = cJSON_GetArraySize(facility_array);
        for (int i = 0; i < count; i++) {
            cJSON* court = cJSON_GetArrayItem(facility_array, i);
            int id = cJSON_GetObjectItem(court, "facility_id")->valueint;
            if (id == court_id) {
                cJSON* status_item = cJSON_GetObjectItem(court, "status");
                status_item->valueint = new_status;
                printf("%s %d 的状态已更改为 %s\n", facility_name, court_id, status_to_string(new_status));
                return;
            }
        }
        printf("未找到 %s 编号为 %d 的场地\n", facility_name, court_id);
    }
    else {
        printf("未找到场地类型 %s\n", facility_name);
    }
}

void site_info()
{
    char* json_string = read_file("site_info.json");
    if (json_string == NULL) {
        return 1;
    }

    // 解析JSON字符串
    cJSON* root = cJSON_Parse(json_string);
    if (root == NULL) {
        printf("JSON解析失败\n");
        free(json_string);
        return 1;
    }

    // 显示菜单和用户交互
    int choice;
    int court_id, new_status;
    const char* facility_names[] = { "badminton", "tennis", "basketball", "pingpang" };
    //const char* facility_names[] = { "羽毛球场", "网球场", "篮球场", "乒乓球场" };
    int facility_count = sizeof(facility_names) / sizeof(facility_names[0]);

    while (1) {
        printf("\n请选择场地类型:\n");
        for (int i = 0; i < facility_count; i++) {
            printf("%d. %s\n", i + 1, facility_names[i]);
        }
        printf("%d. 返回上一级菜单\n", facility_count + 1);
        printf("选择一个选项: ");
        scanf("%d", &choice);
        system("cls");

        if (choice >= 1 && choice <= facility_count) {
            const char* facility_name = facility_names[choice - 1];
            display_facilities(root, facility_name);

            while (1) {
                printf("\n1. 更改场地状态\n");
                printf("2. 返回上一级菜单\n");
                printf("选择一个选项: ");
                scanf("%d", &choice);
                system("cls");

                if (choice == 1) {
                    printf("输入场地编号: ");
                    scanf("%d", &court_id);
                    printf("输入新状态 (0: 空闲, 1: 占用, 2: 故障): ");
                    scanf("%d", &new_status);
                    change_status(root, facility_name, court_id, new_status);
                    display_facilities(root, facility_name);
                }
                else if (choice == 2) {
                    break;
                }
                else {
                    printf("无效选择\n");
                }
            }

        }
        else if (choice == facility_count + 1) {
            // 更新后的JSON字符串
            char* updated_json_string = cJSON_Print(root);
            // 将更新后的JSON字符串写入文件
            write_file("sports_facility_status.json", updated_json_string);
            // 释放内存
            free(updated_json_string);
            cJSON_Delete(root);
            free(json_string);
            break;
        }
        else {
            printf("无效选择\n");
        }
    }
    admin_interface();
}