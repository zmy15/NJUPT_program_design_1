#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include"file.h"
#include"student.h"
#include<Windows.h>
#include<string.h>

#define MAX_STUDENTS 100

STU student_login;
void _student_login()  //学生登录
{
    int i = -1;
    STU student[MAX_STUDENTS];
    int num_student;
    cJSON* root = readJSONFile("student_information.json");
    if (root != NULL) {
        num_student = parseJSONToStudents(root, student, MAX_STUDENTS);
        cJSON_Delete(root);
    }
    int loggedIn = 0; // flag to track if login was successful
    while (!loggedIn) // continue until logged in successfully
    {
        printf("请输入姓名：");
        //学生输入信息
        scanf("%s", &student_login.name);
        Encrypted_input_STU(&student_login);
        printf("请输入学号：");
        scanf("%s", &student_login.ID);

        //判断账号密码是否正确
        for (i = 0; i < num_student; i++)
        {
            if (strcmp(student_login.name, student[i].name) == 0 &&
                strcmp(student_login.password, student[i].password) == 0 &&
                strcmp(student_login.ID, student[i].ID) == 0)
            {
                loggedIn = 1; // set flag indicating successful login
                break;
            }
        }

        if (!loggedIn)
        {
            printf("账号或密码错误，登录失败！\n");
            int choice;
            printf("1.重试\n2.注册\n3.退出系统\n");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                system("cls");
                break; // retry login
            case 2:
                system("cls");
                student_sign_up(); // sign up new student
                return; // exit login function
            case 3:
                return; // exit program
            default:
                printf("无效选项，请重新输入。\n");
                break;
            }
        }
    }
    system("cls");
    printf("登录成功！\n");
    student_interface();    //登录成功跳转到学生界面
}
