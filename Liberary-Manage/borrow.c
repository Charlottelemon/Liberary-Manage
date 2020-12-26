#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <string.h>
#include "borrow.h"
int Maxstubw = 10;    //ѧ�����ɽ�
int Maxteabw = 15;    //��ʦ���ɽ�
float Delaytopay = 1;     //ÿ����һ��֧������
int Applyforday = 30;    //���ν����Լ����������

struct Borrowitem
{
	int id;
	char name[18];
	float price;
	int no;
	int symbol;
	int level;
	int isreturn;
	time_t bowdate;   //time_t������long���ʹ洢1970�����������
	int retdate; 
	float payfor;
}bowitem;

int toMax(int level,int no)   //�ж϶��߽������
{
	int num;
	if (level == 1)
		num = Maxstubw;
	else
		num = Maxteabw;
	FILE *fp = fopen("borrowed.txt", "rb");
	while (1)
	{
		int i = 1;
		i = fread(&bowitem, sizeof(struct Borrowitem), 1, fp);
		if (bowitem.level == level && bowitem.no == no && bowitem.isreturn == 0)
			num--;
		if (i == 0)
			break;
	}
	fclose(fp);

	return num;
}

int countbow()   //���ؽ��ı�ļ�¼����
{
	FILE *fp;
	fp = fopen("borrowed.txt", "rb");
	struct Borrowitem count;
	int num = 0;
	while (1)
	{
		int n = 1;
		n = fread(&count, sizeof(struct Borrowitem), 1, fp);
		if (n == 0)
			break;
		num++;
	}
	fclose(fp);

	return num;
}

void tranDate(time_t t)   //��time_t����ת��������ʱ��
{
	//t = time(NULL);
	char *time;
	time = ctime(&t);
	char str[10];  //��Ĭ�ϵ�ʱ���ʽ��ȡ����-��-��ģʽ
	str[0] = time[20];
	str[1] = time[21];
	str[2] = time[22];
	str[3] = time[23];
	str[4] = time[4];
	str[5] = time[5];
	str[6] = time[6];
	str[7] = time[8];
	str[8] = time[9];
	str[9] = '\0';

	printf("%s\t", str);
}

void borrowed(int level, int symbol, int id, int no)    //����
{
	if (toMax(level, no) > 0)
	{
		printf("��������:");
		scanf("%s", &bowitem.name);
		printf("����۸�:");
		scanf("%f", &bowitem.price);
		bowitem.id = id;
		bowitem.no = no;
		bowitem.level = level;
		bowitem.symbol = symbol;
		bowitem.isreturn = 0;
		bowitem.bowdate = time(NULL);
		bowitem.retdate = 1;   //�����1����1*30*24*3600��
		bowitem.payfor = 0;
		FILE *fp = fopen("borrowed.txt", "ab");
		fwrite(&bowitem, sizeof(struct Borrowitem), 1, fp);
		fclose(fp);
		printf("-----�����ɹ�-----\n");
	}
	else
		printf("-----��ǰ�޽��Ĵ������뻹�������-----\n");
}

void display()
{
	FILE *fp;
	fp = fopen("borrowed.txt", "rb");
	printf("�鼮���|����֤��|�鼮���|�������|\t����\t| �۸� |  ��������  |  ��������  |�Ƿ�黹|������\n");
	while (1)
	{
		int n = 0;
		n = fread(&bowitem, sizeof(struct Borrowitem), 1, fp);
		if (n == 0)
			break;

		printf("%03d\t%03d\t",bowitem.id,bowitem.no);
		if (bowitem.symbol == 1)
			printf("�鼮");
		else if (bowitem.symbol == 2)
			printf("�ڿ�");
		else
			printf("����");
		if (bowitem.level == 1)
			printf("\tѧ��");
		else
			printf("\t��ʦ");
		printf("\t%s\t%.2f\t",bowitem.name,bowitem.price);
		tranDate(bowitem.bowdate);
		tranDate(bowitem.bowdate + bowitem.retdate*Applyforday*24*3600);
		if (bowitem.isreturn == 0)
			printf("��");
		else
			printf("��");
		printf("\t%.2f\n", bowitem.payfor);
	}
	fclose(fp);
	printf("\n");
}

int udRecord(int am,int bn,int signal)     //�������
{
	int a[4],pos=1;
	a[0] = am;
	a[1] = bn;
	printf("����������[1]ѧ��[2]��ʦ���Լ�����֤�ţ�");
	scanf("%d%d", &a[2], &a[3]);
	int m = countbow(),j;
	struct Borrowitem udbow[20];    //��֧���ñ�����ʼ������
	FILE *fp;
	fp = fopen("borrowed.txt", "rb");
	while (1)
	{
		int i = 1;
		i = fread(&bowitem, sizeof(struct Borrowitem), 1, fp);
		if (i == 0)
		{
			pos = -1;
			break;
		}
		else if (bowitem.symbol == a[0] && bowitem.id == a[1] && bowitem.level == a[2] && bowitem.no == a[3] && bowitem.isreturn == 0)   //ֻ����δ�黹��
		{
			printf("��%s��\t������֤�ţ�%03d\t���������ڣ�", bowitem.name, bowitem.no);
			tranDate(bowitem.bowdate);
			printf("\t(��������)");
			tranDate(bowitem.bowdate + bowitem.retdate*Applyforday * 24 * 3600);
			printf("\n");
			break;
		}
		pos++;   //���λ��
		
	}
	
	rewind(fp);    //�ļ�ָ��ص��ļ�ͷ
	fread(&udbow, sizeof(struct Borrowitem), m, fp);     //����д��
	fp = fopen("borrowed.txt", "wb");
	if (pos != -1 && signal == 1)
	{
		if (bowitem.retdate == 1)   //�ж�֮ǰ�Ƿ������
		{
			//struct Borrowitem *udbow = (struct Borrowitem *)malloc(m * sizeof(struct Borrowitem));   
			bowitem.retdate++;
			for (j = 0; j < m; j++)
			{
				if (j + 1 != pos)
					fwrite(&udbow[j], sizeof(struct Borrowitem), 1, fp);
				else
					fwrite(&bowitem, sizeof(struct Borrowitem), 1, fp);
			}
			printf("-----����ɹ�-----\n");
		}
		else
		{
			printf("-----����ʧ�ܣ�ֻ������һ��-----\n");
			fwrite(&udbow, sizeof(struct Borrowitem), m, fp);   //����ʧ�ܣ�����ԭ�ⲻ��д��
		}
	}
	else if (pos != -1 && signal == 2)
	{
		time_t now = time(NULL);   //��ȡ��ǰʱ��
		//struct Borrowitem *udbow = malloc(m * sizeof(struct Borrowitem));   
		bowitem.isreturn = 1;
		if (now - bowitem.bowdate > bowitem.retdate*Applyforday*24*3600)   //�뻹��ʱ�����Ա�
			bowitem.payfor = ((now - bowitem.bowdate) / (24 * 3600)-bowitem.retdate*Applyforday)*Delaytopay;  //���㷣����
		for (j = 0; j < m; j++)
		{
			if (j + 1 != pos)
				fwrite(&udbow[j], sizeof(struct Borrowitem), 1, fp);
			else
				fwrite(&bowitem, sizeof(struct Borrowitem), 1, fp);
		}
		showDelay(a[2], a[3]);    //��ʾ�ö�������δ������
		printf("-----�����ɹ�-----\n");
	}
	else
	{
		printf("-----û����ؽ��ļ�¼-----\n"); 
		fwrite(&udbow, sizeof(struct Borrowitem), m, fp);
	}
	fclose(fp);
	return pos;
}

void showDelay(int level,int no)      //��ʾ����δ�黹����,(-1,-1)��ʾ�����û���Ϣ�����������ʾ���û���Ϣ
{
	FILE *fp;
	fp = fopen("borrowed.txt", "rb");
	time_t now = time(NULL);    //��ȡ��ǰʱ��
	struct Borrowitem bwitem;
	if (level == -1 && no == -1)
	{
		printf("�鼮���|  ����\t|����֤��|  ��������  |  ��������  |������\n");
		while (1)
		{
			int n = 1;
			n = fread(&bwitem, sizeof(struct Borrowitem), 1, fp);
			if (n != 0 && now > bwitem.bowdate + bwitem.retdate*Applyforday * 24 * 3600)
			{
				printf(" %03d  %s   %d\t", bwitem.id, bwitem.name, bwitem.no);
				tranDate(bwitem.bowdate);
				printf("\t");
				tranDate(bwitem.bowdate + bwitem.retdate*Applyforday * 24 * 3600);
				printf("\t%.2f\n", bwitem.payfor);
			}
			if (n == 0)
				break;
		}
	}
	else
	{
		printf("Ŀǰ������δ�黹����--\n�鼮���|   ����\t|����֤��|  ��������  |  ��������  |������\n");
		while (1)
		{
			int n = 1;
			n = fread(&bwitem, sizeof(struct Borrowitem), 1, fp);
			if (n != 0 && bwitem.no == no && bwitem.level == level && (bwitem.bowdate + bwitem.retdate*Applyforday * 24 * 3600) < now)
			{
				printf(" %03d  %s   %d\t", bwitem.id, bwitem.name, bwitem.no);
				tranDate(bwitem.bowdate);
				printf("\t");
				tranDate(bwitem.bowdate + bwitem.retdate*Applyforday * 24 * 3600);
				printf("\t%.2f\n", bwitem.payfor);
			}
			if (n == 0)
				break;
		}
	}
	printf("\n");
	fclose(fp);
}

/*void ranking(int id, int symbol)    //��������
{
	//�������Ž��ı�����һ�����飬���ִ��������ŵ�һ
}*/
