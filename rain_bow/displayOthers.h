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
*@Description.....: ���������С
*@Parameters......: name	:������
*					size	:�����С�� Ϊ12��18��24
*@Return values...: void
*@PreCondition....����
*@PostCondition...����ʾ�ַ���ǰ�����������С
*****************************************************************************************/
void setFont(char* name, int size);

/****************************************************************************************
*@Name............: void drawstr(GLuint x, GLuint y, char* format, ...)
*@Description.....: �ɱ������ʽ�����ַ���
*@Parameters......: x		:X����
*					Y		:Y����
*					format	:�����Ƶ��ַ���
*@Return values...: void
*@PreCondition....����������������
*@PostCondition...����
*****************************************************************************************/
void drawstr(GLuint x, GLuint y, char* format, ...);
#endif
