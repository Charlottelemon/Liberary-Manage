#include <stdio.h>
//#include <windows.h>
#include <stdlib.h>
#include "liberary.h"
#include "reader.h"
#include "borrow.h"

int main()
{
	//���ɲ˵�
	while (1)
	{
		int str = 0,s;
		printf("----------%d%20dͼ��ݹ���ϵͳ%d%20d----------\n",str,str,str,str);
		printf("\n%31d-�������ѡ��-\n%31d[1]ͼ��������\n%31d[2]����������\n%31d[3]���ĵǼǹ���\n%31d[4]�޸�ϵͳ����\n%31d[0]�˳�ϵͳ\n",str,str,str,str,str,str);
		printf("input:");
		scanf("%d", &s);
		if (s == 1)
		{
			while (1)
			{
				printf("[1]���ͼ��\t[2]ɾ��ͼ��\t[3]�޸���Ϣ\t[4]�鿴ͼ��\t[0]�˳�\n");
				scanf("%d", &s);
				if (s == 1)
				{
					printf("ѡ��ͼ����� [1]�鼮\t[2]�ڿ�\t[3]����\n");
					scanf("%d", &s);
					additem(s);
				}
				else if (s == 2)
				{
					printf("ѡ��ͼ����� [1]�鼮\t[2]�ڿ�\t[3]����\n");
					scanf("%d", &s);
					removeitem(s);
				}
				else if (s == 3)
				{
					printf("ѡ��ͼ����� [1]�鼮\t[2]�ڿ�\t[3]����\n");
					scanf("%d", &s);
					updateitem(s);
				}
				else if (s == 4)
				{
					printf("ѡ��ͼ����� [1]�鼮\t[2]�ڿ�\t[3]����\n");
					scanf("%d", &s);
					getitem(s);
				}
				else
					break;
			}
		}
		else if (s == 2)
		{
			while (1)
			{
				printf("[1]��Ϣ¼��\t[2]ע������\t[3]�޸���Ϣ\t[4]�鿴����\t[0]�˳�\n");
				scanf("%d", &s);
				if (s == 1)
				{
					printf("ѡ�������� [1]ѧ��\t[2]��ʦ\n");
					scanf("%d", &s);
					setreader(s);
				}
				else if (s == 2)
				{
					printf("ѡ�������� [1]ѧ��\t[2]��ʦ\n");
					scanf("%d", &s);
					remreader(s);
				}
				else if (s == 3)
				{
					printf("ѡ�������� [1]ѧ��\t[2]��ʦ\n");
					scanf("%d", &s);
					udreader(s);
				}
				else if (s == 4)
				{
					printf("ѡ�������� [1]ѧ��\t[2]��ʦ\n");
					scanf("%d", &s);
					getreader(s);
				}
				else
					break;
			}
		}
		else if (s == 3)
		{
			while (1)
			{
				printf("[1]����\t[2]����\t[3]����\t[4]�鿴ȫ����Ϣ\t[5]����δ����Ϣ\t[0]�˳�\n");
				scanf("%d", &s);
				if (s == 1)
				{
					int a[4];
					printf("����������[1]�鼮[2]�ڿ�[3]�������Լ���ı�ţ�");
					scanf("%d%d", &a[0], &a[1]);
					if (searchitem(a[0], a[1]) != 0)
					{
						if (udbrrowed(a[0], a[1], 1) == 1)
						{
							printf("����������[1]ѧ��[2]��ʦ���Լ�����֤�ţ�");
							scanf("%d%d", &a[2], &a[3]);
							if (searchreader(a[2], a[3]) > 0)
							{
								borrowed(a[2], a[0], a[1], a[3]);
							}
							else if (searchreader(a[2], a[3]) == 0)
							{
								printf("-----�������������֤��-----\n");
								udbrrowed(a[0], a[1], -1);   //�������������ļ���д����
							}
							else
							{
								printf("-----�˽���֤�ѱ���ʧ-----\n");
								udbrrowed(a[0], a[1], -1);
							}
						}
					}
					else
						printf("-----�����ڱ��Ϊ%03d���鼮��-----\n", a[1]);
				}
				else if (s == 2)   //���ֻ������һ��
				{
					int m, n;
					printf("����������[1]�鼮[2]�ڿ�[3]�������Լ���ı�ţ�");
					scanf("%d%d", &m, &n);
					udRecord(m,n,1);
				}
				else if (s == 3)
				{
					int m, n;
					printf("����������[1]�鼮[2]�ڿ�[3]�������Լ���ı�ţ�");
					scanf("%d%d", &m, &n);
					if(udRecord(m, n, 2) != -1)
						udbrrowed(m,n,-1);    //�޸�����ı��������޸�ͼ��������
				}
				else if (s == 4)
				{
					display();
				}
				else if (s == 5)
				{
					printf("-----��ʾ���е���δ�黹�Ľ�����Ϣ-----\n");
					showDelay(-1, -1);
				}
				else
					break;
			}
		}
		else if (s == 4)   //������õ��Ǹı�ȫ�ֱ����ķ�ʽ��ֻ���ڱ������иı��ʼֵ��Ҫ���øı���Ҫ�����ļ���¼
		{
			while (1)
			{
				printf("[1]ѧ�����ɽ豾��\t[2]��ʦ���ɽ豾��\t[3]��������\t[4]����ÿ�շ���\t[0]�˳�\n");
				scanf("%d", &s);
				if (s == 1)
				{
					printf("Now : %d\tSet :",Maxstubw);
					scanf("%d", &s);
					Maxstubw = s;
				}
				else if (s == 2)
				{
					printf("Now : %d\tSet :",Maxteabw);
					scanf("%d", &s);
					Maxteabw = s;
				}
				else if (s == 3)
				{
					printf("Now : %d\tSet :",Applyforday);
					scanf("%d", &s);
					Applyforday = s;
				}
				else if (s == 4)
				{
					float st;
					printf("Now : %.2f\t  Set :",Delaytopay);
					scanf("%f", &st);
					Delaytopay = st;
				}
				else
					break;
			}
		}
		else
			break;
		
	}

	return 0;
}
