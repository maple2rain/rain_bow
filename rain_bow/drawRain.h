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

/****************************************************************************************
*	Macro Define Section
****************************************************************************************/
#define MAX_NUM_OF_NODE 100
#define SMOOTH_DEGREE 100

/****************************************************************************************
*	Prototype Declare Section
****************************************************************************************/
/****************************************************************************************
*@Name............: void initRainScreen(void)
*@Description.....: ��OpenGL���г�ʼ����ʹ�ܸ����ܼ����ù�Դ��
*@Parameters......: void
*@Return values...: void
*@PreCondition....�����ڻ�ͼ֮ǰ�����ã��Ӷ�ʵ�ֹ���
*@PostCondition...����
*****************************************************************************************/
void InitRainScreen(void);
void InitWorld(void);
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
void ResizeWorld(int width, int height);
void ResizeControlScreen(int width, int height);
/****************************************************************************************
*@Name............: void displayRainScreen(void)
*@Description.....: ���곡����ʾ����
*@Parameters......: void
*@Return values...: void
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
void DisplayControlScreen(void);
void DisplayRainScreen(void);
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