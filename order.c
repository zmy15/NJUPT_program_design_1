#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yu_state[6] = { 1,1,1,1,1,1,};
int lan_state[8] = { 1,1,1,1,1,1,1,1,};
int ping_state[10] = { 1,1,1,1,1,1,1,1,1,1,};
int error[24] = {0};
int* lan1 = lan_state;
int* yu1 = yu_state;
int* ping1 = ping_state;


//1Ϊ��ѡ 2Ϊ���� 3Ϊռ��




int jiance(int a, int* b,int length)	//��ⳡ�غ������Ƿ���ȷ
{
		if (1 == *(b + a-1))
		{
			return 0;
		}
	return 1;
}

void zero(int* a, int length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		*(a + i) = 0;
	}
}


// site_state ����״̬ 1Ϊ��ѡ 2Ϊ���� 3Ϊռ�� 
void site_state()
{
	printf("����Ϊ��ѡ���أ�\n");
	printf("\n");
	printf("��ë���ѡ���أ�\n");
	int i;
	for (i = 0; i < 6; i++)
	{
		if (*(yu1+i) == 1)
		{
			printf("%d�ų���\n", i+1);
			printf("  ");
		}
	}
	printf("\n");
	printf("�����ѡ���أ�\n");
	for (i = 0; i < 6; i++)
	{
		if (*(lan1+i) == 1)
		{
			printf("%d�ų���\n", i+1);
			printf("  ");
		}
	}
	printf("\n");
	printf("ƹ�����ѡ���أ�\n");
	for (i = 0; i < 6; i++)
	{
		if (*(ping1+i) == 1)
		{
			printf("%d�ų���\n", i + 1);
			printf("\n");
		}
	}
}

void guanli_check()
{
	FILE* pf = NULL;
	errno_t t = fopen_s(&pf, "D:/state.txt", "w+");
	if (t != 0 || NULL == pf)
	{
		exit(1);
	}
	fread(yu_state, sizeof(yu_state), 1, pf);
	fread(lan_state, sizeof(lan_state), 1, pf);
	fread(ping_state, sizeof(ping_state), 1, pf);

	fclose(pf);

}

void student_check()
{
	FILE* pf = NULL;
	errno_t t = fopen_s(&pf, "D:/state.txt", "w+");
	if (t != 0 || NULL == pf)
	{
		exit(1);
	}
	fread(yu_state, sizeof(yu_state), 1, pf);
	fread(lan_state, sizeof(lan_state), 1, pf);
	fread(ping_state, sizeof(ping_state), 1, pf);

	fclose(pf);
	pf = NULL;
	site_state();
	printf("��ѡ�����в�����ԤԼ�����밴1��ȡ����ǰԤԼ�밴2�����泡�ع����밴3\n");
	int a;  //����ѡ��Ĳ�������a����
	scanf_s("%d", &a);
	int i=0, k = 0;
	int q = 0;//��error��1������
	switch(a)
	{
		case 1:
		{
			printf("��ѡ��ԤԼ���ص����ͣ���ë����ѡ1��������ѡ2��ƹ������ѡ3\n");
			int b;
			scanf_s("%d", &b);
			switch (b)
			{
				case 1:
				{
					printf("��ѡ�����У�\n");
					for (i = 0; i < 6; i++)
					{
						if (*(yu1 + i) == 1)
						{
							//int* panduan1 = panduan;
							//*(panduan1 + k++) = *(yu1 + i);
							printf("%d�ų���", i + 1);
							printf("  ");
						}
					}
					int c;
					do {
						printf("��ѡ��ҪԤԼ��Ӧ���ص�����\n");
						scanf_s("%d", &c);
					} while (jiance(c, yu_state, 6));
					printf("ԤԼ�ɹ�\n");
					*(yu1 + c - 1) = 3;
					errno_t t = fopen_s(&pf, "D:/state.txt", "w+");
					if (t != 0 || NULL == pf)
					{
						exit(1);
					}
					fseek(pf, 0L, 0);
					fwrite(yu_state, sizeof(yu_state), 1, pf);
					fclose(pf);
					pf = NULL;
					break;
				}
				case 2:
				{
					printf("��ѡ�����У�\n");
					for (i = 0; i < 6; i++)
					{
						if (*(lan1 + i) == 1)
						{
							//int* panduan1 = panduan;
							//*(panduan1 + k++) = *(lan1 + i);
							printf("%d�ų���\n", i + 1);
							printf("  ");
						}
					}
					int c;
					do {
						printf("��ѡ��ҪԤԼ��Ӧ���ص�����:\n");
						scanf_s("%d", &c);
					} while (jiance(c, lan_state, 8));
					printf("ԤԼ�ɹ�\n");
					*(lan1 + c - 1) = 3;
					errno_t t = fopen_s(&pf, "D:/state.txt", "w+");
					if (t != 0 || NULL == pf)
					{
						exit(1);
					}
					fseek(pf, 24L, 0);
					fwrite(lan_state, sizeof(lan_state), 1, pf);
					fclose(pf);
					pf = NULL;
					break;
				}
				case 3:
				{
					printf("��ѡ�����У�\n");
					for (i = 0; i < 6; i++)
					{
						if (*(ping1 + i) == 1)
						{
							//int* panduan1 = panduan;
							//*(panduan1 + k++) = *(ping1 + i);
							printf("%d�ų���", i + 1);
							printf("  ");
						}
					}

					int c;
					do {
						printf("��ѡ��ҪԤԼ��Ӧ���ص�����:\n");
						scanf_s("%d", &c);
					} while (jiance(c, ping_state, 10));
					printf("ԤԼ�ɹ�\n");
					*(ping1 + c - 1) = 3;
					errno_t t = fopen_s(&pf, "D:/state.txt", "w+");
					if (t != 0 || NULL == pf)
					{
						exit(1);
					}
					fseek(pf, 56L, 0);
					fwrite(ping_state, sizeof(ping_state), 1, pf);
					fclose(pf);
					pf = NULL;
					break;
				}
				default:
					printf("��ע������\n");
			}
		}
		case 2:
		{
			;
		}
		case 3:
		{
			FILE* fp = NULL;
			errno_t t = fopen_s(&pf, "D:/error.txt", "w+");
			if (t != 0 || NULL == fp)
			{
				exit(1);
			}

			printf("������˼ͬѧ����������˲��õ����飬лл��ķ���\n");
			do {
				printf("�������豸���ϳ��ص�����:\n");
				scanf_s("%d", &q);
			} while (q<=0||q>=24);
			printf("�����볡�ر�ţ���ë�򳡰�λΪ1�����򳡰�λΪ2��ƹ�����λΪ3\n");
			printf("������ë�����ų�Ϊ103\n");
			for (i = 0; i < q; i++)
			{
				scanf_s("%d", &error[i]);
			}
			fwrite(error, q*4, 1, fp);
			fclose(fp);
			fp = NULL;
		}
		default:
			break;
	}
}


void test()
{
	zero(yu_state, 6);
	zero(lan_state, 8);
	zero(ping_state, 10);
	yu_state[2] = 1;
	lan_state[3] = 1;
	ping_state[4] = 1;
	FILE* pf = NULL;
	errno_t t = fopen_s(&pf, "D:/state.txt", "w+");
	if (t != 0 || NULL == pf)
	{
		exit(1);
	}
	fwrite(yu_state, sizeof(yu_state), 1, pf);
	fwrite(lan_state, sizeof(lan_state), 1, pf);
	fwrite(ping_state, sizeof(ping_state), 1, pf);

	fclose(pf);
	pf = NULL;
	student_check();
}




