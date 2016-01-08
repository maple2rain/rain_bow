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
GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_10; //字体

/****************************************************************************************
*	Function Define Section
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
*@Description.....: 可变参数形式绘制字符串
*@Parameters......: x		:X坐标
*					Y		:Y坐标
*					format	:待绘制的字符串
*@Return values...: void
*@PreCondition....：需先设置字体风格
*@PostCondition...：无
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