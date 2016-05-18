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
//雨的四种状态
typedef enum RainState {
	Falling,	//下降过程中
	Melting,	//融于水的过程中
	Impacting,	//与荷叶碰撞
	Dying		//已经和水化为一体
}RainState;

//枚举定义
typedef enum Status
{
	SUCCESS, TRUE, FAIL, FALSE, OVERFLOW
}Status;

//雨滴材料颜色结构体
typedef struct RainColor RainColor;
typedef struct RainColor *ptrRainColor;

//雨滴结构体
typedef struct RainDrop RainDrop;
typedef struct RainDrop *ptrRainDrop;

//涟漪结构体
typedef struct Ripple Ripple;
typedef struct Ripple *ptrRipple;

/*****************************************************************************************
*	Prototype Declare Section
*****************************************************************************************/
Ripple *CreateRipple(void);

RainDrop *CreateRainDrop(void);

/****************************************************************************************
*@Name............: Status SetRainDropColor(RainColor *rainColor)
*@Description.....: 设置雨滴颜色
*@Parameters......: rainColor	:雨滴结构体
*@Return values...: SUCCESS		:设置雨滴材料成功
*@PreCondition....：无
*@PostCondition...：可用于设置一系列雨滴颜色
*****************************************************************************************/
Status SetRainDropColor(RainColor *rainColor);

/****************************************************************************************
*@Name............: Status SetRainDropAttribute(RainDrop *rainDrop, float windSpeed)
*@Description.....: 设置雨滴颜色
*@Parameters......: rainColor	:雨滴结构体
*					wind		:风速，最小为1.0
*@Return values...: SUCCESS		:创建雨滴材料成功
*                   OVERFLOW	:雨滴分配空间失败
*@PreCondition....：无
*@PostCondition...：可用于设置一系列雨滴颜色
*****************************************************************************************/
Status SetRainDropAttribute(RainDrop *rainDrop, float windSpeed);

/****************************************************************************************
*@Name............: Status SetRipple(Ripple *ripple, double widthOfRain, float lengthOfRain)
*@Description.....: 设置涟漪半径
*@Parameters......: ripple		:涟漪结构体
*					widthOfRain	:雨滴的宽度
*					lengthOfRain:雨滴的长度
*@Return values...: SUCCESS		:创建雨滴材料成功
*                   OVERFLOW	:雨滴分配空间失败
*@PreCondition....：雨滴的长度和宽度决定他落水后涟漪的起始半径
*@PostCondition...：可用于设置一系列雨滴半径
*****************************************************************************************/
Status SetRipple(Ripple *ripple, double widthOfRain, double lengthOfRain);

/****************************************************************************************
*@Name............: void UpdateRippleRadius(Ripple *ripple, double offset)
*@Description.....: 更新涟漪半径
*@Parameters......: ripple	:涟漪结构体
*					offset	:半径偏移量
*@Return values...: 无
*@PreCondition....：需先更新轴坐标
*@PostCondition...：无
*****************************************************************************************/
void UpdateRippleRadius(Ripple *ripple, double offset);

/****************************************************************************************
*@Name............: void UpdateXCoordPoint(RainDrop *rainDrop, float offset)
*@Description.....: 更新雨滴X坐标
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
void UpdateXCoordPoint(RainDrop *rainDrop, double offset);

/****************************************************************************************
*@Name............: void UpdateYCoordPoint(RainDrop *rainDrop, double offset)
*@Description.....: 更新雨滴Y坐标
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
void UpdateYCoordPoint(RainDrop *rainDrop, double offset);

/****************************************************************************************
*@Name............: void UpdateSlope(RainDrop *rainDrop, float windSpeed)
*@Description.....: 更新雨滴雨滴斜率
*@Parameters......: rainDrop	:雨滴结构体
*					windSpeed	:风速，最小值为1.0
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：当风速改变时需要改变斜率
*****************************************************************************************/
void UpdateSlope(RainDrop *rainDrop, float windSpeed);

/****************************************************************************************
*@Name............: double GetXCoordEndPoint(RainDrop *rainDrop)
*@Description.....: 获取雨滴终点端X坐标
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 另一端x坐标
*@PreCondition....：需知道当前雨滴的X坐标
*@PostCondition...：无
*****************************************************************************************/
double GetXCoordEndPoint(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: double GetXCoord(RainDrop *rainDrop)
*@Description.....: 获取雨滴X坐标
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
double GetXCoord(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: double GetYCoord(RainDrop *rainDrop)
*@Description.....: 获取雨滴Y坐标
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
double GetYCoord(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: double GetZCoord(RainDrop *rainDrop)
*@Description.....: 获取雨滴Z坐标
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
double GetZCoord(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: double GetYCoordEndPoint(RainDrop *rainDrop)
*@Description.....: 获取雨滴终点端y坐标
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 另一端y坐标
*@PreCondition....：需知道当前雨滴的Y坐标
*@PostCondition...：无
*****************************************************************************************/
double GetYCoordEndPoint(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: Status IsTouchWater(RainDrop * rainDrop)
*@Description.....: 判断雨滴是否碰到水面
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: TRUE		:是
*					FALSE		:否
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
Status IsTouchWater(RainDrop * rainDrop);

//判断是否达到最高点
Status IsBeingHighest(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: double GetWidthOfRainDrop(RainDrop *rainDrop)
*@Description.....: 获取雨滴宽度
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 雨滴宽度
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
double GetWidthOfRainDrop(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: double GetLengthOfRainDrop(RainDrop *rainDrop)
*@Description.....: 获取雨滴长度
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 雨滴长度
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
double GetLengthOfRainDrop(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: float* GetRainDropSpecular(RainDrop *rainDrop)
*@Description.....: 获取雨滴镜面颜色
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 雨滴镜面颜色数组
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
float* GetRainDropSpecular(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: float* GetRainDropDiffuse(RainDrop *rainDrop)
*@Description.....: 获取雨滴散射颜色
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 雨滴散射颜色数组
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
float* GetRainDropDiffuse(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: float* GetRainDropAmbient(RainDrop *rainDrop)
*@Description.....: 获取雨滴环境颜色
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 雨滴环境颜色数组
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
float* GetRainDropAmbient(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: float* GetRainDropShininess(RainDrop *rainDrop)
*@Description.....: 获取雨滴镜面亮度
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 雨滴镜面亮度
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
float* GetRainDropShininess(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: RainState GetRainState(RainDrop *rainDrop)
*@Description.....: 获取雨滴状态
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 雨滴状态
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
RainState GetRainState(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: void ChangeRainStateToMelting(RainDrop *rainDrop)
*@Description.....: 改变雨滴状态为进水状态
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：在雨滴入水后应产生涟漪，故此状态为涟漪状态
*****************************************************************************************/
void ChangeRainStateToMelting(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: void ChangeRainStateToImpacting(RainDrop *rainDrop)
*@Description.....: 改变雨滴状态为触碰荷叶状态
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：在雨碰到荷叶后应溅起，故为碰撞后状态
*****************************************************************************************/
void ChangeRainStateToImpacting(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: void ChangeRainStateToDying(RainDrop *rainDrop)
*@Description.....: 改变雨滴状态为消逝状态
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：涟漪扩散后应消失，从而可以删除该雨滴结点
*****************************************************************************************/
void ChangeRainStateToDying(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: void ChangeRainStateToFalling(RainDrop *rainDrop)
*@Description.....: 改变雨滴状态为下落状态
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：当雨滴碰撞到荷叶反弹到顶点时会下落
*****************************************************************************************/
void ChangeRainStateToFalling(RainDrop *rainDrop);

/****************************************************************************************
*@Name............: double GetRippleMinRadius(Ripple *ripple)
*@Description.....: 获取雨滴涟漪最小半径
*@Parameters......: ripple	:涟漪结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
double GetRippleMinRadius(Ripple *ripple);

/****************************************************************************************
*@Name............: double GetRippleMaxRadius(Ripple *ripple)
*@Description.....: 获取雨滴涟漪最大半径
*@Parameters......: ripple	:涟漪结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
double GetRippleMaxRadius(Ripple *ripple);

/****************************************************************************************
*@Name............: double GetCurrentRadius(Ripple *ripple)
*@Description.....: 获取雨滴涟漪当前半径
*@Parameters......: ripple	:涟漪结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
double GetCurrentRadius(Ripple *ripple);

/****************************************************************************************
*@Name............: Status IsRadiusEqualToMax(Ripple *ripple)
*@Description.....: 判断当前雨滴涟漪当前半径是否到达最大半径
*@Parameters......: ripple	:涟漪结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
Status IsRadiusEqualToMax(Ripple *ripple);

/****************************************************************************************
*@Name............: Status IsInEllipse(RainDrop *rainDrop, double xCoord, double zCoord, double curvature)
*@Description.....: 判断当前雨滴是否在荷叶内，即椭圆内，运用公式（x-x1)^2/A^2+(y-y1)^2/B^2=1
*@Parameters......: rainDrop	:雨滴结构体
*					xCoord		:荷叶x坐标
*					zCoord		:荷叶z坐标
*					curvature	:荷叶的曲率
*@Return values...: TURE		:确实在里面
*					FALSE		:不在里面
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
Status IsInEllipse(RainDrop *rainDrop, double xCoord, double zCoord, double curvature, double radius);
#endif