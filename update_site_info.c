#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "file.h"

#define MAX_SITES 4
#define HOURS_PER_DAY 24

// Function to get the current date and time
void get_current_date(int* year, int* month, int* day) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    *year = tm.tm_year + 1900;
    *month = tm.tm_mon + 1;
    *day = tm.tm_mday;
}

// Function to update the site_info.json file by removing the previous day's data and updating the last day's data
void update_site_info() {
    int year, month, day;
    get_current_date(&year, &month, &day);

    cJSON* root = cJSON_Parse(read_file("site_info.json"));
    if (!root) {
        root = cJSON_CreateObject();
    }

    char last_day_str[20];
    sprintf(last_day_str, "%d-%02d-%02d", year, month, day - 1);
    cJSON_DeleteItemFromObject(root, last_day_str);

    char date_str[20];
    sprintf(date_str, "%d-%02d-%02d", year, month, day + 6);

    // Check if information for the last day already exists
    cJSON* existing_info = cJSON_GetObjectItem(root, date_str);
    if (existing_info) {
        cJSON_Delete(root);
        return;
    }

    cJSON* daily_schedule = cJSON_CreateObject();
    for (int hour = 9; hour < 21; ++hour) {
        char time_range[20];
        sprintf(time_range, "%02d-%02d", hour, hour + 1);

        cJSON* hourly_schedule = cJSON_CreateObject();
        cJSON_AddItemToObject(daily_schedule, time_range, hourly_schedule);

        for (int site_id = 0; site_id < MAX_SITES; ++site_id) {
            char* site_name;
            switch (site_id) {
            case 0:
                site_name = "badminton";
                cJSON_AddItemToObject(hourly_schedule, site_name, cJSON_CreateIntArray((const int*)calloc(6, sizeof(int)), 6));
                break;
            case 1:
                site_name = "tennis";
                cJSON_AddItemToObject(hourly_schedule, site_name, cJSON_CreateIntArray((const int*)calloc(3, sizeof(int)), 3));
                break;
            case 2:
                site_name = "basketball";
                cJSON_AddItemToObject(hourly_schedule, site_name, cJSON_CreateIntArray((const int*)calloc(8, sizeof(int)), 8));
                break;
            case 3:
                site_name = "pingpang";
                cJSON_AddItemToObject(hourly_schedule, site_name, cJSON_CreateIntArray((const int*)calloc(10, sizeof(int)), 10));
                break;
            default:
                break;
            }
        }
    }
    cJSON_AddItemToObject(root, date_str, daily_schedule);

    char* json_str = cJSON_Print(root);
    write_file("site_info.json", json_str);

    cJSON_Delete(root);
    free(json_str);
}

