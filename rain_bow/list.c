/****************************************************************************************
*	File Name				:	list.c
*	CopyRight				:	LPF
*	ModuleName				:	list
*
*	CPU						:   Inter Core 7
*	RTOS					:
*
*	Create Data				:	2015/12/20
*	Author/Corportation		:	Li PeiFeng
*
*	Abstract Description	:	definite the function for list
*
*--------------------------------Revision History----------------------------------------
*	No	version		Data		Revised By			Item			Description
*	1							LPF									first coding
*
****************************************************************************************/

/****************************************************************************************
*	Include File Section
****************************************************************************************/
#include "list.h"

/****************************************************************************************
*	Function Define Section
****************************************************************************************/

/****************************************************************************************
*@Name............: Status InitList(List *L)
*@Description.....: 初始化空链表
*@Parameters......: L		:链表结构体
*@Return values...: SUCCESS :初始化链表成功
*                   OVERFLOW:链表头结点分配空间失败
*@PreCondition....：无
*@PostCondition...：在使用链表时需先使用此函数以初始化该链表
****************************************************************************************/
Status InitList(List *L)
{
	if (NULL == (L->headNode = (ptrList)malloc(sizeof(List))))
		return OVERFLOW;

	L->headNode->next = NULL;
	L->num = 0;

	return SUCCESS;
}

/****************************************************************************************
*@Name............: Status CreateData(ListNode *data, float windSpeed)
*@Description.....: 创建单个数据结点
*@Parameters......: data		:存储链表的结点，如雨滴的属性和涟漪
*					windSpeed	:风速
*@Return values...: SUCCESS :初始化链表成功
*                   OVERFLOW:链表头结点分配空间失败
*@PreCondition....：无
*@PostCondition...：可用于创建数据结点数组
*****************************************************************************************/
Status CreateData(ListNode *data, float windSpeed)
{
	if(NULL == (data->rainDrop = CreateRainDrop()))
		return OVERFLOW;

	if(NULL == (data->ripple = CreateRipple()))
		return OVERFLOW;

	if (OVERFLOW == SetRainDropAttribute(data->rainDrop, windSpeed))//设置雨滴属性
		return OVERFLOW;

	if (OVERFLOW == SetRipple(data->ripple, GetWidthOfRainDrop(data->rainDrop), GetLengthOfRainDrop(data->rainDrop)))//设置涟漪属性
		return OVERFLOW;

	data->next = NULL;
	return SUCCESS;
}

/****************************************************************************************
*@Name............: Status CreateDataArray(ListNode data[], int num, float windSpeed)
*@Description.....: 创建数据结点数组
*@Parameters......: data		:存储链表的结点数组，如雨滴的属性和涟漪
*					num			:数组的数目
*					windSpeed	:风速
*@Return values...: SUCCESS		:初始化链表成功
*                   OVERFLOW	:链表头结点分配空间失败
*@PreCondition....：无
*@PostCondition...：用于插入链表
****************************************************************************************/
Status CreateDataArray(ListNode data[], int num, float windSpeed)
{
	for (int i = 0; i < num; ++i)
	{
		if (OVERFLOW == CreateData(&data[i], windSpeed))
			return OVERFLOW;
	}

	return SUCCESS;
}

/****************************************************************************************
*@Name............: Status UpdateListNode(List *L, int index, double offset)
*@Description.....: 更新链表L的第index个结点
*@Parameters......: L		:链表结构体
*					index	:结点位序
*					offset	:偏移量
*@Return values...: SUCCESS :链表更新结点成功
*                   FAIL	:index参数有误
*@PreCondition....：无
*@PostCondition...：用于更新链表结点
****************************************************************************************/
Status UpdateListNode(List *L, int index, double offset)
{
	ptrList p = L->headNode;

	if (index < 1 || index > L->num)
		return FAIL;

	for (int i = 0; i < index; ++i)
	{
		p = p->next;
	}

	//更新坐标
	UpdateYCoordPoint(p->rainDrop, offset);
	UpdateXCoordPoint(p->rainDrop, offset);
	
	return SUCCESS;
}

/****************************************************************************************
*@Name............: Status InseartList(List *L, ListNode data)
*@Description.....: 为链表L插入新节点
*@Parameters......: L		:链表结构体
*					data	:存储数据的结点
*@Return values...: SUCCESS :链表插入新的结点成功
*                   OVERFLOW:链表结点分配空间失败
*@PreCondition....：无
*@PostCondition...：可以使用此插入结点函数来创建大链表
****************************************************************************************/
Status InseartList(List *L, ListNode data)
{
	ptrList newNode;
	if (NULL == (newNode = (ptrList)malloc(sizeof(ListNode))))
		return OVERFLOW;

	/*为新节点赋值*/
	newNode->rainDrop = data.rainDrop;
	newNode->ripple = data.ripple;

	/*头插法插入链表*/
	newNode->next = L->headNode->next;
	L->headNode->next = newNode;
	L->num++;

	return SUCCESS;
}

/****************************************************************************************
*@Name............: Status CreateList(List *L, ListNode data[], int num)
*@Description.....: 创建链表结点，即插入多个结点
*@Parameters......: L		:链表结构体
*					data	:存储数据的结点数组
*					num		:创建的结点数目
*@Return values...: SUCCESS :链表插入新的结点成功
*                   OVERFLOW:链表结点分配空间失败
*					FAIL    :创建的结点数目有误
*@PreCondition....：无
*@PostCondition...：可以使用此插入结点函数来创建大链表
****************************************************************************************/
Status CreateList(List *L, ListNode data[], int num)
{
	if (num <= 0)
		return FAIL;

	for (int i = 0; i < num; ++i)
	{ 
		if(OVERFLOW == InseartList(L, data[i]))//循环依次插入新的结点
			return OVERFLOW;
	}

	return SUCCESS;
}

/****************************************************************************************
*@Name............: Status IsListEmpty(List L)
*@Description.....: 判断链表L是否为空
*@Parameters......: L		:链表结构体
*@Return values...: TRUE	:表示链表为空
*					FALSE	:表示链表不为空
*@PreCondition....：链表L应经过初始化
*@PostCondition...：无
****************************************************************************************/
Status IsListEmpty(List L)
{
	if (0 == L.num)//根据链表中非头结点数目判断链表是否为空
		return TRUE;
	else
		return FALSE;
}

/****************************************************************************************
*@Name............: int GetListNum(List L)
*@Description.....: 获取链表中
*@Parameters......: L		:链表结构体
*@Return values...: num		:链表中非头结点的数目
*@PreCondition....：链表应先初始化
*@PostCondition...：无
****************************************************************************************/
int GetListNum(List L)
{
	return L.num;
}

/****************************************************************************************
*@Name............: Status GetListIndexNode(List *L, int index, ListNode *data)
*@Description.....: 获取链表L中的第index个结点
*@Parameters......: L		:链表结构体
*					index	:结点位序
*@Return values...: FAIL	:获取失败，位序有误
*					SUCCESS	:获取成功
*@PreCondition....：index应保证正确
*@PostCondition...：可用于辅助置空、销毁链表
*****************************************************************************************/
Status GetListIndexNode(List *L, int index, ListNode *data)
{
	ptrList p = L->headNode;
	if (index < 1 || index > L->num)
		return FAIL;

	for (int i = 0; i < index; ++i)//追踪第index个结点
	{
		p = p->next;
	}

	/*
	**获取结点数据
	*/
	data->rainDrop = p->rainDrop;
	data->ripple = p->ripple;
	data->next = p->next;

	return SUCCESS;
}

/****************************************************************************************
*@Name............: Status DeleteList(List *L, int index)
*@Description.....: 删除链表L中的第index个结点
*@Parameters......: L		:链表结构体
*					index	:结点位序
*@Return values...: FAIL	:删除失败，位序有误
*					SUCCESS	:删除成功
*@PreCondition....：index应保证正确
*@PostCondition...：可用于辅助置空、销毁链表
*****************************************************************************************/
Status DeleteList(List *L, int index)
{
	ptrList p, q = NULL;
	if (index < 1 || index > L->num)//如果index小于1或大于链表的非头结点数目，则出错
		return FAIL;

	p = L->headNode;//p首先指向链表头结点
	for (int i = 0; i < index; ++i)
	{
		q = p;
		p = p->next;//p指向下一结点，q则作为p的前驱
	}

	q->next = p->next;//断开p结点

	free(p->rainDrop);
	free(p->ripple);
	free(p);
	L->num--;

	return SUCCESS;
}

/****************************************************************************************
*@Name............: void ClearList(List *L)
*@Description.....: 置空链表
*@Parameters......: L		:链表结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
void ClearList(List *L)
{
	for (int i = 0; i < L->num; ++i)
	{
		DeleteList(L, 1);
	}
	L->num = 0;
}

/****************************************************************************************
*@Name............: void DestoryList(List *L)
*@Description.....: 销毁链表
*@Parameters......: L		:链表结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
void DestoryList(List *L)
{
	ptrList p = NULL;

	/*当链表头结点不为空时，释放头结点，并在释放之后指向下一结点*/
	while (L->headNode)
	{
		p = L->headNode->next;
		free(L->headNode);
		L->headNode = p;
	}

	L->num = 0;
}