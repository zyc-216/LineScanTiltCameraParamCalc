#include "CSchCamParamCalculator.h"
#include <cmath>
CSchCamParamCal::CSchCamParamCal()
{
	m_dLaserWidthAtFovIntersection = 0;
	m_dHeightFovTopToIntersection = 0;
	m_dCamVerticalHeight = 0;
	m_dCamHorizontalOffset = 0;
	m_dCamFovWidthAtLaserOrigin = 0;
	m_dHeightLaserFovIntersection = 0;

}

CSchCamParamCal::~CSchCamParamCal()
{
	//UnInit();
}

bool CSchCamParamCal::Init(void* ptrSensorParam, double dBaseDistance, double dCamAngle, double dFocalLength, double dLaserFanAngle)
{
	bool bRet = false;

	m_SensorParam.dPixelSize = ((SensorParam*)ptrSensorParam)->dPixelSize;
	m_SensorParam.iSensorHeight = ((SensorParam*)ptrSensorParam)->iSensorHeight;
	m_SensorParam.iSensorWidth = ((SensorParam*)ptrSensorParam)->iSensorWidth;
	m_dBaseDistance = dBaseDistance;
	m_dCamAngle = dCamAngle;
	m_dF = dFocalLength;
	m_dLaserFanAngle = dLaserFanAngle;

	double sensorHeightInMm = m_SensorParam.dPixelSize * std::pow(10, -3) * m_SensorParam.iSensorHeight;
	double lengthOpticalToSensorMiddle = m_dF;
	m_dAngleMiddleOpticalSensorTop= std::atan(0.5 * sensorHeightInMm / lengthOpticalToSensorMiddle);

	bRet = true;
	return bRet;
}

bool CSchCamParamCal::Calculate()
{
	bool bRet = false;
	if (!calculateScheimpflugAngle())
	{
		return bRet;
	}
	bRet = calculateFovParam();
	return bRet;
}

//bool CSchCamParamCal::UnInit()
//{
//	bool bRet = false;
//	if (m_pVecDHeightPointSet)
//	{
//		delete m_pVecDHeightPointSet;
//		m_pVecDHeightPointSet = nullptr;
//	}
//	if (m_pVecDWidthPointSet)
//	{
//		delete m_pVecDWidthPointSet;
//		m_pVecDWidthPointSet = nullptr;
//	}
//	bRet = true;
//	return bRet;
//}

bool CSchCamParamCal::calculateScheimpflugAngle()
{
	bool bRet = false;
	double toRadian = std::acos(-1) / 180;
	double lengthOpticalToSensorMiddle = m_dF;//m_DV
	double distanceOpticsScheimpflugIntersection = m_dBaseDistance / std::cos(m_dCamAngle * toRadian);
	//求解一元二次方程，求u和v
	double delta = std::pow(-1 / m_dF, 2) - 4 * std::sin(m_dCamAngle * toRadian) / (m_dF * m_dBaseDistance);
	if (delta < 0) return bRet;
	double x1, x2;
	x1 = (1 / m_dF + std::sqrt(delta)) / (2 * std::sin(m_dCamAngle * toRadian) / (m_dF * m_dBaseDistance));
	x2= (1 / m_dF - std::sqrt(delta)) / (2 * std::sin(m_dCamAngle * toRadian) / (m_dF * m_dBaseDistance));
	if (x1 < 0 || x2 < 0||x1==x2) return bRet;
	if (x1 > x2)
	{
		m_dU = x1;
		m_dV = x2;
	}
	else
	{
		m_dU = x2;
		m_dV = x1;
	}
	m_dScheimpflugAngle = std::atan(lengthOpticalToSensorMiddle / distanceOpticsScheimpflugIntersection) / toRadian;
	//printf("沙姆角：%.5f\n像距：%.5f\n", m_dScheimpflugAngle,m_dV);
	bRet = true;
	return bRet;
}

bool CSchCamParamCal::calculateFovParam()
{
	bool   bRet									= false;
	double angleMiddleOpticalSensorTop			= 0;	//radian
	double anglePerPixelInSensorHeight			= 0;			
	double angleOpticalMeasurementBottomTop		= 0;	
	double angleOpticalMeasurementTopBottom		= 0;	
	double sensorHeightInMm						= m_SensorParam.dPixelSize * std::pow(10, -3) * m_SensorParam.iSensorHeight;
	double sensorWidthInMm						= m_SensorParam.dPixelSize * std::pow(10, -3) * m_SensorParam.iSensorWidth;
	double toRadian								= std::acos(-1) / 180;
	double lengthOpticalToIntersection			= 0;
	double lengthOpticalToSensorMiddle			= m_dF;		// m_dV
	double lengthOpticalToSensorTop				= 0;
	double lengthOpticalToMeasurementMiddle		= 0;		// m_dU;
	double lengthMeasurementHeightUp			= 0;
	double lengthMeasurementHeightDown			= 0;
	double lengthOpticalToMeasurementTop		= 0;
	double lengthOpticalToMeasurementBottom		= 0;
	//double lengthLaserToMeasurementTop			= 0;	//激光器到测量范围最顶端的距离
	double lengthIntersectionToMeasurementTop	= 0;	//三线交汇点到测量范围最顶端的距离
	double lengthIntersectionToLaser			= 0;    //三线交汇点到激光器的距离

	//相机FOV（5种情况通用参数）
	angleMiddleOpticalSensorTop = std::atan(0.5 * sensorHeightInMm / lengthOpticalToSensorMiddle);  //radian
	lengthOpticalToIntersection = lengthOpticalToSensorMiddle / std::sin(m_dScheimpflugAngle * toRadian);
	lengthOpticalToMeasurementMiddle = std::cos((m_dCamAngle + m_dScheimpflugAngle) * toRadian) * lengthOpticalToIntersection 
										/ std::sin(m_dCamAngle * toRadian);
	lengthMeasurementHeightUp = std::sin(angleMiddleOpticalSensorTop) * lengthOpticalToMeasurementMiddle
										/ std::sin(m_dCamAngle * toRadian + angleMiddleOpticalSensorTop);
	lengthMeasurementHeightDown= std::sin(angleMiddleOpticalSensorTop)* lengthOpticalToMeasurementMiddle
										/ std::sin(m_dCamAngle * toRadian - angleMiddleOpticalSensorTop);
	m_dHeightCamFOV = lengthMeasurementHeightUp + lengthMeasurementHeightDown;

	lengthOpticalToMeasurementTop=std::sin(m_dCamAngle*toRadian)* lengthOpticalToMeasurementMiddle
		                                / std::sin(m_dCamAngle * toRadian + angleMiddleOpticalSensorTop);
	lengthOpticalToMeasurementBottom=std::sin(m_dCamAngle * toRadian)* lengthOpticalToMeasurementMiddle
										/ std::sin(m_dCamAngle * toRadian - angleMiddleOpticalSensorTop);
	m_dCamWidthFovTop = lengthOpticalToMeasurementTop * sensorWidthInMm
								/ (0.5 * sensorHeightInMm / std::sin(angleMiddleOpticalSensorTop));
	m_dCamWidthFovBottom =lengthOpticalToMeasurementBottom * sensorWidthInMm
								/ (0.5 * sensorHeightInMm / std::sin(angleMiddleOpticalSensorTop));
	
	//激光器参数（5种情况通用）
	lengthIntersectionToLaser = m_dBaseDistance * std::tan(m_dCamAngle * toRadian);
	lengthOpticalToSensorTop = lengthOpticalToSensorMiddle / std::cos(angleMiddleOpticalSensorTop);
	lengthIntersectionToMeasurementTop = std::cos(angleMiddleOpticalSensorTop)
		* (lengthOpticalToSensorTop + lengthOpticalToMeasurementTop)
		/ std::cos(m_dCamAngle * toRadian);

	//激光器参数（不通用）
	m_dLengthLaserToFovTop = lengthIntersectionToMeasurementTop - lengthIntersectionToLaser;
	if(m_dLengthLaserToFovTop>=0){ 
		//情况1，2，3
	}
	else {
		//
	}
	m_dLaserWidthAtFovTop = 2 * std::tan(m_dLaserFanAngle / 2 * toRadian) * m_dLengthLaserToFovTop;
	//激光器参数（通用）
	m_dLengthLaserToFovBottom = m_dLengthLaserToFovTop + m_dHeightCamFOV;
	m_dLaserWidthFovBottom = 2 * std::tan(m_dLaserFanAngle / 2 * toRadian) * m_dLengthLaserToFovBottom;


	//相机和激光器范围
	if (m_dLaserWidthAtFovTop > 0&& m_dLaserWidthAtFovTop < m_dCamWidthFovTop&& m_dLaserWidthFovBottom>=m_dCamWidthFovBottom)  //激光范围上短下长
	{
		LaserCamFov = LaserIntersectCam;
		m_dHeightFovTopToIntersection = (m_dCamWidthFovTop - m_dLaserWidthAtFovTop) * m_dHeightCamFOV
			/ (m_dCamWidthFovTop - m_dLaserWidthAtFovTop + m_dLaserWidthFovBottom - m_dCamWidthFovBottom);
		m_dLaserWidthAtFovIntersection = 2 * std::tan(m_dLaserFanAngle / 2 * toRadian) * (m_dLengthLaserToFovTop + m_dHeightFovTopToIntersection);
		m_dMinWidthMeasurement = m_dLaserWidthAtFovTop;
		m_dMaxWidthMeasurement = m_dCamWidthFovBottom;
		m_dHeightMeasure = m_dHeightCamFOV;
		m_dHeightMeasurementTop = m_dLengthLaserToFovTop + m_dCamVerticalHeight;
		m_dHeightMeasurementBottom = m_dHeightMeasurementTop + m_dHeightMeasure;
		m_dHeightLaserFovIntersection = m_dHeightMeasurementTop + m_dHeightFovTopToIntersection;
	}
	else if(m_dLaserWidthAtFovTop >= m_dCamWidthFovTop && m_dLaserWidthFovBottom >= m_dCamWidthFovBottom) //激光范围覆盖相机fov
	{ 
		LaserCamFov = LaserFullOverCam;
		m_dLaserWidthAtFovIntersection = 0;
		m_dMinWidthMeasurement = m_dCamWidthFovTop;
		m_dMaxWidthMeasurement = m_dCamWidthFovBottom;
		m_dHeightMeasure = m_dHeightCamFOV;
		m_dHeightMeasurementTop = m_dLengthLaserToFovTop + m_dCamVerticalHeight;
		m_dHeightMeasurementBottom = m_dHeightMeasurementTop + m_dHeightMeasure;
	}
	else if (m_dLaserWidthAtFovTop>0 && m_dLaserWidthAtFovTop < m_dCamWidthFovTop && m_dLaserWidthFovBottom < m_dCamWidthFovBottom) //激光范围完全被相机fov覆盖
	{
		LaserCamFov = CamFullOverLaser;
		m_dLaserWidthAtFovIntersection = 0;
		m_dMinWidthMeasurement = m_dLaserWidthAtFovTop;
		m_dMaxWidthMeasurement = m_dLaserWidthFovBottom;
		m_dHeightMeasure = m_dHeightCamFOV;
		m_dHeightMeasurementTop = m_dLengthLaserToFovTop + m_dCamVerticalHeight;
		m_dHeightMeasurementBottom = m_dHeightMeasurementTop + m_dHeightMeasure;
	}
	else if (m_dLaserWidthAtFovTop <= 0 && m_dLaserWidthFovBottom >0 && m_dLaserWidthFovBottom < m_dCamWidthFovBottom)
	{
		LaserCamFov = CamTiltTooMuchAndFullOverLaser;
		m_dLaserWidthAtFovIntersection = 0;
		m_dCamFovWidthAtLaserOrigin = m_dCamWidthFovTop * (1 - m_dLengthLaserToFovTop * (m_dCamWidthFovBottom - m_dCamWidthFovTop) / m_dHeightCamFOV
			/ m_dCamWidthFovTop);
		m_dMinWidthMeasurement = 0;
		m_dMaxWidthMeasurement = m_dLaserWidthFovBottom;
		m_dHeightMeasure = m_dLengthLaserToFovBottom;
		m_dHeightMeasurementTop = 0+m_dCamVerticalHeight;
		m_dHeightMeasurementBottom = m_dHeightMeasurementTop + m_dHeightMeasure;
	}
	else if (m_dLaserWidthAtFovTop <= 0 && m_dLaserWidthFovBottom >= m_dCamWidthFovBottom)
	{
		LaserCamFov = CamTiltTooMuchAndIntersect;
		m_dLaserWidthAtFovIntersection = (-m_dLengthLaserToFovTop*(m_dCamWidthFovBottom-m_dCamWidthFovTop)
			+m_dHeightCamFOV*m_dWidthResolutionFovTop)
			/(2*std::tan(m_dLaserFanAngle/2*toRadian)*m_dHeightCamFOV+m_dCamWidthFovTop- m_dCamWidthFovBottom);
		m_dCamFovWidthAtLaserOrigin = m_dCamWidthFovTop * (1 - m_dLengthLaserToFovTop * (m_dCamWidthFovBottom - m_dCamWidthFovTop) / m_dHeightCamFOV
			/ m_dCamWidthFovTop);
		m_dMinWidthMeasurement = 0;
		m_dMaxWidthMeasurement = m_dCamWidthFovBottom;
		m_dHeightMeasure = m_dLengthLaserToFovBottom;
		m_dHeightMeasurementTop = 0 + m_dCamVerticalHeight;
		m_dHeightMeasurementBottom = m_dHeightMeasurementTop + m_dHeightMeasure;
		m_dHeightLaserFovIntersection = m_dLaserWidthAtFovIntersection/2/std::tan(m_dLaserFanAngle/2*toRadian)
										+m_dCamVerticalHeight;
	}
	/*计算精度*/
	if (LaserIntersectCam == LaserCamFov || LaserFullOverCam == LaserCamFov || CamFullOverLaser == LaserCamFov)
	{
		// 水平
		m_dWidthResolutionFovTop = m_dCamWidthFovTop / m_SensorParam.iSensorWidth;
		m_dWidthResolutionFovBottom = m_dCamWidthFovBottom / m_SensorParam.iSensorWidth;
		// 垂直
		m_dHeightResolutionFovTop = m_dWidthResolutionFovTop / std::sin(m_dCamAngle * toRadian);
		m_dHeightResolutionFovBottom = m_dWidthResolutionFovBottom / std::sin(m_dCamAngle * toRadian);
	}
	else
	{
		//水平
		m_dWidthResolutionFovTop= m_dCamFovWidthAtLaserOrigin / m_SensorParam.iSensorWidth;
		m_dWidthResolutionFovBottom = m_dCamWidthFovBottom / m_SensorParam.iSensorWidth;
		//垂直
		m_dHeightResolutionFovTop = m_dWidthResolutionFovTop / std::sin(m_dCamAngle * toRadian);
		m_dHeightResolutionFovBottom = m_dWidthResolutionFovBottom / std::sin(m_dCamAngle * toRadian);
	}
	

	bRet = true;
	return bRet;
}

