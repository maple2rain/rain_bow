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
*@Description.....: 对OpenGL进行初始化，使能各功能及放置光源等
*@Parameters......: void
*@Return values...: void
*@PreCondition....：需在绘图之前被调用，从而实现功能
*@PostCondition...：无
*****************************************************************************************/
void InitRainScreen(void);
void InitWorld(void);
void InitControlScreen(void);
/****************************************************************************************
*@Name............: void ResizeDisplayScreen(int width, int height)
*@Description.....: 控制窗口变化事件
*@Parameters......: width	:窗口宽度
*					height	:窗口高度
*@Return values...: void
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
void ResizeDisplayScreen(int width, int height);
void ResizeWorld(int width, int height);
void ResizeControlScreen(int width, int height);
/****************************************************************************************
*@Name............: void displayRainScreen(void)
*@Description.....: 落雨场景显示函数
*@Parameters......: void
*@Return values...: void
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
void DisplayControlScreen(void);
void DisplayRainScreen(void);
void DisplayWorld(void);
/****************************************************************************************
*@Name............: void idle(void)
*@Description.....: 空闲函数
*@Parameters......: void
*@Return values...: void
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
void Idle(void);

//根据半径radius画椭圆
void DrawCircle(double radius);

/****************************************************************************************
*@Name............: void keyBoard(unsigned char key, int x, int y)
*@Description.....: 按键处理函数
*@Parameters......: key		:按下的‘键’
*@Return values...: void
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
void KeyBoard(unsigned char key, int x, int y);
#endif