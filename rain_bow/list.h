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

/*������ṹ��*/
typedef struct listNode {
	RainDrop *rainDrop;		//��νṹ��ָ��
	Ripple *ripple;			//�����ṹ��ָ��
	struct listNode *next;	//ָ����һ�ڵ��ָ��
}ListNode, *ptrList;

/*
**����洢�ṹ��
*/
typedef struct list {
	int num;			//�����ͷ�����Ŀ
	ptrList headNode;	//����ͷ���
}List;

/****************************************************************************************
*	Prototype Declare Section
****************************************************************************************/
/****************************************************************************************
*@Name............: Status InitList(List *L)
*@Description.....: ��ʼ��������
*@Parameters......: L		:����ṹ��
*@Return values...: SUCCESS :��ʼ������ɹ�
*                   OVERFLOW:����ͷ������ռ�ʧ��
*@PreCondition....����
*@PostCondition...����ʹ������ʱ����ʹ�ô˺����Գ�ʼ��������
*****************************************************************************************/
Status InitList(List *L);

/****************************************************************************************
*@Name............: Status GetListIndexNode(List *L, int index, ListNode *data)
*@Description.....: ��ȡ����L�еĵ�index�����
*@Parameters......: L		:����ṹ��
*					index	:���λ��
*@Return values...: FAIL	:��ȡʧ�ܣ�λ������
*					SUCCESS	:��ȡ�ɹ�
*@PreCondition....��indexӦ��֤��ȷ
*@PostCondition...�������ڸ����ÿա���������
*****************************************************************************************/
Status GetListIndexNode(List *L, int index, ListNode *data);

/****************************************************************************************
*@Name............: Status CreateData(ListNode *data, float windSpeed)
*@Description.....: �����������ݽ��
*@Parameters......: data		:�洢����Ľ�㣬����ε����Ժ�����
*					windSpeed	:����
*@Return values...: SUCCESS :��ʼ������ɹ�
*                   OVERFLOW:����ͷ������ռ�ʧ��
*@PreCondition....����
*@PostCondition...�������ڴ������ݽ������
*****************************************************************************************/
Status CreateData(ListNode *data, float windSpeed);

/****************************************************************************************
*@Name............: Status CreateDataArray(ListNode data[], int num, float windSpeed)
*@Description.....: �������ݽ������
*@Parameters......: data		:�洢����Ľ�����飬����ε����Ժ�����
*					num			:�������Ŀ
*					windSpeed	:����
*@Return values...: SUCCESS		:��ʼ������ɹ�
*                   OVERFLOW	:����ͷ������ռ�ʧ��
*@PreCondition....����
*@PostCondition...�����ڲ�������
*****************************************************************************************/
Status CreateDataArray(ListNode data[], int num, float windSpeed);

/****************************************************************************************
*@Name............: Status UpdateListNode(List *L, int index, float offset)
*@Description.....: ��������L�ĵ�index�����
*@Parameters......: L		:����ṹ��
*					index	:���λ��
*					offset	:ƫ����
*@Return values...: SUCCESS :������½��ɹ�
*                   FAIL	:index��������
*@PreCondition....����
*@PostCondition...�����ڸ���������
****************************************************************************************/
Status UpdateListNode(List *L, int index, double offset);

/****************************************************************************************
*@Name............: Status InseartList(List *L, ListNode data)
*@Description.....: Ϊ����L�����½ڵ�
*@Parameters......: L		:����ṹ��
*					data	:�洢���ݵĽ��
*@Return values...: SUCCESS :��������µĽ��ɹ�
*                   OVERFLOW:���������ռ�ʧ��
*@PreCondition....����
*@PostCondition...������ʹ�ô˲����㺯��������������
*****************************************************************************************/
Status InseartList(List *L, ListNode data);

/****************************************************************************************
*@Name............: Status CreateList(List *L, ListNode data[], int num)
*@Description.....: ���������㣬�����������
*@Parameters......: L		:����ṹ��
*					data	:�洢���ݵĽ������
*					num		:�����Ľ����Ŀ
*@Return values...: SUCCESS :��������µĽ��ɹ�
*                   OVERFLOW:���������ռ�ʧ��
*					FAIL    :�����Ľ����Ŀ����
*@PreCondition....����
*@PostCondition...������ʹ�ô˲����㺯��������������
*****************************************************************************************/
Status CreateList(List *L, ListNode data[], int num);

/****************************************************************************************
*@Name............: int GetListNum(List L)
*@Description.....: ��ȡ������
*@Parameters......: L		:����ṹ��
*@Return values...: num		:�����з�ͷ������Ŀ
*@PreCondition....������Ӧ�ȳ�ʼ��
*@PostCondition...����
*****************************************************************************************/
int GetListNum(List L);

/****************************************************************************************
*@Name............: Status IsListEmpty(List L)
*@Description.....: �ж�����L�Ƿ�Ϊ��
*@Parameters......: L		:����ṹ��
*@Return values...: TRUE	:��ʾ����Ϊ��
*					FALSE	:��ʾ����Ϊ��
*@PreCondition....������LӦ������ʼ��
*@PostCondition...����
*****************************************************************************************/
Status IsListEmpty(List L);

/****************************************************************************************
*@Name............: Status DeleteList(List *L, int index)
*@Description.....: ɾ������L�еĵ�index�����
*@Parameters......: L		:����ṹ��
*					index	:���λ��
*@Return values...: FAIL	:ɾ��ʧ�ܣ�λ������
*					SUCCESS	:ɾ���ɹ�
*@PreCondition....��indexӦ��֤��ȷ
*@PostCondition...�������ڸ�����������
*****************************************************************************************/
Status DeleteList(List *L, int index);

/****************************************************************************************
*@Name............: void ClearList(List *L)
*@Description.....: �ÿ�����
*@Parameters......: L		:����ṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
void ClearList(List *L);

/****************************************************************************************
*@Name............: void DestoryList(List *L)
*@Description.....: ��������
*@Parameters......: L		:����ṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
void DestoryList(List *L);

#endif