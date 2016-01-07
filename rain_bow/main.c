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
int worldWindow;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	mainWindow = glutCreateWindow("≥ÿÃ¡“πΩµ≤ …´”Í");
	InitWorld();
	glutReshapeFunc(ResizeWorld);
	glutDisplayFunc(DisplayWorld);
	glutKeyboardFunc(KeyBoard);

	worldWindow = glutCreateSubWindow(mainWindow, 200, 0, 1720, 1080);
	InitRainScreen();
	glutReshapeFunc(ResizeDisplayScreen);
	glutDisplayFunc(DisplayRainScreen);
	glutKeyboardFunc(KeyBoard);

	controlWindow = glutCreateSubWindow(mainWindow, 0, 0, 200, 1080);
	InitControlScreen();
	glutReshapeFunc(ResizeControlScreen);
	glutDisplayFunc(DisplayControlScreen);
	glutIdleFunc(Idle);

	glutMainLoop();
	
	return EXIT_SUCCESS;
}