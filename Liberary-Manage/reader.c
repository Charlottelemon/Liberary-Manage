#include <stdio.h>
#include <stdlib.h>
#include "reader.h"
struct Readeritem
{
	int no;
	char name[10];
	char class[12];
	int sno;
	int level;
	int islost;
}reader;

int searchreader(int symbol, int id)
{
	FILE *fp;
	struct Readeritem ifexist;
	int pos = 1;  //��Ǹñ�ŵ�λ��
	if (symbol == 1)
		fp = fopen("students.txt", "rb");
	else
		fp = fopen("teachers.txt", "rb");
	while (1)
	{
		int n = 0;
		n = fread(&ifexist, sizeof(struct Readeritem), 1, fp);
		if (n == 0)
		{
			pos = 0;
			break;
		}
		else if (ifexist.no == id && ifexist.islost == 0)   
			break;
		else if (ifexist.no == id && ifexist.islost == 1)
		{
			pos = -1;
			break;
		}
		pos++;
	}
	fclose(fp);

	return pos;   //����״̬�룺0��ʾû�д˶��ߡ�-1��ʾ���ڵ����ѹ�ʧ��������ʾ����
}

void setreader(int symbol)
{
	printf("�������֤�š��������༶��ѧ�ţ�\n");
	scanf("%d%s%s%d", &reader.no, &reader.name, &reader.class, &reader.sno);
	reader.level = symbol;
	reader.islost = 0;

	if (searchreader(symbol, reader.no) == 0)
	{
		if (symbol == 1)
		{
			FILE *fp = fopen("students.txt", "ab");
			fwrite(&reader, sizeof(struct Readeritem), 1, fp);
			fclose(fp);
		}
		else
		{
			FILE *fp = fopen("teachers.txt", "ab");
			fwrite(&reader, sizeof(struct Readeritem), 1, fp);
			fclose(fp);
		}
		printf("-----¼��ɹ�-----\n");
	}
	else
		printf("----------����֤���Ѵ��ڣ����������룡\n");
	
}

void getreader(int symbol)
{
	FILE *fp;
	if (symbol == 1)
		fp = fopen("students.txt", "rb");
	else
		fp = fopen("teachers.txt", "rb");
	printf("����֤��  ����  �༶  ѧ��  ��ѧ��1/��ʦ2��  ��ʧ����1/��0��\n");
	while (1)
	{
		int n = 0;
		n = fread(&reader, sizeof(struct Readeritem), 1, fp);
		if (n == 0)
			break;
		printf("%03d  %s   %s\t  %d\t  %d\t   %d\n", reader.no, reader.name, reader.class, reader.sno, reader.level, reader.islost);
	}
	fclose(fp);
	printf("\n");
}

int countreader(int symbol)
{
	FILE *fp;
	int num = 0;
	if (symbol == 1)
		fp = fopen("students.txt", "rb");
	else
		fp = fopen("teachers.txt", "rb");
	while (1)
	{
		int n = 0;
		n = fread(&reader, sizeof(struct Readeritem), 1, fp);
		if (n == 0)
			break;
		num++;
	}
	fclose(fp);

	return num;
}

void remreader(int symbol)
{
	printf("��������ɾ���Ķ��߽���֤�ţ� ");
	int id;
	scanf("%d", &id);
	int n = searchreader(symbol, id), i, cho;
	if (n != 0)
	{
		struct Readeritem removeit[10];
		FILE *fp;
		if (symbol == 1)
			fp = fopen("students.txt", "rb");
		else
			fp = fopen("teachers.txt", "rb");
		fseek(fp, (n-1) * sizeof(struct Readeritem), 0);
		fread(&reader, sizeof(struct Readeritem), 1, fp);
		printf("%03d\t%s\t%s\t%d\t%d\t%d\n", reader.no, reader.name, reader.class, reader.sno, reader.level, reader.islost);
		rewind(fp);
		printf("[1]����ɾ��\t[2]ȡ�����˳�\n");
		scanf("%d", &cho);
		if (cho == 1)
		{
			int m = countreader(symbol);
			fread(&removeit, sizeof(struct Readeritem), m, fp);

			if (symbol == 1)
				fp = fopen("students.txt", "wb");
			else
				fp = fopen("teachers.txt", "wb");
			for (i = 0; i < m; i++)
			{
				if (i + 1 != n)
					fwrite(&removeit[i], sizeof(struct Readeritem), 1, fp);
			}
			printf("-----ɾ���ɹ�-----\n");
		}
		fclose(fp);
	}
	else
		printf("-----�����ڽ���֤��Ϊ%03d�Ķ��ߣ�-----\n", id);
}

void udreader(int symbol)
{
	printf("���������޸ĵĶ��߽���֤�ţ� ");
	int id;
	scanf("%d", &id);
	int n = searchreader(symbol, id), cho, i;
	if (n != 0)
	{
		struct Readeritem removeit[10],tempit;
		FILE *fp;
		if (symbol == 1)
			fp = fopen("students.txt", "rb");
		else
			fp = fopen("teachers.txt", "rb");
		fseek(fp, (n-1) * sizeof(struct Readeritem), 0);
		fread(&reader, sizeof(struct Readeritem), 1, fp);
		printf("%03d\t%s\t%s\t%d\t%d\t%d\n", reader.no, reader.name, reader.class, reader.sno, reader.level, reader.islost);
		rewind(fp);

		printf("����֤�ţ� ");
		scanf("%d", &tempit.no);
		printf("������ ");
		scanf("%s", &tempit.name);
		printf("�༶�� ");
		scanf("%s", &tempit.class);
		printf("ѧ�ţ� ");
		scanf("%d", &tempit.sno);
		printf("�Ƿ��ʧ�� ");
		scanf("%d", &tempit.islost);
		tempit.level = symbol;
		printf("[1]�����޸�\t[2]ȡ�����˳�\n");
		scanf("%d", &cho);
		if (cho == 1)
		{
			int m = countreader(symbol);
			fread(&removeit, sizeof(struct Readeritem), m, fp);

			if (symbol == 1)
				fp = fopen("students.txt", "wb");
			else
				fp = fopen("teachers.txt", "wb");
			for (i = 0; i < m; i++)
			{
				if (i + 1 != n)
					fwrite(&removeit[i], sizeof(struct Readeritem), 1, fp);
				else
					fwrite(&tempit, sizeof(struct Readeritem), 1, fp);
			}
			printf("-----�޸ĳɹ�-----\n");
		}
		fclose(fp);
	}
	else
		printf("-----�����ڽ���֤��Ϊ%03d�Ķ��ߣ�-----\n", id);
}