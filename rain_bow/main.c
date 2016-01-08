/***************************************************************************************
*	File Name				:	main.c
*	CopyRight				:	LPF
*	ModuleName				:	main control
*
*	CPU						:   Inter Core 7
*	RTOS					:
*
*	Create Data				:	2015/12/20
*	Author/Corportation		:	Li PeiFeng
*
*	Abstract Description	:	for the main control of OpenGL
*
*--------------------------------Revision History--------------------------------------
*	No	version		Data		Revised By			Item			Description
*	1.0							LPF									first coding
*
***************************************************************************************/

/****************************************************************************************
*	Include File Section
****************************************************************************************/
#include "drawRain.h"

int mainWindow;
int controlWindow;
int rainWindow;
GLuint GAP = (WINDOW_WIDTH * WINDOW_HEIGHT / 100000) + 12; //����֮��ļ��

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	mainWindow = glutCreateWindow("����ҹ����ɫ��");
	InitWorld();
	glutReshapeFunc(ResizeWorld);
	glutDisplayFunc(DisplayWorld);

	controlWindow = glutCreateSubWindow(mainWindow, GAP, GAP, WINDOW_WIDTH / 8, WINDOW_HEIGHT - GAP * 2);//����������Ļ����
	InitControlScreen();
	glutReshapeFunc(ResizeControlScreen);
	glutDisplayFunc(DisplayControlScreen);

	rainWindow = glutCreateSubWindow(mainWindow, GAP * 2 + 200, GAP, WINDOW_WIDTH - GAP * 4 - WINDOW_WIDTH / 8, WINDOW_HEIGHT - GAP * 2);//�������곡������
	InitRainScreen();
	glutReshapeFunc(ResizeDisplayScreen);
	glutDisplayFunc(DisplayRainScreen);
	glutKeyboardFunc(KeyBoard);
	glutSpecialFunc(SpecialKeyBoard);

	glutIdleFunc(Idle);
	glutMainLoop();
	
	return EXIT_SUCCESS;
}