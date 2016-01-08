/****************************************************************************************
*	File Name				:	displayOthers.h
*	CopyRight				:	LPF
*	ModuleName				:	displayOthers
*
*	CPU						:   Inter Core 7
*	RTOS					:
*
*	Create Data				:	2015/12/25
*	Author/Corportation		:	Li PeiFeng
*
*	Abstract Description	:	Declared the struct and function for displayOthers
*
*--------------------------------Revision History----------------------------------------
*	No	version		Data		Revised By			Item			Description
*	1							LPF									first coding
*
****************************************************************************************/

/****************************************************************************************
*	Multi-Include-Prevent Section
****************************************************************************************/
#ifndef DISPLAYOTHERS_H_INCLUDED
#define DISPLAYOYHERS_H_INCLUDED

#include <stdarg.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#include <stdio.h>

/****************************************************************************************
*	Prototype Declare Section
****************************************************************************************/
/****************************************************************************************
*@Name............: void setFont(char* name, int size)
*@Description.....: 设置字体大小
*@Parameters......: name	:字体风格
*					size	:字体大小， 为12、18、24
*@Return values...: void
*@PreCondition....：无
*@PostCondition...：显示字符串前需设置字体大小
*****************************************************************************************/
void setFont(char* name, int size);

/****************************************************************************************
*@Name............: void drawstr(GLuint x, GLuint y, char* format, ...)
*@Description.....: 可变参数形式绘制字符串
*@Parameters......: x		:X坐标
*					Y		:Y坐标
*					format	:待绘制的字符串
*@Return values...: void
*@PreCondition....：需先设置字体风格
*@PostCondition...：无
*****************************************************************************************/
void drawstr(GLuint x, GLuint y, char* format, ...);
#endif
