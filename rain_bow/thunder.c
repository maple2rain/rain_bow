/****************************************************************************************
*	File Name				:	rain.c
*	CopyRight				:	LPF
*	ModuleName				:	rain
*
*	CPU						:   Inter Core 7
*	RTOS					:
*
*	Create Data				:	2015/12/20
*	Author/Corportation		:	Li PeiFeng
*
*	Abstract Description	:	definite the function for rain
*
*--------------------------------Revision History----------------------------------------
*	No	version		Data		Revised By			Item			Description
*	1							LPF									first coding
*
****************************************************************************************/

/****************************************************************************************
*	Include File Section
****************************************************************************************/
#include "thunder.h"

/****************************************************************************************
*	Function Define Section
****************************************************************************************/
//初始化闪电总链表
Status InitThunderList(Thunders *L)
{
	if (NULL == (L->head = (ThunderList *)malloc(sizeof(ThunderList))))
		return OVERFLOW;

	L->head->next = NULL;
	L->head->head = NULL;
	L->numOfThunder = 0;

	return SUCCESS;
}

//初始化创建闪电结点链表
Status InitThunderNodeList(ThunderNodeList *L)
{
	if (NULL == (L->head = (ThunderNode *)malloc(sizeof(ThunderNode))))
		return OVERFLOW;

	L->head->next = NULL;
	L->numOfNode = 0;

	return SUCCESS;
}

//初始化闪电分支链表
Status InitThunderTreeList(ThunderTreeList *L)
{
	if (NULL == (L->head = (ThunderTree *)malloc(sizeof(ThunderTree))))
		return OVERFLOW;

	L->head->next = NULL;
	L->numOfTree = 0;
	L->visitTimes = 0;
	L->numOfAllNodes = 0;
	L->flag = 0;

	return SUCCESS;
}

//插入闪电结点
Status InsertThunderNode(ThunderNodeList *L, double coord[])
{
	ThunderNode *newNode;
	if (NULL == (newNode = (ThunderNode *)malloc(sizeof(ThunderNode))))
		return OVERFLOW;

	newNode->Coord[0] = coord[0] + 100 - (0.1 * (rand() % 2000));
	newNode->Coord[1] = coord[1] + 100 - (0.1 * (rand() % 2000));
	newNode->Coord[2] = coord[2] + 100 - (0.1 * (rand() % 2000));
	newNode->next = L->head->next;

	L->head->next = newNode;
	L->numOfNode++;
	
	return SUCCESS;
}

//创建闪电结点链表
Status CreateThunderNodeList(ThunderNodeList *L, int num, double coord[])
{
	if (num <= 0)
		return FAIL;

	for (int i = 0; i < num; ++i)
	{
		if(OVERFLOW == InsertThunderNode(L, coord))
			return OVERFLOW;
	}

	return SUCCESS;
}

//获取第index个闪电结点值
Status GetIndexThunderNode(ThunderNodeList *L, int index, double coord[])
{
	ThunderNode *p = L->head;
	if (index < 1 || index > L->numOfNode)
		return FAIL;

	for (int i = 0; i < index; ++i)
	{
		p = p->next;
	}

	for (int i = 0; i < 3; ++i)
	{
		coord[i] = p->Coord[i];
	}
	return SUCCESS;
}

//销毁闪电结点链表
void DestoryThunderNodeList(ThunderNodeList *L)
{
	ThunderNode *p = L->head->next;
	ThunderNode *q = p;
	while (p)
	{
		q = q->next;
		free(p);
		p = q;
	}
	free(L->head);
}

//获取第index个闪电树结点信息
Status GetIndexThunderTree(ThunderTreeList *L, int index, double coord[], ThunderNodeList *nodeList)
{
	ThunderTree *p= L->head;
	if (index < 1 || index > L->numOfTree)
		return FAIL;

	for (int i = 0; i < index; ++i)
	{
		p = p->next;
	}

	for (int i = 0; i < 3; ++i)
	{
		coord[i] = p->Coord[i];
	}
	nodeList->head = p->head->head;
	nodeList->numOfNode = p->head->numOfNode;
	return SUCCESS;
}

//插入闪电树分支结点
Status InsertThunderTree(ThunderTreeList *L)
{
	ThunderTree *newTree;
	int numOfNodes;
	if (NULL == (newTree = (ThunderTree *)malloc(sizeof(ThunderTree))))
		return OVERFLOW;

	newTree->Coord[0] = 600 - (0.1 * (rand() % 12000));
	newTree->Coord[1] = 250 + (0.1 * (rand() % 3000));
	newTree->Coord[2] = 600 - (0.1 * (rand() % 12000));
	newTree->next = L->head->next;

	if (NULL == (newTree->head = (ThunderNodeList *)malloc(sizeof(ThunderNodeList))))
		return OVERFLOW;

	InitThunderNodeList(newTree->head);
	numOfNodes = rand() % 4 + 1;
	if(OVERFLOW == CreateThunderNodeList(newTree->head, numOfNodes, newTree->Coord))
		return OVERFLOW;

	L->head->next = newTree;
	L->numOfTree++;
	L->numOfAllNodes += numOfNodes;

	return SUCCESS;
}

//被访问的次数增加
void IncreaseThunderTreeVisitTimes(Thunders *thunders, int index)
{
	ThunderList *p = thunders->head;
	if (index < 1 || index > thunders->numOfThunder)
		return FAIL;

	for (int i = 0; i < index; ++i)
	{
		p = p->next;
	}
	p->head->visitTimes++;
}

//被访问的次数减少
void DecreaseThunderTreeVisitTimes(Thunders *thunders, int index)
{
	ThunderList *p = thunders->head;
	if (index < 1 || index > thunders->numOfThunder)
		return FAIL;

	for (int i = 0; i < index; ++i)
	{
		p = p->next;
	}
	p->head->visitTimes--;
}

//重置flag表示为1，表示将逆序展示闪电，及消逝闪电
void ChangeThunderTreeFlag(Thunders *thunders, int index)
{
	ThunderList *p = thunders->head;
	if (index < 1 || index > thunders->numOfThunder)
		return FAIL;

	for (int i = 0; i < index; ++i)
	{
		p = p->next;
	}
	p->head->flag = 1;
}

//创建闪电树分支链表
Status CreateThunderTreeList(ThunderTreeList *L, int num)
{
	if (num <= 0)
		return FAIL;

	for (int i = 0; i < num; ++i)
	{
		if (OVERFLOW == InsertThunderTree(L))
			return OVERFLOW;
	}

	return SUCCESS;
}

//销毁闪电树
void DestoryThunderTreeList(ThunderTreeList *L)
{
	ThunderTree *p = L->head->next;
	ThunderTree *q = p;
	while (p)
	{
		q = q->next;
		DestoryThunderNodeList(p->head);
		free(p);
		p = q;
	}
	free(L->head);
}

//插入闪电
Status InsertThundersList(Thunders *L)
{
	ThunderList *newList;
	if (NULL == (newList = (ThunderList *)malloc(sizeof(ThunderList))))
		return OVERFLOW;

	if (NULL == (newList->head = (ThunderTreeList *)malloc(sizeof(ThunderTreeList))))
		return OVERFLOW;

	InitThunderTreeList(newList->head);
	if (OVERFLOW == CreateThunderTreeList(newList->head, 5 + rand() % 5))
		return OVERFLOW;

	newList->next = L->head->next;
	L->head->next = newList;

	L->numOfThunder++;

	return SUCCESS;
}

//获取第index棵闪电
Status GetIndexThunders(Thunders *L, int index, ThunderTreeList *treeList)
{
	ThunderList *p = L->head;
	if (index < 1 || index > L->numOfThunder)
		return FAIL;

	for (int i = 0; i < index; ++i)
	{
		p = p->next;
	}

	treeList->head = p->head->head;
	treeList->numOfTree = p->head->numOfTree;
	treeList->flag = p->head->flag;
	treeList->numOfAllNodes = p->head->numOfAllNodes;
	treeList->visitTimes = p->head->visitTimes;

	return SUCCESS;
}

//删除第index棵闪电
Status DeleteThunder(Thunders *L, int index)
{
	ThunderList *p, *q = NULL;
	if (index < 1 || index > L->numOfThunder)
		return FAIL;

	p = L->head;
	for (int i = 0; i < index; ++i)
	{
		q = p;
		p = p->next;//p指向下一结点，q则作为p的前驱
	}

	q->next = p->next;
	DestoryThunderTreeList(p->head);
	free(p->head);
	L->numOfThunder--;

	return SUCCESS;
}