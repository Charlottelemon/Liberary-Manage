#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liberary.h"

struct Bookitem
{
	int id;
	char name[20];
	char author[10];
	char publish[20];
	char date[8];
	float price;
	int class;
	int totalnum;
	int nownum;
	int borrowed;
}bookitem;

int searchitem(int symbol,int id)    //���Ҳ�����ͼ���λ��
{
	FILE *fp;
	struct Bookitem ifexist;
	int pos = 1;  //��Ǹñ�ŵ�λ��
	if (symbol == 1)
		fp = fopen("books.txt", "rb");
	else if (symbol == 2)
		fp = fopen("papers.txt", "rb");
	else
		fp = fopen("newspaper.txt", "rb");
	while (1)
	{
		int n = 0;
		n = fread(&ifexist, sizeof(struct Bookitem), 1, fp);
		if (n == 0)
		{
			pos = 0;
			break;
		}
		else if (ifexist.id == id)
			break;
		pos++;
	}
	fclose(fp);

	return pos;
}

void additem(int symbol)      //���ͼ��
{
	printf("��ţ� ");
	scanf("%d", &bookitem.id);
	printf("������ ");
	scanf("%s", &bookitem.name);
	printf("���ߣ� ");
	scanf("%s", &bookitem.author);
	printf("�����磺 ");
	scanf("%s", &bookitem.publish);
	printf("����ʱ�䣺 ");
	scanf("%s", &bookitem.date);
	printf("�۸� ");
	scanf("%f", &bookitem.price);
	printf("����������� ");
	scanf("%d", &bookitem.totalnum);
	printf("��ǰ��棺 ");
	scanf("%d", &bookitem.nownum);
	printf("�ѽ�������� ");
	scanf("%d", &bookitem.borrowed);
	bookitem.class = symbol;

	if (searchitem(symbol, bookitem.id) == 0)
	{
		if (symbol == 1)
		{
			FILE *fp = fopen("books.txt", "ab");    //�ļ������Դ������ͬһ��Ŀ¼
			if (fp != NULL)
			{
				fwrite(&bookitem, sizeof(struct Bookitem), 1, fp);
				fclose(fp);
			}
			else
				printf("error\n");
		}
		else if (symbol == 2)
		{
			FILE *fp = fopen("papers.txt", "ab");
			fwrite(&bookitem, sizeof(struct Bookitem), 1, fp);
			fclose(fp);
		}
		else
		{
			FILE *fp = fopen("newspaper.txt", "ab");
			fwrite(&bookitem, sizeof(struct Bookitem), 1, fp);
			fclose(fp);
		}
		printf("-----��ӳɹ�-----\n");
	}
	else
		printf("-----------����ظ������������룡\n");

}

void getitem(int no)     //��ȡͼ��
{
	FILE *fp;
	printf("���  ����      ����  ������  ����ʱ��  �۸�  ���鼮1/�ڿ�2/����3��  �������  ��ǰ���  �ѽ������\n");
	if (no == 1)
		fp = fopen("books.txt", "rb");
	else if (no == 2)
		fp = fopen("papers.txt", "rb");
	else
		fp = fopen("newspaper.txt", "rb");
	while (1)
	{
		int n=0;
		n = fread(&bookitem, sizeof(struct Bookitem), 1, fp);
		if (n == 0)
			break;

		printf("%03d\t%s\t%s\t%s\t%s\t%.2f\t%d\t %d\t %d\t %d\n", bookitem.id, bookitem.name, bookitem.author, bookitem.publish, bookitem.date,
			bookitem.price, bookitem.class, bookitem.totalnum, bookitem.nownum, bookitem.borrowed);
	}
	fclose(fp);
	printf("\n");
}

int countitem(int symbol)     //�����ļ���ͼ�������
{
	FILE *fp;
	int num = 0;  
	if (symbol == 1)
		fp = fopen("books.txt", "rb");
	else if (symbol == 2)
		fp = fopen("papers.txt", "rb");
	else
		fp = fopen("newspaper.txt", "rb");
	while (1)
	{
		int n = 0;
		n = fread(&bookitem, sizeof(struct Bookitem), 1, fp);
		if (n == 0)
			break;
		num++;
	}
	fclose(fp);

	return num;
}

void removeitem(int symbol)    //ɾ��ͼ���¼
{
	printf("��������ɾ�����鼮��ţ� ");
	int id;
	scanf("%d", &id);
	int n = searchitem(symbol, id),i,cho;
	if (n != 0)
	{
		struct Bookitem removeit[10];
		FILE *fp;
		if (symbol == 1)
			fp = fopen("books.txt", "rb");
		else if (symbol == 2)
			fp = fopen("papers.txt", "rb");
		else
			fp = fopen("newspaper.txt", "rb");
		fseek(fp, (n-1)*sizeof(struct Bookitem),0);     //���ļ�ָ�붨λ��Ҫɾ����������¼
		fread(&bookitem, sizeof(struct Bookitem), 1, fp);
		printf("%03d\t%s\t%s\t%s\t%s\t%.2f\t%d\t%d\t%d\t%d\n", bookitem.id, bookitem.name, bookitem.author, bookitem.publish, bookitem.date,
			bookitem.price, bookitem.class, bookitem.totalnum, bookitem.nownum, bookitem.borrowed);
		rewind(fp);
		printf("[1]����ɾ��\t[2]ȡ�����˳�\n");
		scanf("%d", &cho);
		if (cho == 1)
		{
			int m = countitem(symbol);
			fread(&removeit, sizeof(struct Bookitem), m, fp);

			if (symbol == 1)
				fp = fopen("books.txt", "wb");
			else if (symbol == 2)
				fp = fopen("papers.txt", "wb");
			else
				fp = fopen("newspaper.txt", "wb");
			for (i = 0; i < m; i++)
			{
				if (i + 1 != n)
					fwrite(&removeit[i], sizeof(struct Bookitem), 1, fp);
			}
			printf("-----ɾ���ɹ�-----\n");
		}
		fclose(fp);
	}
	else
		printf("-----�����ڱ��Ϊ%03d���鼮��-----\n", id);
}

void updateitem(int symbol)     //�޸���Ϣ����ɾ����Ϣ����
{
	printf("���������޸ĵ��鼮��ţ� ");
	int id;
	scanf("%d", &id);
	int n = searchitem(symbol, id),cho,i;
	if (n != 0)
	{
		struct Bookitem removeit[10],tempitem;
		FILE *fp;
		if (symbol == 1)
			fp = fopen("books.txt", "rb");
		else if (symbol == 2)
			fp = fopen("papers.txt", "rb");
		else
			fp = fopen("newspaper.txt", "rb");
		fseek(fp, (n-1) * sizeof(struct Bookitem), 0);
		fread(&bookitem, sizeof(struct Bookitem), 1, fp);
		printf("%03d\t%s\t%s\t%s\t%s\t%.2f\t%d\t%d\t%d\t%d\n", bookitem.id, bookitem.name, bookitem.author, bookitem.publish, bookitem.date,
			bookitem.price, bookitem.class, bookitem.totalnum, bookitem.nownum, bookitem.borrowed);
		rewind(fp);

		printf("��ţ� ");
		scanf("%d", &tempitem.id);
		printf("������ ");
		scanf("%s", &tempitem.name);
		printf("���ߣ� ");
		scanf("%s", &tempitem.author);
		printf("�����磺 ");
		scanf("%s", &tempitem.publish);
		printf("����ʱ�䣺 ");
		scanf("%s", &tempitem.date);
		printf("�۸� ");
		scanf("%f", &tempitem.price);
		printf("����������� ");
		scanf("%d", &tempitem.totalnum);
		printf("��ǰ��棺 ");
		scanf("%d", &tempitem.nownum);
		printf("�ѽ�������� ");
		scanf("%d", &tempitem.borrowed);
		tempitem.class = symbol;
		printf("[1]�����޸�\t[2]ȡ�����˳�\n");
		scanf("%d", &cho);
		if (cho == 1)
		{
			int m = countitem(symbol);
			fread(&removeit, sizeof(struct Bookitem), m, fp);

			if (symbol == 1)
				fp = fopen("books.txt", "wb");
			else if (symbol == 2)
				fp = fopen("papers.txt", "wb");
			else
				fp = fopen("newspaper.txt", "wb");
			for (i = 0; i < m; i++)
			{
				if (i + 1 != n)
					fwrite(&removeit[i], sizeof(struct Bookitem), 1, fp);
				else
					fwrite(&tempitem, sizeof(struct Bookitem), 1, fp);
			}
			printf("-----�޸ĳɹ�-----\n");
		}
		fclose(fp);
	}
	else
		printf("-----�����ڱ��Ϊ%03d���鼮��-----\n", id);
}

int udbrrowed(int symbol,int id,int aord)    //ÿ�ν����������ͼ����
{
	int n = searchitem(symbol, id), m = countitem(symbol),i;
	//struct Bookitem *removeit = malloc(m*sizeof(struct Bookitem));
	struct Bookitem removeit[10];
	FILE *fp;
	if (symbol == 1)
		fp = fopen("books.txt", "rb");
	else if (symbol == 2)
		fp = fopen("papers.txt", "rb");
	else
		fp = fopen("newspaper.txt", "rb");
	fseek(fp, (n - 1) * sizeof(struct Bookitem), 0);
	fread(&bookitem, sizeof(struct Bookitem), 1, fp);
	rewind(fp);
	fread(&removeit, sizeof(struct Bookitem), m, fp);
	if (aord == 1 && bookitem.nownum > 0)    //���飬��ǰ��������Ϊ0
	{
		bookitem.nownum -= 1;
		bookitem.borrowed += 1;
		if (symbol == 1)
			fp = fopen("books.txt", "wb");
		else if (symbol == 2)
			fp = fopen("papers.txt", "wb");
		else
			fp = fopen("newspaper.txt", "wb");
		for (i = 0; i < m; i++)
		{
			if (i + 1 != n)
				fwrite(&removeit[i], sizeof(struct Bookitem), 1, fp);
			else
				fwrite(&bookitem, sizeof(struct Bookitem), 1, fp);
		}
		fclose(fp);
		return 1;
	}
	else if (aord == -1 && bookitem.borrowed > 0)    //���飬�ѽ����������Ϊ0
	{
		bookitem.nownum += 1;
		bookitem.borrowed -= 1;
		if (symbol == 1)
			fp = fopen("books.txt", "wb");
		else if (symbol == 2)
			fp = fopen("papers.txt", "wb");
		else
			fp = fopen("newspaper.txt", "wb");
		for (i = 0; i < m; i++)
		{
			if (i + 1 != n)
				fwrite(&removeit[i], sizeof(struct Bookitem), 1, fp);
			else
				fwrite(&bookitem, sizeof(struct Bookitem), 1, fp);
		}
		fclose(fp);
		return 1;
	}
	else
	{
		if(aord == 1)
			printf("-----���鵱ǰû�п��-----\n");
		else
			printf("-----�����Ƿ���û�н��ļ�¼-----\n");
		fclose(fp);
		return 0;
	}
	
}