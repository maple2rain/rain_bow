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
	struct ThunderNode *next;	//下一位指针
	double Coord[3];			//闪电结点坐标
}ThunderNode;

typedef struct ThunderNodeList {
	int numOfNode;				//结点数
	ThunderNode *head;			//指向闪电头结点
}ThunderNodeList;

typedef struct ThunderTree {
	ThunderNodeList *head;		//指向闪电分支结点
	struct ThunderTree *next;	//指向下一个分支
	double Coord[3];			//闪电结点坐标
}ThunderTree;

typedef struct ThunderTreeList {
	ThunderTree *head;			//指向闪电第一分支
	int numOfTree;				//单棵闪电分支的数量
	int visitTimes;				//访问次数
	int numOfAllNodes;			//总结点数
	int flag;					//绘制闪电或消灭闪电的标志
}ThunderTreeList;

typedef struct ThunderList {
	ThunderTreeList *head;		//指向闪电树的头结点
	struct ThunderList *next;	//指向下一棵闪电
}ThunderList;

typedef struct Thunders {
	int numOfThunder;			//闪电的数量
	ThunderList *head;			//指向第一个闪电
}Thunders;

/****************************************************************************************
*	Function Define Section
****************************************************************************************/
//初始化闪电总链表
Status InitThunderList(Thunders *L);

//插入闪电
Status InsertThundersList(Thunders *L);

//获取第index棵闪电
Status GetIndexThunders(Thunders *L, int index, ThunderTreeList *treeList);

//删除第index棵闪电
Status DeleteThunder(Thunders *L, int index);

//初始化创建闪电结点链表
Status InitThunderNodeList(ThunderNodeList *L);

//插入闪电结点
Status InsertThunderNode(ThunderNodeList *L, double coord[]);

//创建闪电结点链表
Status CreateThunderNodeList(ThunderNodeList *L, int num, double coord[]);

//获取第index个闪电结点值
Status GetIndexThunderNode(ThunderNodeList *L, int index, double coord[]);

//销毁闪电结点链表
void DestoryThunderNodeList(ThunderNodeList *L);

//初始化闪电分支链表
Status InitThunderTreeList(ThunderTreeList *L);

//插入闪电树分支结点
Status InsertThunderTree(ThunderTreeList *L);

//被访问的次数增加
void IncreaseThunderTreeVisitTimes(Thunders *thunders, int index);

//被访问的次数减少
void DecreaseThunderTreeVisitTimes(Thunders *thunders, int index);

//重置flag表示为1，表示将逆序展示闪电，及消逝闪电
void ChangeThunderTreeFlag(Thunders *thunders, int index);

//创建闪电树分支链表
Status CreateThunderTreeList(ThunderTreeList *L, int num);

//获取第index个闪电树结点信息
Status GetIndexThunderTree(ThunderTreeList *L, int index, double coord[], ThunderNodeList *nodeList);

//销毁闪电树
void DestoryThunderTreeList(ThunderTreeList *L);
#endif