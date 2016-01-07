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
#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

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

/*链表结点结构体*/
typedef struct listNode {
	RainDrop *rainDrop;		//雨滴结构体指针
	Ripple *ripple;			//涟漪结构体指针
	struct listNode *next;	//指向下一节点的指针
}ListNode, *ptrList;

/*
**链表存储结构体
*/
typedef struct list {
	int num;			//链表非头结点数目
	ptrList headNode;	//链表头结点
}List;

/****************************************************************************************
*	Prototype Declare Section
****************************************************************************************/
/****************************************************************************************
*@Name............: Status InitList(List *L)
*@Description.....: 初始化空链表
*@Parameters......: L		:链表结构体
*@Return values...: SUCCESS :初始化链表成功
*                   OVERFLOW:链表头结点分配空间失败
*@PreCondition....：无
*@PostCondition...：在使用链表时需先使用此函数以初始化该链表
*****************************************************************************************/
Status InitList(List *L);

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
Status GetListIndexNode(List *L, int index, ListNode *data);

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
Status CreateData(ListNode *data, float windSpeed);

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
*****************************************************************************************/
Status CreateDataArray(ListNode data[], int num, float windSpeed);

/****************************************************************************************
*@Name............: Status UpdateListNode(List *L, int index, float offset)
*@Description.....: 更新链表L的第index个结点
*@Parameters......: L		:链表结构体
*					index	:结点位序
*					offset	:偏移量
*@Return values...: SUCCESS :链表更新结点成功
*                   FAIL	:index参数有误
*@PreCondition....：无
*@PostCondition...：用于更新链表结点
****************************************************************************************/
Status UpdateListNode(List *L, int index, double offset);

/****************************************************************************************
*@Name............: Status InseartList(List *L, ListNode data)
*@Description.....: 为链表L插入新节点
*@Parameters......: L		:链表结构体
*					data	:存储数据的结点
*@Return values...: SUCCESS :链表插入新的结点成功
*                   OVERFLOW:链表结点分配空间失败
*@PreCondition....：无
*@PostCondition...：可以使用此插入结点函数来创建大链表
*****************************************************************************************/
Status InseartList(List *L, ListNode data);

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
*****************************************************************************************/
Status CreateList(List *L, ListNode data[], int num);

/****************************************************************************************
*@Name............: int GetListNum(List L)
*@Description.....: 获取链表中
*@Parameters......: L		:链表结构体
*@Return values...: num		:链表中非头结点的数目
*@PreCondition....：链表应先初始化
*@PostCondition...：无
*****************************************************************************************/
int GetListNum(List L);

/****************************************************************************************
*@Name............: Status IsListEmpty(List L)
*@Description.....: 判断链表L是否为空
*@Parameters......: L		:链表结构体
*@Return values...: TRUE	:表示链表为空
*					FALSE	:表示链表不为空
*@PreCondition....：链表L应经过初始化
*@PostCondition...：无
*****************************************************************************************/
Status IsListEmpty(List L);

/****************************************************************************************
*@Name............: Status DeleteList(List *L, int index)
*@Description.....: 删除链表L中的第index个结点
*@Parameters......: L		:链表结构体
*					index	:结点位序
*@Return values...: FAIL	:删除失败，位序有误
*					SUCCESS	:删除成功
*@PreCondition....：index应保证正确
*@PostCondition...：可用于辅助销毁链表
*****************************************************************************************/
Status DeleteList(List *L, int index);

/****************************************************************************************
*@Name............: void ClearList(List *L)
*@Description.....: 置空链表
*@Parameters......: L		:链表结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
void ClearList(List *L);

/****************************************************************************************
*@Name............: void DestoryList(List *L)
*@Description.....: 销毁链表
*@Parameters......: L		:链表结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
void DestoryList(List *L);

#endif