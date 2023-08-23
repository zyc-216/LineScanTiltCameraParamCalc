#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ScheimpflugCamera.h"
#include "CSchCamParamCalculator.h"
#include <QtCharts/qlineseries.h>
#include <QtCharts/qvalueaxis.h>
#include <QtCharts/qareaseries.h>
#include <qcategoryaxis.h>
#include <qmessagebox.h>
#include <list>
#include "CReadWriteSqliteDB.h"
#include "CReWriteQchartView.h"

class PointsSet
{
public:
    PointsSet() = default;
public:
    int iPointsCountLine=3;
    int iPointsCountFov=2;
    QVector<QPointF> m_PointsForMeasureRange{ iPointsCountLine };
    QVector<QPointF> m_PointsForWidthResolution{ iPointsCountLine };
    QVector<QPointF>   m_PointsForHeightResolution{ iPointsCountLine };
    QVector<QPointF>   m_PointsForHeightWidthResolution{ iPointsCountLine };
    QVector<QPointF> m_PointsUpAndRight{ iPointsCountLine }; //矩形
    QVector<QPointF> m_PointsDownAndLeft{ iPointsCountLine }; //矩形
    QVector<QPointF> m_PointsLaserOrigin{ iPointsCountFov }; //扇形
    QVector<QPointF> m_PointsLaserBottom{ iPointsCountFov }; //扇形
};

typedef struct 
{
    double rangeZMax = DBL_MIN;
    double rangeXMax = DBL_MIN;
    double rangeZMin = DBL_MAX;
    double rangeXMin = DBL_MAX;
    double rangeXMaxResolution = DBL_MIN;
    double rangeXMinResolution = DBL_MAX;
    double rangeZMaxResolution = DBL_MIN;
    double rangeZMinResolution = DBL_MAX;
    double rangeTrapezoidXMax = DBL_MIN;
    double rangeTrapezoidXMin = DBL_MAX;
    double rangeTrapezoidZMax = DBL_MIN;
    double rangeTrapezoidZMin = DBL_MAX;
}RangesMaxAndMin;

typedef struct
{
    QLinearGradient* pGradient;
    bool isCamHidden;
    bool isLaserHidden;
}colorHidden;

typedef struct
{
    int RedDarkLight[7] = { 213,0,0 ,255,90,90,0 };
    int GreenDarkLight[7] = {0,213,0,90,255,90,1 };
    int BlueDarkLight[7] = {0,0,213,90,90,255,2 };
    int YellowDarkLight[7] = {213,213,0,255,255,90,3 };
    int PurpleDarkLight[7] = {213,0,213,255,90,255,4 };
    int CyanineDarkLight[7] = { 0,213,213, 90,255,255,5 };
    //没有被使用为nullptr,被使用为QLinearGradient的地址,false表示使用当前颜色的曲线没有被隐藏
    std::map<int*, colorHidden> colorTaken{ 
        {RedDarkLight,{nullptr,false,false}},
        {GreenDarkLight,{nullptr,false,false}} ,
        {BlueDarkLight,{nullptr,false,false}} ,
        {YellowDarkLight,{nullptr,false,false}} ,
        {PurpleDarkLight,{nullptr,false,false,}} ,
        {CyanineDarkLight,{nullptr,false,false}} };
}colorTable;



class CCalScheCamDataForUI
{
public:
    CCalScheCamDataForUI();
    ~CCalScheCamDataForUI();
    friend scheimCamera;


private:
    void CalOutputParams(int index);
    void CalLinesPoints(int index);
    void CalAreasPoints(int index);
    void UpdatePointsRange();  
    int ApplyRangeNumber(int iNumber);
private:
    std::list<CSchCamParamCal>     m_listCSchCamParamCal;
    std::list<PointsSet>           m_listPointsSet;
    RangesMaxAndMin m_rangesMaxAndMin;
};


class scheimCamera : public QMainWindow
{
    Q_OBJECT
public:
    scheimCamera(QWidget* parent = nullptr);
    ~scheimCamera();
private:
    void pushButtonAdd();
    void pushButtonDelete();
    void pushButtonSave(); //保存到数据库
    void pushButtonLoad(); //从数据库加载
    void pushButtonShowHideCam();
    void pushButtonShowHideLaser();
    void pushButtonRefresh();


    bool isInputParamsValid();
    bool SaveInputParams();
    bool SetInputParams(int index);
    bool GetOutputParams(int index);
    void ShowLinesAndAreas(int index);
    void pushButtonXZClicked();
    void pushButtonXresolutionZClicked();
    void pushButtonZresolutionZClicked();
    void pushButtonXresolutionZresolutionClicked();
    void saveToTemp(int iRow);
    void saveToTemp();
    void pushButtonTrapezoid();
    void flushAxisAndLines(std::list<QLineSeries*>& listpLines, QValueAxis*& axisIndependent, QValueAxis*& axisDependent, QChartView* chartView
                         , double minIndependent, double maxIndependent, double minDependent, double maxDependent);
    void flushAxisAndAreas(std::list<QAreaSeries*>& listpAreaSeries, std::list<QAreaSeries*>& listpAreaSeriesLaser, QValueAxis*& axisIndependent,
        QValueAxis*& axisDependent, QChartView* chartView,
        double minIndependent, double maxIndependent, double minDependent, double maxDependent);
    void DeleteLine(std::list<QLineSeries*>& listLines,std::list<QLineSeries*>::iterator& iterLineToBeDelete,
        QValueAxis*& axisIndependent, QValueAxis*& axisDependent,
                        QChartView* chartView);
    void DeleteArea(std::list<QAreaSeries*>& listAreas, std::list<QAreaSeries*>::iterator& iterAreaToBeDelete,
        QValueAxis*& axisIndependent, QValueAxis*& axisDependent,
        QChartView* chartView);
    void HideLine(std::list<QLineSeries*>::iterator& iterLineToBeHide, QValueAxis*& axisIndependent, QValueAxis*& axisDependent, QChartView* chartView);
    void ShowLine(std::list<QLineSeries*>::iterator& iterLineToBeShow, QValueAxis*& axisIndependent, QValueAxis*& axisDependent, QChartView* chartView);
    void HideArea(std::list<QAreaSeries*>::iterator& iterAreaToBeHide, QValueAxis*& axisIndependent, QValueAxis*& axisDependent, QChartView* chartView);
    void ShowArea(std::list<QAreaSeries*>::iterator& iterAreaToBeShow, QValueAxis*& axisIndependent, QValueAxis*& axisDependent, QChartView* chartView);
    void HideAreaCam(int row);  //隐藏表格中一个方案
    void HideAreaLaser(int row);
private slots:
    void tableWidgetItemClicked(QTableWidgetItem*);
    void tableWidgetItemChanged(QTableWidgetItem*);
    void selectMeasurementLine(const QString& text);
private:
    Ui::scheimCameraClass   ui; 
    CCalScheCamDataForUI m_calScheCamDataForUI;
    colorTable m_colorTable;
    CReadWriteSqliteDB m_readWriteSqliteDB;
    CReadWriteSqliteDB m_readWriteSqliteDBTemp;
    std::string m_strTempDBTableName;
    //Axis
    QValueAxis* m_pAxisXForMeasureRange;
    QValueAxis* m_pAxisZForMeasureRange;
    QValueAxis* m_pAxisZForWidthResolution;
    QValueAxis* m_pAxisWidthResolution;
    QValueAxis* m_pAxisZForHeightResolution;
    QValueAxis* m_pAxisHeightResolution;
    QValueAxis* m_pAxisHeightForHeightWidthResolution;
    QValueAxis* m_pAxisWidthForHeightWidthResolution;
    QValueAxis* m_pAxisXRange; //梯形
    QValueAxis* m_pAxisZRange; //梯形
    //Lines
    std::list<QLineSeries*>   m_listpLineseriesForMeasureRange; 
    std::list<QLineSeries*>   m_listpLineseriesForWidthResolution;
    std::list<QLineSeries*>   m_listpLineseriesForHeightResolution;
    std::list<QLineSeries*>   m_listpLineseriesForHeightWidthResolution;
    std::list<QLineSeries*>   m_listpLineseriesUpAndRight; 
    std::list<QLineSeries*>   m_listpLineseriesDownAndLeft;
    std::list<QLineSeries*>   m_listpLineseriesLaserOrigin;
    std::list<QLineSeries*>   m_listpLineseriesLaserBottom;
    std::list<QAreaSeries*>   m_listpAreaSeries;
    std::list<QAreaSeries*>   m_listpAreaSeriesLaser;
    //渐变调色
    std::list<QLinearGradient*> m_listpAreaLinearGradient;
    std::list<QLinearGradient*> m_listpAreaLaserLinearGradient;
    //PushButtons
    std::list<QPushButton*>     m_listpPushButtonDelete;
    std::list<QPushButton*>     m_listpPushButtonHideShowCam;
    std::list<QPushButton*>     m_listpPushButtonHideShowLaser;
    //messageBox
    QMessageBox::StandardButton m_upTo6MessageBox;  //最多6个方案,添加第7个时弹出
    QMessageBox::StandardButton m_deleteMessageBox;   //删除方案时弹出
    QMessageBox::StandardButton m_saveMessageBox;  //保存所有方案成功后弹出
    //QMessageBox::StandardButton m_selectPathMessageBox;  //选择保存路径，文件名不能为空
private:
    int m_indexColColorID;
    CReWriteQChartView* m_chartXZRange;
    CReWriteQChartViewCamFov* m_chartTrapezoidLine;
    CReWriteQChartView* m_chartXresolutionZ;
    CReWriteQChartView* m_chartZresolutionZ;
    CReWriteQChartView* m_chartXresolutionZresolution;
   // QChartView* ChartXZRange;
};




