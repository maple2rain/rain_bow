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
//��ʼ������������
Status InitThunderList(Thunders *L)
{
	if (NULL == (L->head = (ThunderList *)malloc(sizeof(ThunderList))))
		return OVERFLOW;

	L->head->next = NULL;
	L->head->head = NULL;
	L->numOfThunder = 0;

	return SUCCESS;
}

//��ʼ����������������
Status InitThunderNodeList(ThunderNodeList *L)
{
	if (NULL == (L->head = (ThunderNode *)malloc(sizeof(ThunderNode))))
		return OVERFLOW;

	L->head->next = NULL;
	L->numOfNode = 0;

	return SUCCESS;
}

//��ʼ�������֧����
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

//����������
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

//��������������
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

//��ȡ��index��������ֵ
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

//��������������
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

//��ȡ��index�������������Ϣ
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

//������������֧���
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

//�����ʵĴ�������
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

//�����ʵĴ�������
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

//����flag��ʾΪ1����ʾ������չʾ���磬����������
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

//������������֧����
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

//����������
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

//��������
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

//��ȡ��index������
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

//ɾ����index������
Status DeleteThunder(Thunders *L, int index)
{
	ThunderList *p, *q = NULL;
	if (index < 1 || index > L->numOfThunder)
		return FAIL;

	p = L->head;
	for (int i = 0; i < index; ++i)
	{
		q = p;
		p = p->next;//pָ����һ��㣬q����Ϊp��ǰ��
	}

	q->next = p->next;
	DestoryThunderTreeList(p->head);
	free(p->head);
	L->numOfThunder--;

	return SUCCESS;
}