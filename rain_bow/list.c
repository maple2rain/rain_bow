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
*@Description.....: ��ʼ��������
*@Parameters......: L		:����ṹ��
*@Return values...: SUCCESS :��ʼ������ɹ�
*                   OVERFLOW:����ͷ������ռ�ʧ��
*@PreCondition....����
*@PostCondition...����ʹ������ʱ����ʹ�ô˺����Գ�ʼ��������
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
*@Description.....: �����������ݽ��
*@Parameters......: data		:�洢����Ľ�㣬����ε����Ժ�����
*					windSpeed	:����
*@Return values...: SUCCESS :��ʼ������ɹ�
*                   OVERFLOW:����ͷ������ռ�ʧ��
*@PreCondition....����
*@PostCondition...�������ڴ������ݽ������
*****************************************************************************************/
Status CreateData(ListNode *data, float windSpeed)
{
	if(NULL == (data->rainDrop = CreateRainDrop()))
		return OVERFLOW;

	if(NULL == (data->ripple = CreateRipple()))
		return OVERFLOW;

	if (OVERFLOW == SetRainDropAttribute(data->rainDrop, windSpeed))//�����������
		return OVERFLOW;

	if (OVERFLOW == SetRipple(data->ripple, GetWidthOfRainDrop(data->rainDrop), GetLengthOfRainDrop(data->rainDrop)))//������������
		return OVERFLOW;

	data->next = NULL;
	return SUCCESS;
}

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
*@Description.....: ��������L�ĵ�index�����
*@Parameters......: L		:����ṹ��
*					index	:���λ��
*					offset	:ƫ����
*@Return values...: SUCCESS :������½��ɹ�
*                   FAIL	:index��������
*@PreCondition....����
*@PostCondition...�����ڸ���������
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

	//��������
	UpdateYCoordPoint(p->rainDrop, offset);
	UpdateXCoordPoint(p->rainDrop, offset);
	
	return SUCCESS;
}

/****************************************************************************************
*@Name............: Status InseartList(List *L, ListNode data)
*@Description.....: Ϊ����L�����½ڵ�
*@Parameters......: L		:����ṹ��
*					data	:�洢���ݵĽ��
*@Return values...: SUCCESS :��������µĽ��ɹ�
*                   OVERFLOW:���������ռ�ʧ��
*@PreCondition....����
*@PostCondition...������ʹ�ô˲����㺯��������������
****************************************************************************************/
Status InseartList(List *L, ListNode data)
{
	ptrList newNode;
	if (NULL == (newNode = (ptrList)malloc(sizeof(ListNode))))
		return OVERFLOW;

	/*Ϊ�½ڵ㸳ֵ*/
	newNode->rainDrop = data.rainDrop;
	newNode->ripple = data.ripple;

	/*ͷ�巨��������*/
	newNode->next = L->headNode->next;
	L->headNode->next = newNode;
	L->num++;

	return SUCCESS;
}

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
****************************************************************************************/
Status CreateList(List *L, ListNode data[], int num)
{
	if (num <= 0)
		return FAIL;

	for (int i = 0; i < num; ++i)
	{ 
		if(OVERFLOW == InseartList(L, data[i]))//ѭ�����β����µĽ��
			return OVERFLOW;
	}

	return SUCCESS;
}

/****************************************************************************************
*@Name............: Status IsListEmpty(List L)
*@Description.....: �ж�����L�Ƿ�Ϊ��
*@Parameters......: L		:����ṹ��
*@Return values...: TRUE	:��ʾ����Ϊ��
*					FALSE	:��ʾ����Ϊ��
*@PreCondition....������LӦ������ʼ��
*@PostCondition...����
****************************************************************************************/
Status IsListEmpty(List L)
{
	if (0 == L.num)//���������з�ͷ�����Ŀ�ж������Ƿ�Ϊ��
		return TRUE;
	else
		return FALSE;
}

/****************************************************************************************
*@Name............: int GetListNum(List L)
*@Description.....: ��ȡ������
*@Parameters......: L		:����ṹ��
*@Return values...: num		:�����з�ͷ������Ŀ
*@PreCondition....������Ӧ�ȳ�ʼ��
*@PostCondition...����
****************************************************************************************/
int GetListNum(List L)
{
	return L.num;
}

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
Status GetListIndexNode(List *L, int index, ListNode *data)
{
	ptrList p = L->headNode;
	if (index < 1 || index > L->num)
		return FAIL;

	for (int i = 0; i < index; ++i)//׷�ٵ�index�����
	{
		p = p->next;
	}

	/*
	**��ȡ�������
	*/
	data->rainDrop = p->rainDrop;
	data->ripple = p->ripple;
	data->next = p->next;

	return SUCCESS;
}

/****************************************************************************************
*@Name............: Status DeleteList(List *L, int index)
*@Description.....: ɾ������L�еĵ�index�����
*@Parameters......: L		:����ṹ��
*					index	:���λ��
*@Return values...: FAIL	:ɾ��ʧ�ܣ�λ������
*					SUCCESS	:ɾ���ɹ�
*@PreCondition....��indexӦ��֤��ȷ
*@PostCondition...�������ڸ����ÿա���������
*****************************************************************************************/
Status DeleteList(List *L, int index)
{
	ptrList p, q = NULL;
	if (index < 1 || index > L->num)//���indexС��1���������ķ�ͷ�����Ŀ�������
		return FAIL;

	p = L->headNode;//p����ָ������ͷ���
	for (int i = 0; i < index; ++i)
	{
		q = p;
		p = p->next;//pָ����һ��㣬q����Ϊp��ǰ��
	}

	q->next = p->next;//�Ͽ�p���

	free(p->rainDrop);
	free(p->ripple);
	free(p);
	L->num--;

	return SUCCESS;
}

/****************************************************************************************
*@Name............: void ClearList(List *L)
*@Description.....: �ÿ�����
*@Parameters......: L		:����ṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
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
*@Description.....: ��������
*@Parameters......: L		:����ṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
void DestoryList(List *L)
{
	ptrList p = NULL;

	/*������ͷ��㲻Ϊ��ʱ���ͷ�ͷ��㣬�����ͷ�֮��ָ����һ���*/
	while (L->headNode)
	{
		p = L->headNode->next;
		free(L->headNode);
		L->headNode = p;
	}

	L->num = 0;
}