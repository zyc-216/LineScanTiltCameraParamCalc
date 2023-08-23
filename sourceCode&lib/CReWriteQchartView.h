#pragma once
#ifndef _CREWRITEQCHARTVIEW_H_
#define _CREWRITEQCHARTVIEW_H_

#include <QtCharts/QChartView>
#include <QObject>
#include <cmath>

QT_CHARTS_USE_NAMESPACE
class CSchCamParamCal;
class PointsSet;
class CReWriteQChartView : public QChartView
{
    Q_OBJECT
public:
    CReWriteQChartView(QWidget* pParent = nullptr);
    ~CReWriteQChartView();
    friend class scheimCamera;
protected:
    virtual void mouseMoveEvent(QMouseEvent* pEvent) override;
    virtual void mousePressEvent(QMouseEvent* pEvent) override;
    virtual void mouseReleaseEvent(QMouseEvent* pEvent) override;
    virtual void wheelEvent(QWheelEvent* pEvent) override;
    virtual void enterEvent(QEvent* pEvent)override;
    virtual void leaveEvent(QEvent* pEvent)override;
private:
    bool m_bMiddleButtonPressed;
    QPoint m_oPrePos;
    QGraphicsLineItem* x_line;
    QGraphicsLineItem* y_line;
    QGraphicsSimpleTextItem* x_y_text;
    int m_oldPosOfX = 0;
    //bool m_bSingleLine = false; //梯形图中只需要一条横线
signals:
};

class CReWriteQChartViewCamFov : public QChartView
{
    Q_OBJECT
public:
    CReWriteQChartViewCamFov(QWidget* pParent = nullptr);
    ~CReWriteQChartViewCamFov();
    friend class scheimCamera;
protected:
    virtual void mouseMoveEvent(QMouseEvent* pEvent) override;
    virtual void mousePressEvent(QMouseEvent* pEvent) override;
    virtual void mouseReleaseEvent(QMouseEvent* pEvent) override;
    virtual void wheelEvent(QWheelEvent* pEvent) override;
    virtual void enterEvent(QEvent* pEvent)override;
    virtual void leaveEvent(QEvent* pEvent)override;
private:
    bool m_bMiddleButtonPressed;
    QPoint m_oPrePos;
    QGraphicsLineItem* y_line;
    QGraphicsSimpleTextItem* y_text;
    QGraphicsSimpleTextItem* x_y_pos_text;
    int m_oldPosOfX = 0;

private:
    QVector<QPointF>* m_pUpAndRightPoints;
    QVector<QPointF>* m_pDownAndLeftPoints;
    CSchCamParamCal* m_pCSchCamParamCal;
    double toRadian = std::acos(-1) / 180;


};


#endif // _CREWRITEQCHARTVIEW_H_
