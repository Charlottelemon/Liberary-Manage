#pragma once
#ifndef __BORROW_H__   //��ֹ�ظ�����
#define __BORROW_H__
extern int Maxstubw;   //��Ϊ�ⲿ����ȫ�ֱ���
extern int Maxteabw;
extern float Delaytopay;
extern int Applyforday;

void borrowed(int level, int symbol, int id, int no);
void display();
int udRecord(int m,int n,int signal);
void showDelay(int level,int no);

#endif