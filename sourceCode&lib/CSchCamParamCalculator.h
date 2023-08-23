#pragma once
#ifndef _CSchCamParamCalculator_H_
#define _CSchCamParamCalculator_H_

#include <vector>
enum fovEnum
{
	InitalStatus =-1,
	LaserFullOverCam = 0,  //激光扇形范围完全覆盖相机FOV  
	LaserIntersectCam=1,	//交叉
	CamFullOverLaser=2,		//相机FOV完全覆盖激光扇形范围
	//相机倾角过大，浪费最近端的fov
	CamTiltTooMuchAndFullOverLaser=3,  
	CamTiltTooMuchAndIntersect = 4
};

class CReWriteQChartViewCamFov;
class CSchCamParamCal
{
public:
	CSchCamParamCal();
	~CSchCamParamCal();
	friend class CReWriteQChartViewCamFov;
	bool Init(void* ptrSensorParam, double dBaseDistance,  double dCamAngle, 
						double dFocalLength, double dLaserFanAngle);
	bool Calculate();
	//bool UnInit();

private:
	/*sick:传感器垂线经过镜头中心点*/
	bool calculateScheimpflugAngle();  
	bool calculateFovParam();


private:
	friend class CCalScheCamDataForUI;
	friend class scheimCamera;
	typedef struct
	{
		double  dPixelSize;   //μm=10^-3mm
		int		iSensorWidth;
		int		iSensorHeight;

	}SensorParam;
	/*input params*/
	SensorParam m_SensorParam;
	double		m_dBaseDistance;				// 单目线结构光相机基距 mm
	double		m_dCamAngle;					// 相机倾角（°）
	double		m_dF;							// 镜头焦距 mm
	double		m_dLaserFanAngle;				// 激光器扇角

	/*output params*/
	double		m_dU;							// 物距 mm
	double		m_dV;							// 像距 mm
	double		m_dScheimpflugAngle;			// 沙姆角（°）
	double		m_dMinWidthMeasurement;			// 近端水平测量范围 mm
	double		m_dMaxWidthMeasurement;			// 远端水平测量范围 mm
	double		m_dHeightMeasure;				// 高度测量范围    mm
	double		m_dHeightMeasurementTop;
	double		m_dHeightMeasurementBottom;
	double		m_dWidthResolutionFovTop;		// 近端水平方向精度 mm/px
	double		m_dWidthResolutionFovBottom;	// 远端水平方向精度 mm/px
	double		m_dHeightResolutionFovTop;		// 近端垂直方向精度 mm/px
	double		m_dHeightResolutionFovBottom;	// 远端垂直方向精度 mm/px
	double		m_dHeightCamFOV;
private:
	/*Qt程序用到的参数*/
	double m_dLengthLaserToFovTop;
	double m_dLengthLaserToFovBottom;
	double m_dLengthLaserToMeasurementTop;
	double m_dAngleMiddleOpticalSensorTop;
	double m_dLaserWidthAtFovTop;
	double m_dLaserWidthFovBottom;	
	double m_dLaserWidthAtFovIntersection;		//激光范围在fov上短下长时不为零，完全被fov覆盖或者完全覆盖fov时为0
	double m_dHeightLaserFovIntersection;		//激光范围在fov上短下长时和第五种情况时不为零，完全被fov覆盖或者完全覆盖fov时为0
	double m_dCamWidthFovTop;
	double m_dCamWidthFovBottom;
	double m_dHeightFovTopToIntersection;
	double m_dCamVerticalHeight;                // 相机安装高度
	double m_dCamHorizontalOffset;				// 相机水平偏移
	double m_dCamFovWidthAtLaserOrigin;			// 只在第4，5种情况下不为零
	int	   LaserCamFov = InitalStatus;
};
#endif // !_CSchCamParamCalculator_H_
