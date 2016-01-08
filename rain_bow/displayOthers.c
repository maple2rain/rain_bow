/****************************************************************************************
*	File Name				:	displayOthers.c
*	CopyRight				:	LPF
*	ModuleName				:	displayOthers
*
*	CPU						:   Inter Core 7
*	RTOS					:
*
*	Create Data				:	2015/12/20
*	Author/Corportation		:	Li PeiFeng
*
*	Abstract Description	:	definite the function for displaying others
*
*--------------------------------Revision History----------------------------------------
*	No	version		Data		Revised By			Item			Description
*	1							LPF									first coding
*
***************************************************************************************/

/****************************************************************************************
*	Include File Section
****************************************************************************************/
#include "displayOthers.h"
#pragma warning(disable: 4996)

/*****************************************************************************************
*	Global Variable Declare Section
*****************************************************************************************/
GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_10; //����

/****************************************************************************************
*	Function Define Section
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
void setFont(char* name, int size)
{
	font_style = GLUT_BITMAP_HELVETICA_10;
	if (strcmp(name, "helvetica") == 0) {
		if (size == 12)
			font_style = GLUT_BITMAP_HELVETICA_12;
		else if (size == 18)
			font_style = GLUT_BITMAP_HELVETICA_18;
	}
	else if (strcmp(name, "times roman") == 0) {
		font_style = GLUT_BITMAP_TIMES_ROMAN_10;
		if (size == 24)
			font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	}
	else if (strcmp(name, "8x13") == 0) {
		font_style = GLUT_BITMAP_8_BY_13;
	}
	else if (strcmp(name, "9x15") == 0) {
		font_style = GLUT_BITMAP_9_BY_15;
	}
}

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
void drawstr(GLuint x, GLuint y, char* format, ...)
{
	va_list args;
	char buffer[255], *s;

	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	glRasterPos2i(x, y);
	for (s = buffer; *s; s++)
		glutBitmapCharacter(font_style, *s);
}