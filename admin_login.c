#define _CRT_SECURE_NO_WARNINGS 1
#include"file.h"
#include"admin.h"
#include<string.h>
#include<stdio.h>
#include<Windows.h>

void admin_login()//����Ա��¼
{
    while (1) {
        ADMIN admin_login;
        ui("admin_login_ui.txt");//����UI����
        //��ȡ�û�����
        printf("������������");
        scanf("%s", &admin_login.name);
        Encrypted_input_ADMIN(&admin_login);
        printf("�����빤�ţ�");
        scanf("%s", &admin_login.ID);
        //���е�¼
        if (strcmp(admin_login.name, "admin") == 0 && strcmp(admin_login.password, "password") == 0 && strcmp(admin_login.ID, "1234") == 0)
        {
            printf("��¼�ɹ���");
            system("cls");
            admin_interface();//����Ա����
            return; // exit the function after successful login
        }
        else
        {
            printf("�˺Ż�������󣬵�¼ʧ�ܣ�\n");
            int choice;
            printf("1.����\n2.������һ��\n3.�˳�ϵͳ\n");
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
                printf("��Чѡ����������롣\n");
                break;
            }
        }
    }
}
