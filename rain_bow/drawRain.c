/****************************************************************************************
*	File Name				:	drawRain.c
*	CopyRight				:	LPF
*	ModuleName				:	drawRain
*
*	CPU						:   Inter Core 7
*	RTOS					:
*
*	Create Data				:	2015/12/20
*	Author/Corportation		:	Li PeiFeng
*
*	Abstract Description	:	definite the function for drawRaining
*
*--------------------------------Revision History----------------------------------------
*	No	version		Data		Revised By			Item			Description
*	1							LPF									first coding
*
***************************************************************************************/

/****************************************************************************************
*	Include File Section
****************************************************************************************/
#include "drawRain.h"
#include <windows.h>
#pragma warning(disable: 4996)
/*****************************************************************************************
*	Global Variable Declare Section
*****************************************************************************************/
/*光照属性*/
const GLfloat light_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 0.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 0.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 0.0f, 100.0f, 0.0f };
const GLfloat local_view[] = { GL_TRUE };

/*月亮属性*/
GLfloat shininess[] = { 100.0 };
const GLfloat moonEmission[] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat moonAmbient[] = { 0.9, 0.9, 0.9, 1.0 };
const GLfloat moonDiffuse[] = { 0.5, 0.5, 0.5, 1.0 };
const GLfloat moonSpecular[] = { 0.5, 0.5, 0.5, 1.0 };
const GLfloat moonPosition [] = { -300.0, 300.0, -100.0, 0.0 };

static float windSpeed = 1.0;			//风速
static double increaseCoord = 0.5;		//坐标增量
static double increaseRadius = 0.05;	//半径增量
static int density = 1;					//雨滴密度,至少为1
static List L;

extern int mainWindow;
extern int controlWindow;
extern int rainWindow;
extern GLuint GAP;

GLuint subWidth, subHeight;
GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_10;
/****************************************************************************************
*	Function Define Section
****************************************************************************************/
/****************************************************************************************
*@Name............: void InitRainScreen(void)
*@Description.....: 初始化绘雨场景
*@Parameters......: void
*@Return values...: void
*@PreCondition....：需在绘图之前被调用，从而实现功能
*@PostCondition...：无
*****************************************************************************************/
void InitRainScreen(void)
{
	ListNode data[MAX_NUM_OF_NODE];
	srand((unsigned)time(NULL));

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	/*设置混合抗锯齿*/
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(1.5);

	/*设置光照属性*/
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, moonAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, moonDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, moonDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, moonPosition);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	InitList(&L);
	CreateDataArray(data, MAX_NUM_OF_NODE, windSpeed);
	CreateList(&L, data, MAX_NUM_OF_NODE);
}

//初始化全局世界
void InitWorld(void)
{
	glClearColor(0.5, 0.5, 0.5, 1.0);
}

//初始化控制屏幕
void InitControlScreen(void)
{
	glClearColor(0.3, 0.3, 0.3, 1.0);
}
/****************************************************************************************
*@Name............: void ResizeDisplayScreen(int width, int height)
*@Description.....: 控制窗口变化事件
*@Parameters......: width	:窗口宽度
*					height	:窗口高度
*@Return values...: void
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
void ResizeDisplayScreen(int width, int height)
{
	glViewport(0, 0, width - GAP * 4 - subWidth, subHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120.0, (GLfloat)width / (GLfloat)height, 1.0, 1000.0);//设置透视视景体
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 10.0, 40.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//设置相机位置
}

//控制全局窗口改变事件
void ResizeWorld(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	subWidth = width / 8;
	subHeight = height - 2 * GAP;
	GAP = width / 40;

	/*当窗口改变时，调节各窗口大小*/
	glutSetWindow(controlWindow);
	glutPositionWindow(GAP, GAP);
	glutReshapeWindow(subWidth, subHeight);

	glutSetWindow(rainWindow);
	glutPositionWindow(GAP + subWidth + GAP, GAP);
	glutReshapeWindow(width - GAP * 4 - subWidth, subHeight);
}

//控制屏幕大小变化事件
void ResizeControlScreen(int width, int height)
{
	glViewport(0, 0, subWidth, subHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//根据半径radius画椭圆
void DrawCircle(double radius)
{
	glBegin(GL_LINE_LOOP);
	for (int j = 0; j < SMOOTH_DEGREE; ++j)
		glVertex2f(radius * cos(2 * PI / SMOOTH_DEGREE * j), radius * sin(2 * PI / SMOOTH_DEGREE * j));
	glEnd();
}

void
setfont(char* name, int size)
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

/****************************************************************************************
*@Name............: void DisplayRainScreen(void)
*@Description.....: 落雨场景显示函数
*@Parameters......: void
*@Return values...: void
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
void DisplayRainScreen(void)
{
	ListNode dat;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除背景

	/*绘制月亮*/
	glPushMatrix();
	glTranslatef(moonPosition[0], moonPosition[1], moonPosition[2]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, moonSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, moonDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, moonAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, moonEmission);
	glutSolidSphere(10.0, 32, 32);//绘制一个较大的球体充当月亮
	glPopMatrix();
	for (int i = 1; i <= L.num; ++i)
	{
		GetListIndexNode(&L, i, &dat);

		/*设置雨滴材料颜色*/
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, GetRainDropSpecular(dat.rainDrop));
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, GetRainDropDiffuse(dat.rainDrop));
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, GetRainDropAmbient(dat.rainDrop));
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, GetRainDropShininess(dat.rainDrop));
		glLineWidth(GetWidthOfRainDrop(dat.rainDrop));

		if (Falling == GetRainState(dat.rainDrop))
		{
			GLdouble rainCoord[][3] = { 
				{GetXCoord(dat.rainDrop), GetYCoord(dat.rainDrop), GetZCoord(dat.rainDrop)},
				{GetXCoordEndPoint(dat.rainDrop), GetYCoordEndPoint(dat.rainDrop), GetZCoord(dat.rainDrop)} };//获取雨滴顶点坐标
			/*绘制雨滴*/
			glBegin(GL_LINES);
			glVertex3dv(rainCoord[1]);
			glVertex3dv(rainCoord[0]);
			glEnd();

			if (TRUE == IsTouchWater(dat.rainDrop))//根据落水坐标判断是否该转换成生成涟漪的状态
			{
				ChangeRainStateToMelting(dat.rainDrop);
				Beep(500, 30);//水滴有声
			}
				
			UpdateListNode(&L, i, increaseCoord);//更新结点数据
		}
		else if (Melting == GetRainState(dat.rainDrop))
		{
			/*绘制涟漪*/
			glPushMatrix();
			glTranslated(GetXCoord(dat.rainDrop), GetYCoord(dat.rainDrop), GetZCoord(dat.rainDrop));//设置相对坐标系使涟漪在雨滴下落处生成
			glRotatef(90.0, 1.0, 0.0, 0.0);
			DrawCircle(GetCurrentRadius(dat.ripple));
			glPopMatrix();
			UpdateRippleRadius(dat.ripple, increaseRadius);//更新涟漪半径

			if (TRUE == IsRadiusEqualToMax(dat.ripple))//判断是否更新结点状态
			{
				ChangeRainStateToDying(dat.rainDrop);
				for (int j = 0; j < density; ++j)//预置雨滴
				{
					CreateData(&dat, windSpeed);
					InseartList(&L, dat);
				}
			}
				
		}
		else if (Dying == GetRainState(dat.rainDrop))
		{
			DeleteList(&L, i);
			
		/*	increaseCoord = L.num * 0.01 + 0.3;
			increaseRadius = L.num * 0.0001 + 0.03;*/
		}
	}
	
	glutSwapBuffers();
}

void DisplayWorld(void)
{
	glClearColor(0.85, 0.85, 0.85, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除背景
	glColor3ub(1, 0, 0);
	setfont("helvetica", 12);
	drawstr(GAP, GAP - 5, "Control Screen");
	drawstr(GAP * 2 + subWidth, GAP - 5, "Rain Screen");
	glutSwapBuffers();
}

void DisplayControlScreen(void)
{
	glClearColor(0.7, 0.7, 0.7, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除背景
	glutSwapBuffers();
}
/****************************************************************************************
*@Name............: void idle(void)
*@Description.....: 空闲函数
*@Parameters......: void
*@Return values...: void
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
void Idle(void)
{
	glutSetWindow(rainWindow);
	glutPostRedisplay();
	glutSetWindow(controlWindow);
	glutPostRedisplay();
}

/****************************************************************************************
*@Name............: void keyBoard(unsigned char key, int x, int y)
*@Description.....: 按键处理函数
*@Parameters......: key		:按下的‘键’
*@Return values...: void
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
void KeyBoard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27://按下"Esc"则退出
			exit(0);
			break;
	}
}