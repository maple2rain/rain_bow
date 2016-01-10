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
//��Ҷ�ṹ��
typedef struct leave {
	double x;			//x����
	double z;			//z����
	double radius;		//�뾶
	double curvature;	//����
}leave;
/*****************************************************************************************
*	Global Variable Declare Section
*****************************************************************************************/
/*��������*/
const GLfloat light_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 0.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 0.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 0.0f, 100.0f, 0.0f };
const GLfloat local_view[] = { GL_TRUE };

/*��������*/
GLfloat shininess[] = { 100.0 };
const GLfloat moonEmission[] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat moonAmbient[] = { 0.9, 0.9, 0.9, 1.0 };
const GLfloat moonDiffuse[] = { 0.5, 0.5, 0.5, 1.0 };
const GLfloat moonSpecular[] = { 0.5, 0.5, 0.5, 1.0 };
const GLfloat moonPosition [] = { -300.0, 300.0, -100.0, 0.0 };

/*ˮƽ������*/
const GLfloat waterAmbient[] = { 0.6, 0.8, 0.9, 1.0 };
const GLfloat waterDiffuse[] = { 0.5, 0.5, 0.5, 1.0 };
const GLfloat waterSpecular[] = { 0.5, 0.5, 0.5, 1.0 };

//��Ҷ����
const GLfloat leaveAmbient[] = { 0.2, 0.6, 0.2, 1.0 };
const GLfloat leaveDiffuse[] = { 0.5, 0.5, 0.5, 1.0 };
const GLfloat leaveSpecular[] = { 0.5, 0.5, 0.5, 1.0 };

//���������
double �� = PI / 2;						//������ϵ��ת�Ƕ�
double �� = PI;							//������ϵ��ת�Ƕ�
double rotateSpeed = PI / 180.0;		//��ת�ٶ�
GLfloat sightDistance = 10.0;			//�۾�ע�ӵľ���
GLfloat eye[3] = { 0.0, 10.0, 0.0 };
GLfloat at[3] = { 0.0, 0.0, 0.0 };
GLfloat up[3] = { 0.0, 1.0, 0.0 };

/*
**��ť���ϽǺ����½�����
**��һΪThunder����
**�ڶ��͵���Ϊ�ƶ��ٶȼӼ��ٶȰ�ť
**�����͵���Ϊ���ټӼ���ť
**���ĺ͵���λ���������Ŀ��ť
*/
GLuint buttonCoord[7][4];
GLuint buttonIndex = 0;		//�����µİ�ť����

static float windSpeed = 1.0;			//����
static double increaseCoord = 0.5;		//��������
static double increaseRadius = 0.05;	//�뾶����
static int density = 10;					//����ܶ�,����Ϊ1
static List L;

extern int mainWindow;		//������
extern int controlWindow;	//����̨
extern int rainWindow;		//���г�������
extern GLuint GAP;			//���

GLfloat moveSpeed = 0.5;	//ǰ���ٶ� 
GLuint subWidth, subHeight;	//����̨�Ӵ��ڿ�Ⱥ͸߶�
/****************************************************************************************
*	Function Define Section
****************************************************************************************/
/****************************************************************************************
*@Name............: void InitRainScreen(void)
*@Description.....: ��ʼ�����곡��
*@Parameters......: void
*@Return values...: void
*@PreCondition....�����ڻ�ͼ֮ǰ�����ã��Ӷ�ʵ�ֹ���
*@PostCondition...����
*****************************************************************************************/
void InitRainScreen(void)
{
	ListNode data[MAX_NUM_OF_NODE];
	srand((unsigned)time(NULL));

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	/*���û�Ͽ����*/
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(1.5);

	/*���ù�������*/
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
}

//��ʼ��ȫ������
void InitWorld(void)
{
	glClearColor(0.5, 0.5, 0.5, 1.0);
}

//��ʼ��������Ļ
void InitControlScreen(void)
{
	glClearColor(0.3, 0.3, 0.3, 1.0);
}

/****************************************************************************************
*@Name............: void ResizeDisplayScreen(int width, int height)
*@Description.....: ���ƴ��ڱ仯�¼�
*@Parameters......: width	:���ڿ��
*					height	:���ڸ߶�
*@Return values...: void
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
void ResizeDisplayScreen(int width, int height)
{
	glViewport(0, 0, width, subHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120.0, (GLfloat)width / (GLfloat)height, 1.0, 1000.0);//����͸���Ӿ���
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*��������۲��*/
	at[0] = eye[0] + sightDistance * sin(��) * sin(��);	//�۾�������x��������������λ�ú���ת�ǶȾ���
	at[2] = eye[2] + sightDistance * sin(��) * cos(��);	//z������
	at[1] = eye[1] + sightDistance * cos(��);			//y����
	gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);//�������λ��
}

//����ȫ�ִ��ڸı��¼�
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
	GAP = width * height / 100000 + 12;
	
	/*���ð�ť����*/
	for (int i = 0; i < 4; ++i)
	{
		buttonCoord[i][0] = GAP / 2.0;
		buttonCoord[i][1] = GAP / 2.0 + i * GAP * 2;
		buttonCoord[i][2] = subWidth / 2 - GAP / 2.0;
		buttonCoord[i][3] = buttonCoord[i][1] + GAP * 1.5;
	}
	for (int i = 4; i < 7; ++i)
	{
		buttonCoord[i][0] = buttonCoord[0][2] + GAP;
		buttonCoord[i][1] = buttonCoord[i - 3][1];
		buttonCoord[i][2] = subWidth - GAP / 2.0;
		buttonCoord[i][3] = buttonCoord[i][1] + GAP * 1.5;
	}

	/*�����ڸı�ʱ�����ڸ����ڴ�С*/
	glutSetWindow(controlWindow);
	glutPositionWindow(GAP, GAP);
	glutReshapeWindow(subWidth, subHeight);

	glutSetWindow(rainWindow);
	glutPositionWindow(GAP + subWidth + GAP, GAP);
	glutReshapeWindow(width - GAP * 4 - subWidth, subHeight);
}

//������Ļ��С�仯�¼�
void ResizeControlScreen(int width, int height)
{
	glViewport(0, 0, subWidth, subHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//���ݰ뾶radius��Բ
void DrawCircle(double radius)
{
	glBegin(GL_LINE_LOOP);
	for (int j = 0; j < SMOOTH_DEGREE; ++j)
		glVertex2f(radius * cos(2 * PI / SMOOTH_DEGREE * j), radius * sin(2 * PI / SMOOTH_DEGREE * j));
	glEnd();
}

//���ݰ뾶radius,����curvature��x��z���껭ʵ����Բ
void DrawSolidCircle(double x, double z, double radius, double curvature)
{
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, leaveSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, leaveDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, leaveAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glTranslatef(0.0, -increaseCoord, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	for (int j = 0; j < SMOOTH_DEGREE; ++j)
		glVertex2f(x + radius * cos(2 * PI / SMOOTH_DEGREE * j), z + radius * sin(2 * PI / SMOOTH_DEGREE * j) / curvature);
	glEnd();
	glPopMatrix();
}

//��������
void DrawMoon(void)
{
	glPushMatrix();
	glTranslatef(moonPosition[0], moonPosition[1], moonPosition[2]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, moonSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, moonDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, moonAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, moonEmission);
	glutSolidSphere(10.0, 32, 32);//����һ���ϴ������䵱����
	glPopMatrix();
}

//����ˮƽ��
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
	glRectd(-1000.0, -1000.0, 1000.0, 1000.0);
	glPopMatrix();
}
/****************************************************************************************
*@Name............: void DisplayRainScreen(void)
*@Description.....: ���곡����ʾ����
*@Parameters......: void
*@Return values...: void
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
void DisplayRainScreen(void)
{
	ListNode dat;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�������

	DrawMoon();//��������
	DrawWater();//����ˮƽ��
	DrawSolidCircle(10.0, 10.0, 20.0, 3.0);//������Բ����Ҫ������Բ�����Ա��������Ƿ�������ײ

	if(rand() % 100 > 50)
	for (int j = 0; j < density; ++j)//Ԥ�����
	{
		CreateData(&dat, windSpeed);
		InseartList(&L, dat);
	}

	for (int i = 1; i <= L.num; ++i)
	{
		
		GetListIndexNode(&L, i, &dat);

		/*������β���*/
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, GetRainDropSpecular(dat.rainDrop));
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, GetRainDropDiffuse(dat.rainDrop));
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, GetRainDropAmbient(dat.rainDrop));
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, GetRainDropShininess(dat.rainDrop));
		glLineWidth(GetWidthOfRainDrop(dat.rainDrop));

		if (Falling == GetRainState(dat.rainDrop))
		{
			GLdouble rainCoord[][3] = { 
				{GetXCoord(dat.rainDrop), GetYCoord(dat.rainDrop), GetZCoord(dat.rainDrop)},
				{GetXCoordEndPoint(dat.rainDrop), GetYCoordEndPoint(dat.rainDrop), GetZCoord(dat.rainDrop)} };//��ȡ��ζ�������
			/*�������*/
			glBegin(GL_LINES);
			glVertex3dv(rainCoord[1]);
			glVertex3dv(rainCoord[0]);
			glEnd();

			if (TRUE == IsTouchWater(dat.rainDrop))//������ˮ�����ж��Ƿ��ת��������������״̬
			{
				ChangeRainStateToMelting(dat.rainDrop);
				//Beep(500, 30);//ˮ������
			}
				
			UpdateListNode(&L, i, increaseCoord);//���½������
			UpdateSlope(dat.rainDrop, windSpeed);//���·���
		}
		else if (Melting == GetRainState(dat.rainDrop))
		{
			/*��������*/
			glPushMatrix();
			glTranslated(GetXCoord(dat.rainDrop), GetYCoord(dat.rainDrop), GetZCoord(dat.rainDrop));//�����������ϵʹ������������䴦����
			glRotatef(90.0, 1.0, 0.0, 0.0);
			DrawCircle(GetCurrentRadius(dat.ripple));
			glPopMatrix();
			UpdateRippleRadius(dat.ripple, increaseRadius);//���������뾶

			if (TRUE == IsRadiusEqualToMax(dat.ripple))//�ж��Ƿ���½��״̬
			{
				ChangeRainStateToDying(dat.rainDrop);
				//for (int j = 0; j < density && rand() % 1000 > 980; ++j)//Ԥ�����
				//{
				//	CreateData(&dat, windSpeed);
				//	InseartList(&L, dat);
				//}
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

//����ȫ������
void DisplayWorld(void)
{
	glClearColor(0.85, 0.85, 0.85, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�������
	glColor3ub(1, 0, 0);
	setFont("helvetica", (GAP >= 18 ? 18 : 12));
	drawstr(GAP, GAP - 4, "Control Screen");
	drawstr(GAP * 2 + subWidth, GAP - 4, "Rain Screen");
	glutSwapBuffers();
}

//���ƿ�����Ļ
void DisplayControlScreen(void)
{
	char *str[] = { "Thunder", "Speed -", "Wind -", "Rain -", "Speed +", "Wind +", "Rain +"};
	glClearColor(0.7, 0.7, 0.7, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�������
	setFont("helvetica", (GAP >= 18 ? 18 : 12));

	/*��ʾ��ť*/
	for (int i = 0; i < 7; ++i)
	{
		glColor3f(0.9, 0.9, 0.9);
		glRectd(buttonCoord[i][0], buttonCoord[i][1], buttonCoord[i][2], buttonCoord[i][3]);
		glColor3f(0.3, 0.3, 0.7);
		drawstr(buttonCoord[i][0] + 2, buttonCoord[i][3] - GAP * 0.5, str[i]);
	}
	if (buttonIndex)
	{
		glColor3f(1.0, 1.0, 0.1);
		drawstr(buttonCoord[buttonIndex - 1][0] + 2, buttonCoord[buttonIndex - 1][3] - GAP * 0.5, str[buttonIndex - 1]);
	}

	/*��ʾ��ͷ����*/
	glColor3f(0.0, 0.0, 0.0);
	drawstr(12, subHeight - 300, "Number Of Rain: %d", L.num);
	drawstr(12, subHeight - 250, "rainFallingSpeed:");
	drawstr(12, subHeight - 200, "eyes:");
	drawstr(12, subHeight - 100, "at:");
	glColor3f(0.2, 0.2, 0.7);
	drawstr(12 + GAP, subHeight - 250 + 25, "%.2f", increaseCoord);
	drawstr(12 + GAP, subHeight - 200 + 25, "X:%.2f", eye[0]);
	drawstr(12 + GAP, subHeight - 200 + 45, "Y:%.2f", eye[1]);
	drawstr(12 + GAP, subHeight - 200 + 65, "Z:%.2f", eye[2]);
	drawstr(12 + GAP, subHeight - 100 + 25, "X:%.2f", at[0]);
	drawstr(12 + GAP, subHeight - 100 + 45, "Y:%.2f", at[1]);
	drawstr(12 + GAP, subHeight - 100 + 65, "Z:%.2f", at[2]);
	//drawstr(12 + GAP, subHeight - 300 + 65 + 10, "��: %.2f", ��);
	//drawstr(12 + GAP, subHeight - 300 + 65 + 30, "��: %.2f", ��);
	glutSwapBuffers();
}

/****************************************************************************************
*@Name............: void idle(void)
*@Description.....: ���к���
*@Parameters......: void
*@Return values...: void
*@PreCondition....����
*@PostCondition...����
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
*@Description.....: ����������
*@Parameters......: key		:���µġ�����
*@Return values...: void
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
void KeyBoard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:	//����"Esc"���˳�
			exit(0);
			break;
		case 'w':	//��ǰ�ƶ�
			eye[2] -= cos(PI - ��) * moveSpeed;
			eye[0] += sin(PI - ��) * moveSpeed;
			RedisplayAll();
			break;
		case 's':	//����ƶ�
			eye[2] += cos(PI - ��) * moveSpeed;
			eye[0] -= sin(PI - ��) * moveSpeed;
			RedisplayAll();
			break;
		case 'a':	//�����ƶ�
			eye[0] -= sin(�� - PI / 2) * moveSpeed;
			eye[2] -= cos(�� - PI / 2) * moveSpeed;
			RedisplayAll();
			break;
		case 'd':	//�����ƶ�
			eye[0] += sin(�� - PI / 2) * moveSpeed;
			eye[2] += cos(�� - PI / 2) * moveSpeed;
			RedisplayAll();
			break;
		case '8'://��������
			�� -= rotateSpeed;
			if (�� <= 0.0)
				�� = 0.0 + rotateSpeed;
			RedisplayAll();
			break;
		case '2'://���¸���
			�� += rotateSpeed;
			if (�� > PI -rotateSpeed)
				�� = PI - rotateSpeed;
			RedisplayAll();
			break;
		case '6'://������ת
			�� -= rotateSpeed;
			RedisplayAll();
			break;
		case '4'://������ת
			�� += rotateSpeed;
			RedisplayAll();
			break;
		case '+'://����������
			if(increaseCoord < 4.9)
			increaseCoord += 0.1;
			break;
		case '-'://����������
			increaseCoord -= 0.1;
			if (increaseCoord < 0.0)
				increaseCoord = 0.0;
			break;
		default:
			break;
	}
}

//���ⰴ������ָ���ֺ���ĸ���һЩ���ܼ�
void SpecialKeyBoard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_UP: //���ϼ�ͷ����ʾ���������ƶ�
			eye[1] += moveSpeed;
			at[1] += moveSpeed;
			RedisplayAll();
			break;

		case GLUT_KEY_DOWN: //���¼�ͷ����ʾ����������ƶ�
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
	/*�����ڸı�ʱ�����ڸ����ڴ�С*/
	glutSetWindow(controlWindow);
	ResizeControlScreen(subWidth, subHeight);
	glutPostRedisplay();

	glutSetWindow(rainWindow);
	ResizeDisplayScreen(1600 - GAP * 4 - subWidth, subHeight);
	glutPostRedisplay();
}

//��갴������¼�
void MouseMotion(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		if (x >= buttonCoord[0][0] && x <= buttonCoord[0][2])//���һ�еİ�ť
		{
			if (y >= buttonCoord[0][1] && y <= buttonCoord[0][3])//��һ�а�ť
			{
				buttonIndex = 1;
			}
			else if (y >= buttonCoord[1][1] && y <= buttonCoord[1][3])//�ڶ��а�ť
			{
				buttonIndex = 2;
				if (moveSpeed >= 0.2)
					moveSpeed -= 0.1;
				if (rotateSpeed > PI / 180)
					rotateSpeed -= PI / 24;
			}
			else if (y >= buttonCoord[2][1] && y <= buttonCoord[2][3])//�����а�ť
			{
				buttonIndex = 3;
				windSpeed -= 0.01;
			}
			else if (y >= buttonCoord[3][1] && y <= buttonCoord[3][3])//�����а�ť
			{
				buttonIndex = 4;
				for (int i = 1; i < 50; ++i)
				{
					DeleteList(&L, 1);
				}
			}
		}
		else if (x >= buttonCoord[4][0] && x <= buttonCoord[4][2])//�ұ�һ�еİ�ť
		{
			if (y >= buttonCoord[4][1] && y <= buttonCoord[4][3])//��һ�а�ť
			{
				buttonIndex = 5;
				moveSpeed += 0.1;
				if (rotateSpeed < PI / 24)
					rotateSpeed += PI / 24;
			}
			else if (y >= buttonCoord[5][1] && y <= buttonCoord[5][3])//�ڶ��а�ť
			{
				buttonIndex = 6;
				windSpeed += 0.01;
			}
			else if (y >= buttonCoord[6][1] && y <= buttonCoord[6][3])//�����а�ť
			{
				ListNode dat;
				buttonIndex = 7;
				/*�������*/
				for (int i = 0; i < 50; ++i)
				{
					CreateData(&dat, windSpeed);
					InseartList(&L, dat);
				}
			}
		}
		RedisplayAll();
	}
	if (state == GLUT_UP && button == GLUT_LEFT_BUTTON)
	{
		buttonIndex = 0;
	}
}