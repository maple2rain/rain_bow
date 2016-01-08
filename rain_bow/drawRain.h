/****************************************************************************************
*	File Name				:	drawRain.h
*	CopyRight				:	LPF
*	ModuleName				:	drawRain
*
*	CPU						:   Inter Core 7
*	RTOS					:
*
*	Create Data				:	2015/12/20
*	Author/Corportation		:	Li PeiFeng
*
*	Abstract Description	:	Declared the struct and function for drawRain
*
*--------------------------------Revision History----------------------------------------
*	No	version		Data		Revised By			Item			Description
*	1							LPF									first coding
*
****************************************************************************************/

/****************************************************************************************
*	Multi-Include-Prevent Section
****************************************************************************************/
#ifndef DRAWRAIN_H_INCLUDED
#define DRAWRAIN_H_INCLUDED

/*****************************************************************************************
*	Macro Define Section
*****************************************************************************************/
#define PI 3.14159265

/****************************************************************************************
*	Include File Section
****************************************************************************************/
#include "list.h"
#include <stdlib.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#include <math.h>
#include "displayOthers.h"

/****************************************************************************************
*	Macro Define Section
****************************************************************************************/
#define MAX_NUM_OF_NODE 100	//��ʼʱ��������
#define SMOOTH_DEGREE 32	//�����⻬�̶�

#define WINDOW_WIDTH 1590	//���ڿ��
#define WINDOW_HEIGHT 830	//���ڸ߶�


/****************************************************************************************
*	Prototype Declare Section
****************************************************************************************/
/****************************************************************************************
*@Name............: void initRainScreen(void)
*@Description.....: ��ʼ�����곡��
*@Parameters......: void
*@Return values...: void
*@PreCondition....�����ڻ�ͼ֮ǰ�����ã��Ӷ�ʵ�ֹ���
*@PostCondition...����
*****************************************************************************************/
void InitRainScreen(void);

//��ʼ��ȫ������
void InitWorld(void);

//��ʼ��������Ļ
void InitControlScreen(void);

/****************************************************************************************
*@Name............: void ResizeDisplayScreen(int width, int height)
*@Description.....: ���ƴ��ڱ仯�¼�
*@Parameters......: width	:���ڿ��
*					height	:���ڸ߶�
*@Return values...: void
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
void ResizeDisplayScreen(int width, int height);

//����ȫ�����細�ڸı��¼�
void ResizeWorld(int width, int height);

//���������Ļ���ڸı��¼�
void ResizeControlScreen(int width, int height);
/****************************************************************************************
*@Name............: void DisplayRainScreen(void)
*@Description.....: ���곡����ʾ����
*@Parameters......: void
*@Return values...: void
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
void DisplayRainScreen(void);

//���ƿ�����Ļ
void DisplayControlScreen(void);

//����ȫ������
void DisplayWorld(void);

/****************************************************************************************
*@Name............: void idle(void)
*@Description.....: ���к���
*@Parameters......: void
*@Return values...: void
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
void Idle(void);

//���ݰ뾶radius����Բ
void DrawCircle(double radius);

/****************************************************************************************
*@Name............: void keyBoard(unsigned char key, int x, int y)
*@Description.....: ����������
*@Parameters......: key		:���µġ�����
*@Return values...: void
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
void KeyBoard(unsigned char key, int x, int y);
#endif