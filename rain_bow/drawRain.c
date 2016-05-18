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

/****************************************************************************************
*	Struct Define Section
****************************************************************************************/
//荷叶结构体
typedef struct leave {
	double x;			//x坐标
	double z;			//z坐标
	double radius;		//半径
	double curvature;	//曲率
	int lineGap;		//荷叶黑线之间的间隔
}leave;

//山结构体
typedef struct Mount {
	float x;
	float z;
	double radius;			//半径
	double curvature;		//曲率
	int direction;			//方向，表示前后左右
	float mountAmbient[4];	//山的颜色属性
}Mount;
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
const GLfloat moonAmbient[] = { 0.9, 0.9, 0.8, 1.0 };
const GLfloat moonDiffuse[] = { 0.5, 0.5, 0.5, 1.0 };
const GLfloat moonSpecular[] = { 0.5, 0.5, 0.5, 1.0 };
const GLfloat moonPosition [] = { -300.0, 300.0, -100.0, 0.0 };

/*水平面属性*/
const GLfloat waterAmbient[] = { 0.6, 0.8, 0.9, 1.0 };
const GLfloat waterDiffuse[] = { 0.5, 0.5, 0.5, 1.0 };
const GLfloat waterSpecular[] = { 0.5, 0.5, 0.5, 1.0 };

//荷叶属性
const GLfloat leaveAmbient[] = { 0.2, 0.6, 0.2, 1.0 };
const GLfloat leaveDiffuse[] = { 0.5, 0.5, 0.5, 1.0 };
const GLfloat leaveSpecular[] = { 0.5, 0.5, 0.5, 1.0 };
leave leaves[MAX_NUM_OF_LEAVES];

//山的属性
Mount mount[MAX_NUM_OF_MOUNT];

//照相机属性
double Θ = PI / 2;						//球坐标系旋转角度
double φ = PI;							//球坐标系旋转角度
double rotateSpeed = PI / 180.0;		//旋转速度
GLfloat sightDistance = 10.0;			//眼睛注视的距离
GLfloat eye[3] = { 0.0, 10.0, 0.0 };
GLfloat at[3] = { 0.0, 0.0, 0.0 };
GLfloat up[3] = { 0.0, 1.0, 0.0 };
unsigned int timeCount = 0;
#define TIME_COUNT 100

/*
**按钮左上角和右下角坐标
**第一为Thunder坐标
**第二和第五为移动速度加减速度按钮
**第三和第六为风速加减按钮
**第四和第七位增减雨滴数目按钮
**第八为狂风坐标
*/
GLuint buttonCoord[8][4];
GLuint buttonIndex = 0;		//被按下的按钮序数

int timesOfImpacting = 0;				//雨滴与荷叶碰撞次数
static float windSpeed = 1.0;			//风速
static double increaseCoord = 10.0;		//坐标增量
static double increaseRadius = 0.05;	//半径增量
static int density = 10;				//雨滴密度,至少为1
static List L;

Thunders thunders;			//闪电链表
int IsThunder = 0;			//判断是否闪电
int IsWildWind = 0;			//判断是否狂风骤雨
extern int mainWindow;		//主窗口
extern int controlWindow;	//控制台
extern int rainWindow;		//雨中场景窗口
extern GLuint GAP;			//间隔

GLfloat moveSpeed = 1.0;	//前进速度 
GLuint subWidth, subHeight;	//控制台子窗口宽度和高度
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

	/*设置光照属性*/
	glLightfv(GL_LIGHT1, GL_AMBIENT, moonAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, moonDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, moonDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, moonPosition);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 2.0);

	InitList(&L);
	CreateDataArray(data, MAX_NUM_OF_NODE, windSpeed);
	CreateList(&L, data, MAX_NUM_OF_NODE);

	for (int i = 0; i < MAX_NUM_OF_LEAVES; ++i)
	{
		SetLeavesAttribute(leaves, MAX_NUM_OF_LEAVES);
	}

	SetMountAttribute(mount, MAX_NUM_OF_MOUNT);

	InitThunderList(&thunders);
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
	glViewport(0, 0, width, subHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120.0, (GLfloat)width / (GLfloat)height, 1.0, 1000.0);//设置透视视景体
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*设置相机观察点*/
	at[0] = eye[0] + sightDistance * sin(Θ) * sin(φ);	//眼睛看到的x轴坐标由所处的位置和旋转角度决定
	at[2] = eye[2] + sightDistance * sin(Θ) * cos(φ);	//z轴坐标
	at[1] = eye[1] + sightDistance * cos(Θ);			//y坐标
	gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);//设置相机位置
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
	subHeight = height - 2 * GAP;//可能会造成子窗口高度为负数
	GAP = width * height / 100000 + 12;
	
	/*设置按钮坐标*/
	for (int i = 0; i < 4; ++i)
	{
		buttonCoord[i][0] = GAP / 2.0;
		buttonCoord[i][1] = GAP / 2.0 + i * GAP * 2;
		buttonCoord[i][2] = subWidth / 2 - GAP / 3.0;
		buttonCoord[i][3] = buttonCoord[i][1] + GAP * 1.5;
	}
	for (int i = 4; i < 7; ++i)
	{
		buttonCoord[i][0] = buttonCoord[0][2] + GAP / 2.0;
		buttonCoord[i][1] = buttonCoord[i - 3][1];
		buttonCoord[i][2] = subWidth - GAP / 3.0;
		buttonCoord[i][3] = buttonCoord[i][1] + GAP * 1.5;
	}

	//狂风骤雨坐标
	buttonCoord[7][0] = buttonCoord[0][2] + GAP / 2.0;
	buttonCoord[7][1] = GAP / 2.0;
	buttonCoord[7][2] = subWidth - GAP / 3.0;
	buttonCoord[7][3] = buttonCoord[7][1] + GAP * 1.5;

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

//根据半径radius画圆
void DrawCircle(double radius)
{
	glBegin(GL_LINE_LOOP);
	for (int j = 0; j < SMOOTH_DEGREE; ++j)
		glVertex2f(radius * cos(2 * PI / SMOOTH_DEGREE * j), radius * sin(2 * PI / SMOOTH_DEGREE * j));
	glEnd();
}

//设置荷叶属性
void SetLeavesAttribute(leave leaves[], int num)
{
	for (int i = 0; i < num; ++i)
	{
		leaves[i].x = 300 - (0.1 * (rand() % 6000));
		leaves[i].z = 300 - (0.1 * (rand() % 6000));
		leaves[i].radius = rand() % 20 + 5.0;
		leaves[i].curvature = rand() % 5 + 1.5;
		leaves[i].lineGap = SMOOTH_DEGREE * 2 / leaves[i].radius;
	}
}

//设置山的属性
void SetMountAttribute(Mount mount[], int num)
{
	for (int i = 0; i < num; ++i)
	{
		mount[i].mountAmbient[0] = 0.2;
		mount[i].mountAmbient[1] = 0.6;
		mount[i].mountAmbient[2] = 0.2;
		mount[i].mountAmbient[3] = 1.0;
		for (int j = 0; j < 3; ++j)
		{
			mount[i].mountAmbient[j] += 0.2 - rand() % 100 * 0.01;
		}
		mount[i].direction = rand() % 4;
		mount[i].curvature = 0.3 + 0.01 * (rand() % 100);
		mount[i].radius = (double)(rand() % 300);
		mount[i].x = (float)(800 - rand() % 1600);
		mount[i].z = (float)(800 - rand() % 1600);
	}
}
//根据半径radius,曲率curvature及x、z坐标画实心椭圆
void DrawSolidCircle(double x, double z, double radius, double curvature, int lineGap)
{
	float dotAmbient[] = { 0.0, 0.1, 0.1, 1.0 };
	float dotDiffuse[] = { 0.0, 0.0, 0.0, 1.0 };
	float dotSpecular[] = { 0.0, 0.0, 0.0, 1.0 };
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, leaveSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, leaveDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, leaveAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glTranslatef(0.0, -radius / 25.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);

	glBegin(GL_TRIANGLE_FAN);//绘制椭圆代替荷叶
	for (int j = 0; j < SMOOTH_DEGREE; ++j)
		glVertex2f(x + radius * cos(2 * PI / SMOOTH_DEGREE * j), z + radius * sin(2 * PI / SMOOTH_DEGREE * j) / curvature);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, dotAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dotDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, dotSpecular);

	for (int j = 0; j < SMOOTH_DEGREE; j += lineGap) 
	{
		glBegin(GL_LINES);//绘制黑线
		glVertex2f(x + radius * cos(2 * PI / SMOOTH_DEGREE * j), z + radius * sin(2 * PI / SMOOTH_DEGREE * j) / curvature);
		glVertex2f(x, z);
		glEnd();
	}

	glPopMatrix();
}

//画山
void DrawMountain(Mount mount)
{
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mount.mountAmbient);
	switch (mount.direction)
	{
		case 0:
			glTranslatef(800.0 + mount.radius / 100.0, -increaseCoord - 2.0, mount.z);
			glRotatef(-90.0, 0.0, 1.0, 0.0);
			break;

		case 1:
			glTranslatef(-800.0 + mount.radius / 100.0, -increaseCoord - 2.0, mount.z);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			break;

		case 2:
			glTranslatef(mount.x, -increaseCoord - 2.0, 800.0 + mount.radius / 100.0);
			break;

		case 3:
			glTranslatef(mount.x, -increaseCoord - 2.0, -800.0 + mount.radius / 100.0);
			break;
	}

	glBegin(GL_TRIANGLE_FAN);//绘制半椭圆代替小山
	for (int j = 0; j <= SMOOTH_DEGREE; ++j)
		glVertex2f(mount.radius * cos(PI / SMOOTH_DEGREE * j), mount.radius * sin(PI / SMOOTH_DEGREE * j) / mount.curvature);
	glEnd();
	glPopMatrix();
}

//绘制荷叶
void DrawLeaves(leave leaves[])
{
	for (int i = 0; i < MAX_NUM_OF_LEAVES; ++i)
	{
		DrawSolidCircle(leaves[i].x, leaves[i].z, leaves[i].radius, leaves[i].curvature, leaves[i].lineGap);
	}
}

//绘制月亮
void DrawMoon(void)
{
	glPushMatrix();
	glTranslatef(moonPosition[0], moonPosition[1], moonPosition[2]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, moonSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, moonDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, moonAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, moonEmission);
	glutSolidSphere(25.0, 32, 32);//绘制一个较大的球体充当月亮
	glPopMatrix();
}

//绘制水平面
void DrawWater(void)
{
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, waterSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, waterDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, waterAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glTranslatef(0.0, -increaseCoord - 2.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glNormal3f(0.0, 1.0, 0.0);
	glRectd(-800.0, -800.0, 800.0, 800.0);
	glPopMatrix();
}

//绘制闪电
void DrawThunder(Thunders *thunders)
{
	ThunderTreeList treeList;
	double coordHeadTree[3];
	GLfloat thunderAmbient[] = { 0.9, 0.9, 0.2, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, thunderAmbient);
	
	for (int i = 1; i <= thunders->numOfThunder; ++i)
	{
		int num = 0;
		GetIndexThunders(thunders, i, &treeList);
		glLineWidth((GLfloat)treeList.numOfTree / 3.0);		
		if (0 == treeList.flag)//根据访问到的结点数依次展开闪电树
		{
			IncreaseThunderTreeVisitTimes(thunders, i);
			if (treeList.visitTimes + 1 == treeList.numOfAllNodes)
				ChangeThunderTreeFlag(thunders, i);
		}
		else 
		{
			DecreaseThunderTreeVisitTimes(thunders, i);;//依次消逝闪电
			if (0 == treeList.visitTimes)
			{
				DeleteThunder(thunders, i);
				if (thunders->numOfThunder == 0)
				{
					IsThunder = 0;
					if (NULL == PlaySound(TEXT("\\rain.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP))//异步播放音乐
						printf("NULL");
				}
					
				break;
			}
		}

		for (int j = 1; j <= treeList.numOfTree; ++j)
		{
			ThunderNodeList thunderNodeList;
			double coordTree[3];
			double coordBenchHead[3];
			
			GetIndexThunderTree(&treeList, j, coordTree, &thunderNodeList);
			if (j > 1)
			{
				glBegin(GL_LINES);
				glVertex3dv(coordHeadTree);
				glVertex3dv(coordTree);
				glEnd();
				if (++num > treeList.visitTimes)
					break;
			}

			memcpy(coordHeadTree, coordTree, sizeof(coordHeadTree));//coordHead保留分支的每个点，也即每次绘制的初始点
			memcpy(coordBenchHead, coordTree, sizeof(coordBenchHead));//coordHead保留分支的每个点，也即每次绘制的初始点

			for (int k = 1; k <= thunderNodeList.numOfNode; ++k)
			{
				double coordEnd[3];
				GetIndexThunderNode(&thunderNodeList, k, coordEnd);
				glBegin(GL_LINES);
				glVertex3dv(coordBenchHead);
				glVertex3dv(coordEnd);
				glEnd();
				memcpy(coordBenchHead, coordEnd, sizeof(coordBenchHead));
				if (++num > treeList.visitTimes)
					break;
			}
		}
	}
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

	DrawMoon();//绘制月亮
	DrawWater();//绘制水平面
	DrawLeaves(leaves);//绘制椭圆代替荷叶，需要计算椭圆中心以便求得雨滴是否与其碰撞
	for (int i = 0; i < MAX_NUM_OF_MOUNT; ++i)
	{
		DrawMountain(mount[i]);
	}
	
	if (IsThunder)
		DrawThunder(&thunders);

	if(increaseCoord > 0.01 && rand() % 100 > 50)
	for (int j = 0; j < density; ++j)//预置雨滴
	{
		CreateData(&dat, windSpeed);
		InseartList(&L, dat);
	}

	for (int i = 1; i <= L.num; ++i)
	{
		GetListIndexNode(&L, i, &dat);

		/*设置雨滴材料*/
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, GetRainDropSpecular(dat.rainDrop));
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, GetRainDropDiffuse(dat.rainDrop));
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, GetRainDropAmbient(dat.rainDrop));
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, GetRainDropShininess(dat.rainDrop));
		glLineWidth(GetWidthOfRainDrop(dat.rainDrop));

		switch (GetRainState(dat.rainDrop))
		{
			case Falling : 
			{
				GLdouble rainCoord[][3] = {
					{ GetXCoord(dat.rainDrop), GetYCoord(dat.rainDrop), GetZCoord(dat.rainDrop) },
					{ GetXCoordEndPoint(dat.rainDrop), GetYCoordEndPoint(dat.rainDrop), GetZCoord(dat.rainDrop) } };//获取雨滴顶点坐标
																													/*绘制雨滴*/
				glBegin(GL_LINES);
				glVertex3dv(rainCoord[1]);
				glVertex3dv(rainCoord[0]);
				glEnd();

				if (TRUE == IsTouchWater(dat.rainDrop))//根据落水坐标判断是否接触到水平面
				{
					int i;
					for (i = 0; i < MAX_NUM_OF_LEAVES; ++i)//判断是否接触到荷叶
					{
						if (TRUE == IsInEllipse(dat.rainDrop, leaves[i].x, leaves[i].z, leaves[i].curvature, leaves[i].radius))
						{
							timesOfImpacting++;
							ChangeRainStateToImpacting(dat.rainDrop);
							UpdateSlope(dat.rainDrop, -windSpeed);//风速取反，则表示向反斜率方向运动
							Beep(500, 15);//触碰荷叶有声
							break;
						}
					}

					if (MAX_NUM_OF_LEAVES == i)//否则就直接进水
						ChangeRainStateToMelting(dat.rainDrop);
					
				}

				UpdateListNode(&L, i, increaseCoord);//更新结点数据
				UpdateSlope(dat.rainDrop, windSpeed);//更新风速
			}break;

			case Impacting :
			{
				if (TRUE == IsBeingHighest(dat.rainDrop))
				{
					ChangeRainStateToDying(dat.rainDrop);
				}
				GLdouble rainCoord[][3] = {
					{ GetXCoord(dat.rainDrop), GetYCoord(dat.rainDrop), GetZCoord(dat.rainDrop) },
					{ GetXCoordEndPoint(dat.rainDrop), GetYCoordEndPoint(dat.rainDrop), GetZCoord(dat.rainDrop) } };//获取雨滴顶点坐标
																													/*绘制雨滴*/
				glBegin(GL_LINES);
				glVertex3dv(rainCoord[0]);
				glVertex3dv(rainCoord[1]);
				glEnd();
				UpdateListNode(&L, i, -increaseCoord);//更新结点数据
				UpdateSlope(dat.rainDrop, -windSpeed);
				
			}break;

			case Melting :
			{
				/*绘制涟漪*/
				glPushMatrix();
				glTranslated(GetXCoord(dat.rainDrop), GetYCoord(dat.rainDrop), GetZCoord(dat.rainDrop));//设置相对坐标系使涟漪在雨滴下落处生成
				glRotatef(90.0, 1.0, 0.0, 0.0);
				DrawCircle(GetCurrentRadius(dat.ripple));
				glPopMatrix();
				UpdateRippleRadius(dat.ripple, increaseRadius);//更新涟漪半径

				if (TRUE == IsRadiusEqualToMax(dat.ripple))//判断涟漪半径达到最大值
				{
					ChangeRainStateToDying(dat.rainDrop);
				}
			}break;

			case Dying :
			{
				DeleteList(&L, i);
			}break;
		}
	}
	
	glutSwapBuffers();
}

//绘制全局世界
void DisplayWorld(void)
{
	glClearColor(0.85, 0.85, 0.85, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除背景
	glColor3ub(1, 0, 0);
	setFont("helvetica", (GAP >= 18 ? 18 : 12));
	drawstr(GAP, GAP - 4, "Control Screen");
	drawstr(GAP * 2 + subWidth, GAP - 4, "Rain Screen");
	glutSwapBuffers();
}

//绘制控制屏幕
void DisplayControlScreen(void)
{
	char *str[] = { "Thunder", "Speed -", "Wind -", "Rain -", "Speed +", "Wind +", "Rain +"};
	glClearColor(0.7, 0.7, 0.7, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除背景
	setFont("helvetica", (GAP >= 18 ? 18 : 12));

	/*显示按钮*/
	for (int i = 0; i < 7; ++i)
	{
		glColor3f(0.9, 0.9, 0.9);
		glRectd(buttonCoord[i][0], buttonCoord[i][1], buttonCoord[i][2], buttonCoord[i][3]);
		glColor3f(0.3, 0.3, 0.7);
		drawstr(buttonCoord[i][0] + 2, buttonCoord[i][3] - GAP * 0.5, str[i]);
	}

	//显示狂风按钮
	glColor3f(0.9, 0.9, 0.9);
	glRectd(buttonCoord[7][0], buttonCoord[7][1], buttonCoord[7][2], buttonCoord[7][3]);
	if (IsWildWind)
		glColor3f(0.9, 0.1, 0.1);
	else
		glColor3f(0.1, 0.8, 0.1);
	drawstr(buttonCoord[7][0] + 2, buttonCoord[7][3] - GAP * 0.5, "WildWind");//狂风时显示红色，否则显示绿色

	if (buttonIndex)
	{
		glColor3f(1.0, 1.0, 0.1);
		drawstr(buttonCoord[buttonIndex - 1][0] + 2, buttonCoord[buttonIndex - 1][3] - GAP * 0.5, str[buttonIndex - 1]);
	}

	/*显示镜头坐标*/
	glColor3f(0.0, 0.0, 0.0);
	drawstr(12, subHeight - 500, "Number Of Thunders:");
	drawstr(12, subHeight - 450, "Times Of Impacting:");
	drawstr(12, subHeight - 400, "MoveSpeed:");
	drawstr(12, subHeight - 350, "WindSpeed:");
	drawstr(12, subHeight - 300, "Number Of Rain:");
	drawstr(12, subHeight - 250, "rainFallingSpeed:");
	drawstr(12, subHeight - 200, "eyes:");
	drawstr(12, subHeight - 100, "at:");

	glColor3f(0.2, 0.2, 0.7);
	drawstr(12 + GAP, subHeight - 500 + 25, "%d", thunders.numOfThunder);
	drawstr(12 + GAP, subHeight - 450 + 25, "%d", timesOfImpacting);
	drawstr(12 + GAP, subHeight - 400 + 25, "%.2f", moveSpeed);
	drawstr(12 + GAP, subHeight - 350 + 25, "%.2f", windSpeed);
	drawstr(12 + GAP, subHeight - 300 + 25, "%d", L.num);
	drawstr(12 + GAP, subHeight - 250 + 25, "%.2f", increaseCoord);
	drawstr(12 + GAP, subHeight - 200 + 25, "X:%.2f", eye[0]);
	drawstr(12 + GAP, subHeight - 200 + 45, "Y:%.2f", eye[1]);
	drawstr(12 + GAP, subHeight - 200 + 65, "Z:%.2f", eye[2]);
	drawstr(12 + GAP, subHeight - 100 + 25, "X:%.2f", at[0]);
	drawstr(12 + GAP, subHeight - 100 + 45, "Y:%.2f", at[1]);
	drawstr(12 + GAP, subHeight - 100 + 65, "Z:%.2f", at[2]);
	//drawstr(12 + GAP, subHeight - 300 + 65 + 10, "Θ: %.2f", Θ);
	//drawstr(12 + GAP, subHeight - 300 + 65 + 30, "φ: %.2f", φ);
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
	timeCount++;
	if (timeCount == TIME_COUNT)//定时改变风速
	{
		if (IsWildWind)
			windSpeed = 10.0 - rand() % 1000 * 0.02;

		timeCount = 0;
	}
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
		case 27:	//按下"Esc"则退出
			exit(0);
			break;
		case 'w':	//向前移动
			eye[2] -= cos(PI - φ) * moveSpeed;
			eye[0] += sin(PI - φ) * moveSpeed;
			RedisplayAll();
			break;
		case 's':	//向后移动
			eye[2] += cos(PI - φ) * moveSpeed;
			eye[0] -= sin(PI - φ) * moveSpeed;
			RedisplayAll();
			break;
		case 'a':	//向左移动
			eye[0] -= sin(φ - PI / 2) * moveSpeed;
			eye[2] -= cos(φ - PI / 2) * moveSpeed;
			RedisplayAll();
			break;
		case 'd':	//向右移动
			eye[0] += sin(φ - PI / 2) * moveSpeed;
			eye[2] += cos(φ - PI / 2) * moveSpeed;
			RedisplayAll();
			break;
		case '8'://向上眺望
			Θ -= rotateSpeed;
			if (Θ <= 0.0)
				Θ = 0.0 + rotateSpeed;
			RedisplayAll();
			break;
		case '2'://向下俯视
			Θ += rotateSpeed;
			if (Θ > PI -rotateSpeed)
				Θ = PI - rotateSpeed;
			RedisplayAll();
			break;
		case '6'://向右旋转
			φ -= rotateSpeed;
			RedisplayAll();
			break;
		case '4'://向左旋转
			φ += rotateSpeed;
			RedisplayAll();
			break;
		case '+'://雨滴下落加速
			increaseCoord += 0.1;
			break;
		case '-'://雨滴下落减速
			increaseCoord -= 0.1;
			if (increaseCoord < 0.0)
				increaseCoord = 0.0;
			break;
		default:
			break;
	}
}

//特殊按键，特指数字和字母外的一些功能键
void SpecialKeyBoard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_UP: //向上箭头，表示人物向上移动
			eye[1] += moveSpeed;
			at[1] += moveSpeed;
			RedisplayAll();
			break;

		case GLUT_KEY_DOWN: //向下箭头，表示人物向地下移动
			eye[1] -= moveSpeed;
			at[1] -= moveSpeed;
			RedisplayAll();
			break;
		default:
			break;
	}
}
void RedisplayAll(void)
{
	/*当窗口改变时，调节各窗口大小*/
	glutSetWindow(controlWindow);
	ResizeControlScreen(subWidth, subHeight);
	glutPostRedisplay();

	glutSetWindow(rainWindow);
	ResizeDisplayScreen(1600 - GAP * 4 - subWidth, subHeight);
	glutPostRedisplay();
}

//鼠标按键点击事件
void MouseMotion(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		if (x >= buttonCoord[0][0] && x <= buttonCoord[0][2])//左边一列的按钮
		{
			if (y >= buttonCoord[0][1] && y <= buttonCoord[0][3])//第一行按钮
			{
				buttonIndex = 1;
				IsThunder = 1;
				InsertThundersList(&thunders);
				if (NULL == PlaySound(TEXT("\\thunder.wav"), NULL, SND_FILENAME | SND_ASYNC))//异步播放音乐
					printf("NULL");
			}
			else if (y >= buttonCoord[1][1] && y <= buttonCoord[1][3])//第二行按钮
			{
				buttonIndex = 2;
				if (moveSpeed - 0.1 >= 0.0001)
					moveSpeed -= 0.1;
				if (rotateSpeed > PI / 180)
					rotateSpeed -= PI / 24;
			}
			else if (y >= buttonCoord[2][1] && y <= buttonCoord[2][3])//第三行按钮
			{
				buttonIndex = 3;
				windSpeed -= 0.05;
			}
			else if (y >= buttonCoord[3][1] && y <= buttonCoord[3][3])//第四行按钮
			{
				buttonIndex = 4;
				for (int i = 1; i < 50; ++i)
				{
					DeleteList(&L, 1);
				}
			}
		}
		else if (x >= buttonCoord[4][0] && x <= buttonCoord[4][2])//右边一列的按钮
		{
			if (y >= buttonCoord[4][1] && y <= buttonCoord[4][3])//第一行按钮
			{
				buttonIndex = 5;
				moveSpeed += 0.1;
				if (rotateSpeed < PI / 24)
					rotateSpeed += PI / 24;
			}
			else if (y >= buttonCoord[5][1] && y <= buttonCoord[5][3])//第二行按钮
			{
				buttonIndex = 6;
				windSpeed += 0.05;
			}
			else if (y >= buttonCoord[6][1] && y <= buttonCoord[6][3])//第三行按钮
			{
				ListNode dat;
				buttonIndex = 7;
				/*新增结点*/
				for (int i = 0; i < 50; ++i)
				{
					CreateData(&dat, windSpeed);
					InseartList(&L, dat);
				}
			}
			else if (y >= buttonCoord[7][1] && y <= buttonCoord[7][3])
			{
				IsWildWind = !IsWildWind;
			}
		}
		RedisplayAll();
	}
	if (state == GLUT_UP && button == GLUT_LEFT_BUTTON)
	{
		buttonIndex = 0;
	}
}