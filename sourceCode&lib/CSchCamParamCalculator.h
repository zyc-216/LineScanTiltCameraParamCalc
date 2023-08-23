#pragma once
#ifndef _CSchCamParamCalculator_H_
#define _CSchCamParamCalculator_H_

#include <vector>
enum fovEnum
{
	InitalStatus =-1,
	LaserFullOverCam = 0,  //�������η�Χ��ȫ�������FOV  
	LaserIntersectCam=1,	//����
	CamFullOverLaser=2,		//���FOV��ȫ���Ǽ������η�Χ
	//�����ǹ����˷�����˵�fov
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
	/*sick:���������߾�����ͷ���ĵ�*/
	bool calculateScheimpflugAngle();  
	bool calculateFovParam();


private:
	friend class CCalScheCamDataForUI;
	friend class scheimCamera;
	typedef struct
	{
		double  dPixelSize;   //��m=10^-3mm
		int		iSensorWidth;
		int		iSensorHeight;

	}SensorParam;
	/*input params*/
	SensorParam m_SensorParam;
	double		m_dBaseDistance;				// ��Ŀ�߽ṹ��������� mm
	double		m_dCamAngle;					// �����ǣ��㣩
	double		m_dF;							// ��ͷ���� mm
	double		m_dLaserFanAngle;				// �������Ƚ�

	/*output params*/
	double		m_dU;							// ��� mm
	double		m_dV;							// ��� mm
	double		m_dScheimpflugAngle;			// ɳķ�ǣ��㣩
	double		m_dMinWidthMeasurement;			// ����ˮƽ������Χ mm
	double		m_dMaxWidthMeasurement;			// Զ��ˮƽ������Χ mm
	double		m_dHeightMeasure;				// �߶Ȳ�����Χ    mm
	double		m_dHeightMeasurementTop;
	double		m_dHeightMeasurementBottom;
	double		m_dWidthResolutionFovTop;		// ����ˮƽ���򾫶� mm/px
	double		m_dWidthResolutionFovBottom;	// Զ��ˮƽ���򾫶� mm/px
	double		m_dHeightResolutionFovTop;		// ���˴�ֱ���򾫶� mm/px
	double		m_dHeightResolutionFovBottom;	// Զ�˴�ֱ���򾫶� mm/px
	double		m_dHeightCamFOV;
private:
	/*Qt�����õ��Ĳ���*/
	double m_dLengthLaserToFovTop;
	double m_dLengthLaserToFovBottom;
	double m_dLengthLaserToMeasurementTop;
	double m_dAngleMiddleOpticalSensorTop;
	double m_dLaserWidthAtFovTop;
	double m_dLaserWidthFovBottom;	
	double m_dLaserWidthAtFovIntersection;		//���ⷶΧ��fov�϶��³�ʱ��Ϊ�㣬��ȫ��fov���ǻ�����ȫ����fovʱΪ0
	double m_dHeightLaserFovIntersection;		//���ⷶΧ��fov�϶��³�ʱ�͵��������ʱ��Ϊ�㣬��ȫ��fov���ǻ�����ȫ����fovʱΪ0
	double m_dCamWidthFovTop;
	double m_dCamWidthFovBottom;
	double m_dHeightFovTopToIntersection;
	double m_dCamVerticalHeight;                // �����װ�߶�
	double m_dCamHorizontalOffset;				// ���ˮƽƫ��
	double m_dCamFovWidthAtLaserOrigin;			// ֻ�ڵ�4��5������²�Ϊ��
	int	   LaserCamFov = InitalStatus;
};
#endif // !_CSchCamParamCalculator_H_
