/****************************************************************************************
*	File Name				:	list.h
*	CopyRight				:	LPF
*	ModuleName				:	list
*
*	CPU						:   Inter Core 7
*	RTOS					:
*
*	Create Data				:	2015/12/20
*	Author/Corportation		:	Li PeiFeng
*
*	Abstract Description	:	Declared the struct and function for list
*
*--------------------------------Revision History----------------------------------------
*	No	version		Data		Revised By			Item			Description
*	1							LPF									first coding
*
****************************************************************************************/

/****************************************************************************************
*	Multi-Include-Prevent Section
****************************************************************************************/
#ifndef THUNDER_H_INCLUDED
#define THUNDER_H_INCLUDED

/****************************************************************************************
*	Include File Section
****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "rain.h"

/****************************************************************************************
*	Macro Define Section
****************************************************************************************/

/****************************************************************************************
*	Struct Define Section
****************************************************************************************/

typedef struct ThunderNode {
	struct ThunderNode *next;	//��һλָ��
	double Coord[3];			//����������
}ThunderNode;

typedef struct ThunderNodeList {
	int numOfNode;				//�����
	ThunderNode *head;			//ָ������ͷ���
}ThunderNodeList;

typedef struct ThunderTree {
	ThunderNodeList *head;		//ָ�������֧���
	struct ThunderTree *next;	//ָ����һ����֧
	double Coord[3];			//����������
}ThunderTree;

typedef struct ThunderTreeList {
	ThunderTree *head;			//ָ�������һ��֧
	int numOfTree;				//���������֧������
	int visitTimes;				//���ʴ���
	int numOfAllNodes;			//�ܽ����
	int flag;					//�����������������ı�־
}ThunderTreeList;

typedef struct ThunderList {
	ThunderTreeList *head;		//ָ����������ͷ���
	struct ThunderList *next;	//ָ����һ������
}ThunderList;

typedef struct Thunders {
	int numOfThunder;			//���������
	ThunderList *head;			//ָ���һ������
}Thunders;

/****************************************************************************************
*	Function Define Section
****************************************************************************************/
//��ʼ������������
Status InitThunderList(Thunders *L);

//��������
Status InsertThundersList(Thunders *L);

//��ȡ��index������
Status GetIndexThunders(Thunders *L, int index, ThunderTreeList *treeList);

//ɾ����index������
Status DeleteThunder(Thunders *L, int index);

//��ʼ����������������
Status InitThunderNodeList(ThunderNodeList *L);

//����������
Status InsertThunderNode(ThunderNodeList *L, double coord[]);

//��������������
Status CreateThunderNodeList(ThunderNodeList *L, int num, double coord[]);

//��ȡ��index��������ֵ
Status GetIndexThunderNode(ThunderNodeList *L, int index, double coord[]);

//��������������
void DestoryThunderNodeList(ThunderNodeList *L);

//��ʼ�������֧����
Status InitThunderTreeList(ThunderTreeList *L);

//������������֧���
Status InsertThunderTree(ThunderTreeList *L);

//�����ʵĴ�������
void IncreaseThunderTreeVisitTimes(Thunders *thunders, int index);

//�����ʵĴ�������
void DecreaseThunderTreeVisitTimes(Thunders *thunders, int index);

//����flag��ʾΪ1����ʾ������չʾ���磬����������
void ChangeThunderTreeFlag(Thunders *thunders, int index);

//������������֧����
Status CreateThunderTreeList(ThunderTreeList *L, int num);

//��ȡ��index�������������Ϣ
Status GetIndexThunderTree(ThunderTreeList *L, int index, double coord[], ThunderNodeList *nodeList);

//����������
void DestoryThunderTreeList(ThunderTreeList *L);
#endif