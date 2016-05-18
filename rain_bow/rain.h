/****************************************************************************************
*	File Name				:	rain.h
*	CopyRight				:	LPF
*	ModuleName				:	rain
*
*	CPU						:   Inter Core 7
*	RTOS					:
*
*	Create Data				:	2015/12/20
*	Author/Corportation		:	Li PeiFeng
*
*	Abstract Description	:	Declared the struct for rain
*
*--------------------------------Revision History--------------------------------------
*	No	version		Data		Revised By			Item			Description
*	1							LPF									first coding
*
****************************************************************************************/

/****************************************************************************************
*	Multi-Include-Prevent Section
****************************************************************************************/
#ifndef RAIN_H_INCLUDED
#define RAIN_H_INCLUDED

/*****************************************************************************************
*	Include File Section
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*****************************************************************************************
*	Macro Define Section
*****************************************************************************************/
#define MAX_LENGTH_OF_RAINDROP 5
#define MIN_LENGTH_OF_RAINDROP 0.5
#define MAX_WIDTH_OF_RAINDROP 2
#define MIN_WIDTH_OF_RAINDROP 0.5

/*****************************************************************************************
*	Struct Define Section
*****************************************************************************************/
//�������״̬
typedef enum RainState {
	Falling,	//�½�������
	Melting,	//����ˮ�Ĺ�����
	Impacting,	//���Ҷ��ײ
	Dying		//�Ѿ���ˮ��Ϊһ��
}RainState;

//ö�ٶ���
typedef enum Status
{
	SUCCESS, TRUE, FAIL, FALSE, OVERFLOW
}Status;

//��β�����ɫ�ṹ��
typedef struct RainColor RainColor;
typedef struct RainColor *ptrRainColor;

//��νṹ��
typedef struct RainDrop RainDrop;
typedef struct RainDrop *ptrRainDrop;

//�����ṹ��
typedef struct Ripple Ripple;
typedef struct Ripple *ptrRipple;

/*****************************************************************************************
*	Prototype Declare Section
*****************************************************************************************/
Ripple *CreateRipple(void);

RainDrop *CreateRainDrop(void);

/****************************************************************************************
*@Name............: Status SetRainDropColor(RainColor *rainColor)
*@Description.....: ���������ɫ
*@Parameters......: rainColor	:��νṹ��
*@Return values...: SUCCESS		:������β��ϳɹ�
*@PreCondition....����
*@PostCondition...������������һϵ�������ɫ
*****************************************************************************************/
Status SetRainDropColor(RainColor *rainColor);

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
Status SetRainDropAttribute(RainDrop *rainDrop, float windSpeed);

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
Status SetRipple(Ripple *ripple, double widthOfRain, double lengthOfRain);

/****************************************************************************************
*@Name............: void UpdateRippleRadius(Ripple *ripple, double offset)
*@Description.....: ���������뾶
*@Parameters......: ripple	:�����ṹ��
*					offset	:�뾶ƫ����
*@Return values...: ��
*@PreCondition....�����ȸ���������
*@PostCondition...����
*****************************************************************************************/
void UpdateRippleRadius(Ripple *ripple, double offset);

/****************************************************************************************
*@Name............: void UpdateXCoordPoint(RainDrop *rainDrop, float offset)
*@Description.....: �������X����
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
void UpdateXCoordPoint(RainDrop *rainDrop, double offset);

/****************************************************************************************
*@Name............: void UpdateYCoordPoint(RainDrop *rainDrop, double offset)
*@Description.....: �������Y����
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
void UpdateYCoordPoint(RainDrop *rainDrop, double offset);

/****************************************************************************************
*@Name............: void UpdateSlope(RainDrop *rainDrop, float windSpeed)
*@Description.....: ����������б��
*@Parameters......: rainDrop	:��νṹ��
*					windSpeed	:���٣���СֵΪ1.0
*@Return values...: ��
*@PreCondition....����
*@PostCondition...�������ٸı�ʱ��Ҫ�ı�б��
*****************************************************************************************/
void UpdateSlope(RainDrop *rainDrop, float windSpeed);

/****************************************************************************************
*@Name............: double GetXCoordEndPoint(RainDrop *rainDrop)
*@Description.....: ��ȡ����յ��X����
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��һ��x����
*@PreCondition....����֪����ǰ��ε�X����
*@PostCondition...����
*****************************************************************************************/
double GetXCoordEndPoint(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: double GetXCoord(RainDrop *rainDrop)
*@Description.....: ��ȡ���X����
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
double GetXCoord(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: double GetYCoord(RainDrop *rainDrop)
*@Description.....: ��ȡ���Y����
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
double GetYCoord(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: double GetZCoord(RainDrop *rainDrop)
*@Description.....: ��ȡ���Z����
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
double GetZCoord(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: double GetYCoordEndPoint(RainDrop *rainDrop)
*@Description.....: ��ȡ����յ��y����
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��һ��y����
*@PreCondition....����֪����ǰ��ε�Y����
*@PostCondition...����
*****************************************************************************************/
double GetYCoordEndPoint(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: Status IsTouchWater(RainDrop * rainDrop)
*@Description.....: �ж�����Ƿ�����ˮ��
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: TRUE		:��
*					FALSE		:��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
Status IsTouchWater(RainDrop * rainDrop);

//�ж��Ƿ�ﵽ��ߵ�
Status IsBeingHighest(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: double GetWidthOfRainDrop(RainDrop *rainDrop)
*@Description.....: ��ȡ��ο��
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��ο��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
double GetWidthOfRainDrop(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: double GetLengthOfRainDrop(RainDrop *rainDrop)
*@Description.....: ��ȡ��γ���
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��γ���
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
double GetLengthOfRainDrop(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: float* GetRainDropSpecular(RainDrop *rainDrop)
*@Description.....: ��ȡ��ξ�����ɫ
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��ξ�����ɫ����
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
float* GetRainDropSpecular(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: float* GetRainDropDiffuse(RainDrop *rainDrop)
*@Description.....: ��ȡ���ɢ����ɫ
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ���ɢ����ɫ����
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
float* GetRainDropDiffuse(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: float* GetRainDropAmbient(RainDrop *rainDrop)
*@Description.....: ��ȡ��λ�����ɫ
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��λ�����ɫ����
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
float* GetRainDropAmbient(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: float* GetRainDropShininess(RainDrop *rainDrop)
*@Description.....: ��ȡ��ξ�������
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��ξ�������
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
float* GetRainDropShininess(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: RainState GetRainState(RainDrop *rainDrop)
*@Description.....: ��ȡ���״̬
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ���״̬
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
RainState GetRainState(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: void ChangeRainStateToMelting(RainDrop *rainDrop)
*@Description.....: �ı����״̬Ϊ��ˮ״̬
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...���������ˮ��Ӧ�����������ʴ�״̬Ϊ����״̬
*****************************************************************************************/
void ChangeRainStateToMelting(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: void ChangeRainStateToImpacting(RainDrop *rainDrop)
*@Description.....: �ı����״̬Ϊ������Ҷ״̬
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...������������Ҷ��Ӧ���𣬹�Ϊ��ײ��״̬
*****************************************************************************************/
void ChangeRainStateToImpacting(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: void ChangeRainStateToDying(RainDrop *rainDrop)
*@Description.....: �ı����״̬Ϊ����״̬
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...��������ɢ��Ӧ��ʧ���Ӷ�����ɾ������ν��
*****************************************************************************************/
void ChangeRainStateToDying(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: void ChangeRainStateToFalling(RainDrop *rainDrop)
*@Description.....: �ı����״̬Ϊ����״̬
*@Parameters......: rainDrop	:��νṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...���������ײ����Ҷ����������ʱ������
*****************************************************************************************/
void ChangeRainStateToFalling(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: double GetRippleMinRadius(Ripple *ripple)
*@Description.....: ��ȡ���������С�뾶
*@Parameters......: ripple	:�����ṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
double GetRippleMinRadius(Ripple *ripple);

/****************************************************************************************
*@Name............: double GetRippleMaxRadius(Ripple *ripple)
*@Description.....: ��ȡ����������뾶
*@Parameters......: ripple	:�����ṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
double GetRippleMaxRadius(Ripple *ripple);

/****************************************************************************************
*@Name............: double GetCurrentRadius(Ripple *ripple)
*@Description.....: ��ȡ���������ǰ�뾶
*@Parameters......: ripple	:�����ṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
double GetCurrentRadius(Ripple *ripple);

/****************************************************************************************
*@Name............: Status IsRadiusEqualToMax(Ripple *ripple)
*@Description.....: �жϵ�ǰ���������ǰ�뾶�Ƿ񵽴����뾶
*@Parameters......: ripple	:�����ṹ��
*@Return values...: ��
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
Status IsRadiusEqualToMax(Ripple *ripple);

/****************************************************************************************
*@Name............: Status IsInEllipse(RainDrop *rainDrop, double xCoord, double zCoord, double curvature)
*@Description.....: �жϵ�ǰ����Ƿ��ں�Ҷ�ڣ�����Բ�ڣ����ù�ʽ��x-x1)^2/A^2+(y-y1)^2/B^2=1
*@Parameters......: rainDrop	:��νṹ��
*					xCoord		:��Ҷx����
*					zCoord		:��Ҷz����
*					curvature	:��Ҷ������
*@Return values...: TURE		:ȷʵ������
*					FALSE		:��������
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
Status IsInEllipse(RainDrop *rainDrop, double xCoord, double zCoord, double curvature, double radius);
#endif