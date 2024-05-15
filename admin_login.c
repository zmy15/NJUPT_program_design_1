#define _CRT_SECURE_NO_WARNINGS 1
#include"file.h"
#include"admin.h"
#include<string.h>
#include<stdio.h>
#include<Windows.h>

void admin_login()//管理员登录
{
    while (1) {
        ADMIN admin_login;
        ui("admin_login_ui.txt");//绘制UI界面
        //获取用户输入
        printf("请输入姓名：");
        scanf("%s", &admin_login.name);
        Encrypted_input_ADMIN(&admin_login);
        printf("请输入工号：");
        scanf("%s", &admin_login.ID);
        //进行登录
        if (strcmp(admin_login.name, "admin") == 0 && strcmp(admin_login.password, "password") == 0 && strcmp(admin_login.ID, "1234") == 0)
        {
            printf("登录成功！");
            system("cls");
            admin_interface();//管理员界面
            return; // exit the function after successful login
        }
        else
        {
            printf("账号或密码错误，登录失败！\n");
            int choice;
            printf("1.重试\n2.返回上一级\n3.退出系统\n");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                system("cls");
                break; // retry login
            case 2:
                system("cls");
                main(); // return to the previous level
            case 3:
                exit(0); // exit the program
            default:
                printf("无效选项，请重新输入。\n");
                break;
            }
        }
    }
}
