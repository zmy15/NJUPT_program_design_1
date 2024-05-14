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


//1为可选 2为故障 3为占用




int jiance(int a, int* b,int length)	//检测场地号输入是否正确
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


// site_state 场地状态 1为可选 2为故障 3为占用 
void site_state()
{
	printf("以下为可选场地：\n");
	printf("\n");
	printf("羽毛球可选场地：\n");
	int i;
	for (i = 0; i < 6; i++)
	{
		if (*(yu1+i) == 1)
		{
			printf("%d号场地\n", i+1);
			printf("  ");
		}
	}
	printf("\n");
	printf("篮球可选场地：\n");
	for (i = 0; i < 6; i++)
	{
		if (*(lan1+i) == 1)
		{
			printf("%d号场地\n", i+1);
			printf("  ");
		}
	}
	printf("\n");
	printf("乒乓球可选场地：\n");
	for (i = 0; i < 6; i++)
	{
		if (*(ping1+i) == 1)
		{
			printf("%d号场地\n", i + 1);
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
	printf("请选择下列操作，预约场地请按1，取消当前预约请按2，报告场地故障请按3\n");
	int a;  //上面选择的操作存在a里面
	scanf_s("%d", &a);
	int i=0, k = 0;
	int q = 0;//存error的1个变量
	switch(a)
	{
		case 1:
		{
			printf("请选择预约场地的类型，羽毛球请选1，篮球请选2，乒乓球请选3\n");
			int b;
			scanf_s("%d", &b);
			switch (b)
			{
				case 1:
				{
					printf("可选场地有：\n");
					for (i = 0; i < 6; i++)
					{
						if (*(yu1 + i) == 1)
						{
							//int* panduan1 = panduan;
							//*(panduan1 + k++) = *(yu1 + i);
							printf("%d号场地", i + 1);
							printf("  ");
						}
					}
					int c;
					do {
						printf("请选择要预约对应场地的数字\n");
						scanf_s("%d", &c);
					} while (jiance(c, yu_state, 6));
					printf("预约成功\n");
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
					printf("可选场地有：\n");
					for (i = 0; i < 6; i++)
					{
						if (*(lan1 + i) == 1)
						{
							//int* panduan1 = panduan;
							//*(panduan1 + k++) = *(lan1 + i);
							printf("%d号场地\n", i + 1);
							printf("  ");
						}
					}
					int c;
					do {
						printf("请选择要预约对应场地的数字:\n");
						scanf_s("%d", &c);
					} while (jiance(c, lan_state, 8));
					printf("预约成功\n");
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
					printf("可选场地有：\n");
					for (i = 0; i < 6; i++)
					{
						if (*(ping1 + i) == 1)
						{
							//int* panduan1 = panduan;
							//*(panduan1 + k++) = *(ping1 + i);
							printf("%d号场地", i + 1);
							printf("  ");
						}
					}

					int c;
					do {
						printf("请选择要预约对应场地的数字:\n");
						scanf_s("%d", &c);
					} while (jiance(c, ping_state, 10));
					printf("预约成功\n");
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
					printf("请注意输入\n");
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

			printf("不好意思同学，给你带来了不好的体验，谢谢你的反馈\n");
			do {
				printf("请输入设备故障场地的数量:\n");
				scanf_s("%d", &q);
			} while (q<=0||q>=24);
			printf("请输入场地编号，羽毛球场百位为1，篮球场百位为2，乒乓球百位为3\n");
			printf("例如羽毛球三号场为103\n");
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




