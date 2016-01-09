/****************************************************************************************
*	File Name				:	rain.c
*	CopyRight				:	LPF
*	ModuleName				:	rain
*
*	CPU						:   Inter Core 7
*	RTOS					:
*
*	Create Data				:	2015/12/20
*	Author/Corportation		:	Li PeiFeng
*
*	Abstract Description	:	definite the function for rain
*
*--------------------------------Revision History----------------------------------------
*	No	version		Data		Revised By			Item			Description
*	1							LPF									first coding
*
****************************************************************************************/

/****************************************************************************************
*	Include File Section
****************************************************************************************/
#include "rain.h"

/****************************************************************************************
*	Struct Define Section
****************************************************************************************/
//��β�����ɫ�ṹ��
struct RainColor {
	float ambient[4];	//��λ�����ɫ
	float diffuse[4];	//���ɢ����ɫ
	float specular[4];	//��ξ�����ɫ
	float shininess[1];	//��ξ���ָ��
};

//��νṹ��
struct RainDrop {
	double xCoord;			//x����
	double yCoord;			//y����
	double zCoord;			//z����
	double xEndCoord;		//x�յ�����
	double yEndCoord;		//y�յ�����
	double b;				//����b�� �� x = ky + b�ó�
	double lengthOfRain;	//��γ���
	double widthOfRain;		//��ο��
	double slope;			//���б��
	RainColor rainColor;	//�����ɫ
	RainState rainState;	//���״̬
};

//�����ṹ��
struct Ripple {
	double radius;		//������ǰ�뾶
	double minRadius;	//������С�뾶
	double maxRadius;	//�������뾶
						//��������ɫ��Ϊ��ε���ɫ
};

/****************************************************************************************
*	Function Define Section
****************************************************************************************/

/****************************************************************************************
*@Name............: Status SetRainDropColor(RainColor *rainColor)
*@Description.....: ���������ɫ
*@Parameters......: rainColor	:��νṹ��
*@Return values...: SUCCESS		:������β��ϳɹ�
*@PreCondition....����
*@PostCondition...������������һϵ�������ɫ
*****************************************************************************************/
Status SetRainDropColor(RainColor *rainColor)
{
	/*
	**������ò�����ɫ
	*/
	for (int i = 0; i < 4; ++i)
	{
		rainColor->ambient[i] = (float)((rand() % 1000 * 0.001));
		rainColor->diffuse[i] = (float)((rand() % 1000 * 0.001));
		rainColor->specular[i] = (float)((rand() % 1000 * 0.001));
	}

	rainColor->shininess[0] = 0.8 + (float)(1.0 / (rand() % 5 + 1));//������þ���ָ��

	return SUCCESS;
}

/****************************************************************************************
*@Name............: RainDrop *CreateRainDrop(void)
*@Description.....: ������νṹ��
*@Parameters......: ��
*@Return values...: ��νṹ��ָ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
RainDrop *CreateRainDrop(void)
{
	return (RainDrop*)malloc(sizeof(RainDrop));
}

/****************************************************************************************
*@Name............: Ripple *CreateRipple(void)
*@Description.....: ���������ṹ��
*@Parameters......: ��
*@Return values...: ��νṹ��ָ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
Ripple *CreateRipple(void)
{
	return (Ripple*)malloc(sizeof(Ripple));
}

/****************************************************************************************
*@Name............: Status SetRainDropAttribute(RainDrop *rainDrop, float windSpeed)
*@Description.....: ���������ɫ
*@Parameters......: rainColor	:��νṹ��
*					wind		:���٣���СΪ1.0
*@Return values...: SUCCESS		:������β��ϳɹ�
*                   OVERFLOW	:��η���ռ�ʧ��
*@PreCondition....����
*@PostCondition...������������һϵ�������ɫ
*****************************************************************************************/
Status SetRainDropAttribute(RainDrop *rainDrop, float windSpeed)
{
	/*
	**�����������ֵ
	*/
	rainDrop->xCoord = 300 - (0.1 * (rand() % 6000));
	rainDrop->yCoord = 200.0 + (0.1 * (rand() % 2000));
	rainDrop->zCoord = 300.0 - (0.1 * (rand() % 6000));
	rainDrop->lengthOfRain = (double)(MIN_LENGTH_OF_RAINDROP + rand() % MAX_LENGTH_OF_RAINDROP);
	rainDrop->widthOfRain = (double)(MIN_WIDTH_OF_RAINDROP + rand() % MAX_WIDTH_OF_RAINDROP);
	rainDrop->rainState = Falling;

	rainDrop->slope = windSpeed;
	rainDrop->b = rainDrop->xCoord - rainDrop->slope * rainDrop->yCoord;//x = ky + b
	rainDrop->yEndCoord = rainDrop->yCoord + rainDrop->lengthOfRain;
	rainDrop->xEndCoord = rainDrop->yEndCoord * rainDrop->slope + rainDrop->b;
	
	SetRainDropColor(&rainDrop->rainColor);//������ɫ

	return SUCCESS;
}

/****************************************************************************************
*@Name............: Status SetRipple(Ripple *ripple, double widthOfRain, float lengthOfRain)
*@Description.....: ���������뾶
*@Parameters......: ripple		:�����ṹ��
*					widthOfRain	:��εĿ��
*					lengthOfRain:��εĳ���
*@Return values...: SUCCESS		:������β��ϳɹ�
*                   OVERFLOW	:��η���ռ�ʧ��
*@PreCondition....����εĳ��ȺͿ�Ⱦ�������ˮ����������ʼ�뾶
*@PostCondition...������������һϵ����ΰ뾶
*****************************************************************************************/
Status SetRipple(Ripple *ripple, double widthOfRain, double lengthOfRain)
{
	//����������С�����뾶
	ripple->minRadius = (int)(widthOfRain + lengthOfRain) % 3 + 0.5;
	ripple->maxRadius = ripple->minRadius + 4;
	ripple->radius = ripple->minRadius;

	return SUCCESS;
}

/****************************************************************************************
*@Name............: void UpdateRippleRadius(Ripple *ripple, double offset)
*@Description.....: ���������뾶
*@Parameters......: ripple	:�����ṹ��
*					offset	:�뾶ƫ����
*@Return values...: ��
*@PreCondition....�����ȸ���������
*@PostCondition...����
*****************************************************************************************/
void UpdateRippleRadius(Ripple *ripple, double offset)
{
	ripple->radius += offset;
}

/****************************************************************************************
*@Name............: void UpdateXCoordPoint(RainDrop *rainDrop, double offset)
*@Description.....: �������X����
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��
*@PreCondition....�����ȸ���������
*@PostCondition...����
*****************************************************************************************/
void UpdateXCoordPoint(RainDrop *rainDrop, double offset)
{
	rainDrop->xCoord = rainDrop->yCoord * rainDrop->slope + rainDrop->b;
	rainDrop->xEndCoord = rainDrop->yEndCoord * rainDrop->slope + rainDrop->b;
}

/****************************************************************************************
*@Name............: void UpdateSlope(RainDrop *rainDrop, float windSpeed)
*@Description.....: ����������б��
*@Parameters......: rainDrop	:��νṹ��
*					windSpeed	:���٣���СֵΪ1.0
*@Return values...: ��
*@PreCondition....����
*@PostCondition...�������ٸı�ʱ��Ҫ�ı�б��
*****************************************************************************************/
void UpdateSlope(RainDrop *rainDrop, float windSpeed)
{
	rainDrop->slope = windSpeed;
}

/****************************************************************************************
*@Name............: void UpdateYCoordPoint(RainDrop *rainDrop, double offset)
*@Description.....: �������Y����
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
void UpdateYCoordPoint(RainDrop *rainDrop, double offset)
{
	rainDrop->yCoord -= offset;
	rainDrop->yEndCoord -= offset;
}

/****************************************************************************************
*@Name............: double GetXCoord(RainDrop *rainDrop) 
*@Description.....: ��ȡ���X����
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
double GetXCoord(RainDrop *rainDrop) 
{
	return rainDrop->xCoord;
}

/****************************************************************************************
*@Name............: double GetYCoord(RainDrop *rainDrop)
*@Description.....: ��ȡ���Y����
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
double GetYCoord(RainDrop *rainDrop)
{
	return rainDrop->yCoord;
}

/****************************************************************************************
*@Name............: double GetZCoord(RainDrop *rainDrop)
*@Description.....: ��ȡ���Z����
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
double GetZCoord(RainDrop *rainDrop)
{
	return rainDrop->zCoord;
}

/****************************************************************************************
*@Name............: double GetXCoordEndPoint(RainDrop *rainDrop)
*@Description.....: ��ȡ����յ��X����
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��һ��x����
*@PreCondition....����֪����ǰ��ε�X����
*@PostCondition...����
*****************************************************************************************/
double GetXCoordEndPoint(RainDrop *rainDrop)
{
	return rainDrop->xEndCoord;
}

/****************************************************************************************
*@Name............: double GetYCoordEndPoint(RainDrop *rainDrop)
*@Description.....: ��ȡ����յ��y����
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��һ��y����
*@PreCondition....����֪����ǰ��ε�Y����
*@PostCondition...����
*****************************************************************************************/
double GetYCoordEndPoint(RainDrop *rainDrop)
{
	return rainDrop->yEndCoord;
}

/****************************************************************************************
*@Name............: Status IsTouchWater(RainDrop * rainDrop)
*@Description.....: �ж�����Ƿ�����ˮ��
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: TRUE		:��
*					FALSE		:��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
Status IsTouchWater(RainDrop * rainDrop)
{
	if (rainDrop->yCoord <= 0.0)
		return TRUE;
	else
		return FALSE;
}

/****************************************************************************************
*@Name............: double GetWidthOfRainDrop(RainDrop *rainDrop)
*@Description.....: ��ȡ��ο��
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��ο��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
double GetWidthOfRainDrop(RainDrop *rainDrop)
{
	return rainDrop->widthOfRain;
}

/****************************************************************************************
*@Name............: float* GetRainDropSpecular(RainDrop *rainDrop)
*@Description.....: ��ȡ��ξ�����ɫ
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��ξ�����ɫ����
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
float* GetRainDropSpecular(RainDrop *rainDrop)
{
	return rainDrop->rainColor.specular;
}

/****************************************************************************************
*@Name............: float* GetRainDropDiffuse(RainDrop *rainDrop)
*@Description.....: ��ȡ���ɢ����ɫ
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ���ɢ����ɫ����
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
float* GetRainDropDiffuse(RainDrop *rainDrop)
{
	return rainDrop->rainColor.diffuse;
}

/****************************************************************************************
*@Name............: float* GetRainDropAmbient(RainDrop *rainDrop)
*@Description.....: ��ȡ��λ�����ɫ
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��λ�����ɫ����
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
float* GetRainDropAmbient(RainDrop *rainDrop)
{
	return rainDrop->rainColor.ambient;
}

/****************************************************************************************
*@Name............: float* GetRainDropShininess(RainDrop *rainDrop)
*@Description.....: ��ȡ��ξ�������
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��ξ�������
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
float* GetRainDropShininess(RainDrop *rainDrop)
{
	return rainDrop->rainColor.shininess;
}

/****************************************************************************************
*@Name............: double GetLengthOfRainDrop(RainDrop *rainDrop)
*@Description.....: ��ȡ��γ���
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��γ���
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
double GetLengthOfRainDrop(RainDrop *rainDrop)
{
	return rainDrop->lengthOfRain;
}

/****************************************************************************************
*@Name............: RainState GetRainState(RainDrop *rainDrop)
*@Description.....: ��ȡ���״̬
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ���״̬
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
RainState GetRainState(RainDrop *rainDrop)
{
	return rainDrop->rainState;
}

/****************************************************************************************
*@Name............: void ChangeRainStateToMelting(RainDrop *rainDrop)
*@Description.....: �ı����״̬Ϊ��ˮ״̬
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...���������ˮ��Ӧ�����������ʴ�״̬Ϊ����״̬
*****************************************************************************************/
void ChangeRainStateToMelting(RainDrop *rainDrop)
{
	rainDrop->rainState = Melting;
}

/****************************************************************************************
*@Name............: void ChangeRainStateToDying(RainDrop *rainDrop)
*@Description.....: �ı����״̬Ϊ����״̬
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...��������ɢ��Ӧ��ʧ���Ӷ�����ɾ������ν��
*****************************************************************************************/
void ChangeRainStateToDying(RainDrop *rainDrop)
{
	rainDrop->rainState = Dying;
}

/****************************************************************************************
*@Name............: double GetRippleMinRadius(Ripple *ripple)
*@Description.....: ��ȡ���������С�뾶
*@Parameters......: ripple	:�����ṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
double GetRippleMinRadius(Ripple *ripple)
{
	return ripple->minRadius;
}

/****************************************************************************************
*@Name............: double GetRippleMaxRadius(Ripple *ripple)
*@Description.....: ��ȡ����������뾶
*@Parameters......: ripple	:�����ṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
double GetRippleMaxRadius(Ripple *ripple)
{
	return ripple->maxRadius;
}

/****************************************************************************************
*@Name............: double GetCurrentRadius(Ripple *ripple)
*@Description.....: ��ȡ���������ǰ�뾶
*@Parameters......: ripple	:�����ṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
double GetCurrentRadius(Ripple *ripple)
{
	return ripple->radius;
}

/****************************************************************************************
*@Name............: Status IsRadiusEqualToMax(Ripple *ripple)
*@Description.....: �жϵ�ǰ���������ǰ�뾶�Ƿ񵽴����뾶
*@Parameters......: ripple	:�����ṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
Status IsRadiusEqualToMax(Ripple *ripple)
{
	if (ripple->maxRadius <= ripple->radius)
		return TRUE;
	else
		return FALSE;
}