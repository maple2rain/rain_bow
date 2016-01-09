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
//雨滴材料颜色结构体
struct RainColor {
	float ambient[4];	//雨滴环境颜色
	float diffuse[4];	//雨滴散射颜色
	float specular[4];	//雨滴镜面颜色
	float shininess[1];	//雨滴镜面指数
};

//雨滴结构体
struct RainDrop {
	double xCoord;			//x坐标
	double yCoord;			//y坐标
	double zCoord;			//z坐标
	double xEndCoord;		//x终点坐标
	double yEndCoord;		//y终点坐标
	double b;				//增量b， 由 x = ky + b得出
	double lengthOfRain;	//雨滴长度
	double widthOfRain;		//雨滴宽度
	double slope;			//雨滴斜率
	RainColor rainColor;	//雨滴颜色
	RainState rainState;	//雨滴状态
};

//涟漪结构体
struct Ripple {
	double radius;		//涟漪当前半径
	double minRadius;	//涟漪最小半径
	double maxRadius;	//涟漪最大半径
						//涟漪的颜色即为雨滴的颜色
};

/****************************************************************************************
*	Function Define Section
****************************************************************************************/

/****************************************************************************************
*@Name............: Status SetRainDropColor(RainColor *rainColor)
*@Description.....: 设置雨滴颜色
*@Parameters......: rainColor	:雨滴结构体
*@Return values...: SUCCESS		:设置雨滴材料成功
*@PreCondition....：无
*@PostCondition...：可用于设置一系列雨滴颜色
*****************************************************************************************/
Status SetRainDropColor(RainColor *rainColor)
{
	/*
	**随机设置材料颜色
	*/
	for (int i = 0; i < 4; ++i)
	{
		rainColor->ambient[i] = (float)((rand() % 1000 * 0.001));
		rainColor->diffuse[i] = (float)((rand() % 1000 * 0.001));
		rainColor->specular[i] = (float)((rand() % 1000 * 0.001));
	}

	rainColor->shininess[0] = 0.8 + (float)(1.0 / (rand() % 5 + 1));//随机设置镜面指数

	return SUCCESS;
}

/****************************************************************************************
*@Name............: RainDrop *CreateRainDrop(void)
*@Description.....: 创建雨滴结构体
*@Parameters......: 无
*@Return values...: 雨滴结构体指针
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
RainDrop *CreateRainDrop(void)
{
	return (RainDrop*)malloc(sizeof(RainDrop));
}

/****************************************************************************************
*@Name............: Ripple *CreateRipple(void)
*@Description.....: 创建涟漪结构体
*@Parameters......: 无
*@Return values...: 雨滴结构体指针
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
Ripple *CreateRipple(void)
{
	return (Ripple*)malloc(sizeof(Ripple));
}

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
Status SetRainDropAttribute(RainDrop *rainDrop, float windSpeed)
{
	/*
	**设置雨滴属性值
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
	
	SetRainDropColor(&rainDrop->rainColor);//设置颜色

	return SUCCESS;
}

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
Status SetRipple(Ripple *ripple, double widthOfRain, double lengthOfRain)
{
	//设置涟漪最小及最大半径
	ripple->minRadius = (int)(widthOfRain + lengthOfRain) % 3 + 0.5;
	ripple->maxRadius = ripple->minRadius + 4;
	ripple->radius = ripple->minRadius;

	return SUCCESS;
}

/****************************************************************************************
*@Name............: void UpdateRippleRadius(Ripple *ripple, double offset)
*@Description.....: 更新涟漪半径
*@Parameters......: ripple	:涟漪结构体
*					offset	:半径偏移量
*@Return values...: 无
*@PreCondition....：需先更新轴坐标
*@PostCondition...：无
*****************************************************************************************/
void UpdateRippleRadius(Ripple *ripple, double offset)
{
	ripple->radius += offset;
}

/****************************************************************************************
*@Name............: void UpdateXCoordPoint(RainDrop *rainDrop, double offset)
*@Description.....: 更新雨滴X坐标
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 无
*@PreCondition....：需先更新轴坐标
*@PostCondition...：无
*****************************************************************************************/
void UpdateXCoordPoint(RainDrop *rainDrop, double offset)
{
	rainDrop->xCoord = rainDrop->yCoord * rainDrop->slope + rainDrop->b;
	rainDrop->xEndCoord = rainDrop->yEndCoord * rainDrop->slope + rainDrop->b;
}

/****************************************************************************************
*@Name............: void UpdateSlope(RainDrop *rainDrop, float windSpeed)
*@Description.....: 更新雨滴雨滴斜率
*@Parameters......: rainDrop	:雨滴结构体
*					windSpeed	:风速，最小值为1.0
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：当风速改变时需要改变斜率
*****************************************************************************************/
void UpdateSlope(RainDrop *rainDrop, float windSpeed)
{
	rainDrop->slope = windSpeed;
}

/****************************************************************************************
*@Name............: void UpdateYCoordPoint(RainDrop *rainDrop, double offset)
*@Description.....: 更新雨滴Y坐标
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
void UpdateYCoordPoint(RainDrop *rainDrop, double offset)
{
	rainDrop->yCoord -= offset;
	rainDrop->yEndCoord -= offset;
}

/****************************************************************************************
*@Name............: double GetXCoord(RainDrop *rainDrop) 
*@Description.....: 获取雨滴X坐标
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
double GetXCoord(RainDrop *rainDrop) 
{
	return rainDrop->xCoord;
}

/****************************************************************************************
*@Name............: double GetYCoord(RainDrop *rainDrop)
*@Description.....: 获取雨滴Y坐标
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
double GetYCoord(RainDrop *rainDrop)
{
	return rainDrop->yCoord;
}

/****************************************************************************************
*@Name............: double GetZCoord(RainDrop *rainDrop)
*@Description.....: 获取雨滴Z坐标
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
double GetZCoord(RainDrop *rainDrop)
{
	return rainDrop->zCoord;
}

/****************************************************************************************
*@Name............: double GetXCoordEndPoint(RainDrop *rainDrop)
*@Description.....: 获取雨滴终点端X坐标
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 另一端x坐标
*@PreCondition....：需知道当前雨滴的X坐标
*@PostCondition...：无
*****************************************************************************************/
double GetXCoordEndPoint(RainDrop *rainDrop)
{
	return rainDrop->xEndCoord;
}

/****************************************************************************************
*@Name............: double GetYCoordEndPoint(RainDrop *rainDrop)
*@Description.....: 获取雨滴终点端y坐标
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 另一端y坐标
*@PreCondition....：需知道当前雨滴的Y坐标
*@PostCondition...：无
*****************************************************************************************/
double GetYCoordEndPoint(RainDrop *rainDrop)
{
	return rainDrop->yEndCoord;
}

/****************************************************************************************
*@Name............: Status IsTouchWater(RainDrop * rainDrop)
*@Description.....: 判断雨滴是否碰到水面
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: TRUE		:是
*					FALSE		:否
*@PreCondition....：无
*@PostCondition...：无
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
*@Description.....: 获取雨滴宽度
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 雨滴宽度
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
double GetWidthOfRainDrop(RainDrop *rainDrop)
{
	return rainDrop->widthOfRain;
}

/****************************************************************************************
*@Name............: float* GetRainDropSpecular(RainDrop *rainDrop)
*@Description.....: 获取雨滴镜面颜色
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 雨滴镜面颜色数组
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
float* GetRainDropSpecular(RainDrop *rainDrop)
{
	return rainDrop->rainColor.specular;
}

/****************************************************************************************
*@Name............: float* GetRainDropDiffuse(RainDrop *rainDrop)
*@Description.....: 获取雨滴散射颜色
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 雨滴散射颜色数组
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
float* GetRainDropDiffuse(RainDrop *rainDrop)
{
	return rainDrop->rainColor.diffuse;
}

/****************************************************************************************
*@Name............: float* GetRainDropAmbient(RainDrop *rainDrop)
*@Description.....: 获取雨滴环境颜色
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 雨滴环境颜色数组
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
float* GetRainDropAmbient(RainDrop *rainDrop)
{
	return rainDrop->rainColor.ambient;
}

/****************************************************************************************
*@Name............: float* GetRainDropShininess(RainDrop *rainDrop)
*@Description.....: 获取雨滴镜面亮度
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 雨滴镜面亮度
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
float* GetRainDropShininess(RainDrop *rainDrop)
{
	return rainDrop->rainColor.shininess;
}

/****************************************************************************************
*@Name............: double GetLengthOfRainDrop(RainDrop *rainDrop)
*@Description.....: 获取雨滴长度
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 雨滴长度
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
double GetLengthOfRainDrop(RainDrop *rainDrop)
{
	return rainDrop->lengthOfRain;
}

/****************************************************************************************
*@Name............: RainState GetRainState(RainDrop *rainDrop)
*@Description.....: 获取雨滴状态
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 雨滴状态
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
RainState GetRainState(RainDrop *rainDrop)
{
	return rainDrop->rainState;
}

/****************************************************************************************
*@Name............: void ChangeRainStateToMelting(RainDrop *rainDrop)
*@Description.....: 改变雨滴状态为进水状态
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：在雨滴入水后应产生涟漪，故此状态为涟漪状态
*****************************************************************************************/
void ChangeRainStateToMelting(RainDrop *rainDrop)
{
	rainDrop->rainState = Melting;
}

/****************************************************************************************
*@Name............: void ChangeRainStateToDying(RainDrop *rainDrop)
*@Description.....: 改变雨滴状态为消逝状态
*@Parameters......: rainDrop	:雨滴结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：涟漪扩散后应消失，从而可以删除该雨滴结点
*****************************************************************************************/
void ChangeRainStateToDying(RainDrop *rainDrop)
{
	rainDrop->rainState = Dying;
}

/****************************************************************************************
*@Name............: double GetRippleMinRadius(Ripple *ripple)
*@Description.....: 获取雨滴涟漪最小半径
*@Parameters......: ripple	:涟漪结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
double GetRippleMinRadius(Ripple *ripple)
{
	return ripple->minRadius;
}

/****************************************************************************************
*@Name............: double GetRippleMaxRadius(Ripple *ripple)
*@Description.....: 获取雨滴涟漪最大半径
*@Parameters......: ripple	:涟漪结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
double GetRippleMaxRadius(Ripple *ripple)
{
	return ripple->maxRadius;
}

/****************************************************************************************
*@Name............: double GetCurrentRadius(Ripple *ripple)
*@Description.....: 获取雨滴涟漪当前半径
*@Parameters......: ripple	:涟漪结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
double GetCurrentRadius(Ripple *ripple)
{
	return ripple->radius;
}

/****************************************************************************************
*@Name............: Status IsRadiusEqualToMax(Ripple *ripple)
*@Description.....: 判断当前雨滴涟漪当前半径是否到达最大半径
*@Parameters......: ripple	:涟漪结构体
*@Return values...: 无
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
Status IsRadiusEqualToMax(Ripple *ripple)
{
	if (ripple->maxRadius <= ripple->radius)
		return TRUE;
	else
		return FALSE;
}