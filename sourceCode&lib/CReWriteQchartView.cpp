#include "CReWriteQchartView.h"
#include <cmath>
#include "ScheimpflugCamera.h"
//#include <qtextformat.h>
CReWriteQChartView::CReWriteQChartView(QWidget* pParent /*= nullptr*/) :
    QChartView(pParent),
    m_bMiddleButtonPressed(false),
    m_oPrePos(0, 0)
{
    // 创建线
    x_line = new QGraphicsLineItem();
    // 设置颜色
    x_line->setPen(QPen(QColor(100, 100, 100)));
    x_line->setZValue(2);
    y_line = new QGraphicsLineItem();
    y_line->setPen(QPen(QColor(100, 100, 100)));
    y_line->setZValue(2);
    x_y_text = new QGraphicsSimpleTextItem();
    x_y_text->setFont(QFont());
    x_y_text->font().setPointSize(10);
    // 添加到scene中。
    this->scene()->addItem(x_line);
    this->scene()->addItem(y_line);
    this->scene()->addItem(x_y_text);
}

CReWriteQChartViewCamFov::CReWriteQChartViewCamFov(QWidget* pParent /*= nullptr*/) :
    QChartView(pParent),
    m_bMiddleButtonPressed(false),
    m_oPrePos(0, 0)
{
    m_pDownAndLeftPoints = nullptr;
    m_pUpAndRightPoints = nullptr;
    m_pCSchCamParamCal = nullptr;
    // 创建线
    y_line = new QGraphicsLineItem();
    y_line->setPen(QPen(QColor(100, 100, 100)));
    y_line->setZValue(10);
    y_text = new QGraphicsSimpleTextItem();
    y_text->setFont(QFont());
    y_text->font().setPointSize(12);
    x_y_pos_text= new QGraphicsSimpleTextItem();
    x_y_pos_text->setFont(QFont());
    x_y_pos_text->font().setPointSize(12);
    // 添加到scene中。
    this->scene()->addItem(y_line);
    this->scene()->addItem(y_text);
    this->scene()->addItem(x_y_pos_text);
}

CReWriteQChartView::~CReWriteQChartView()
{
    if(y_line)
    {
        delete y_line;
        y_line = nullptr;
    }
    if (x_line)
    {
        delete x_line;
        x_line = nullptr;
    }
    if (x_y_text)
    {
        delete x_y_text;
        x_y_text = nullptr;
    }
}
CReWriteQChartViewCamFov::~CReWriteQChartViewCamFov()
{
    m_pCSchCamParamCal = nullptr;
    m_pDownAndLeftPoints = nullptr;
    m_pUpAndRightPoints = nullptr;

    if (y_line)
    {
        delete y_line;
        y_line = nullptr;
    }
    if (y_text)
    {
        delete y_text;
        y_text = nullptr;
    }
    if (x_y_pos_text)
    {
        delete x_y_pos_text;
        x_y_pos_text = nullptr;
    }
}
// 鼠标移动
void CReWriteQChartView::mouseMoveEvent(QMouseEvent* pEvent)
{
    if (m_bMiddleButtonPressed)
    {
        QPoint oDeltaPos = pEvent->pos() - m_oPrePos;
        this->chart()->scroll(-oDeltaPos.x(), oDeltaPos.y());
        m_oPrePos = pEvent->pos();
    }

    __super::mouseMoveEvent(pEvent);
    // 绘制线
    x_line->setLine(pEvent->x(), 0, pEvent->x(), this->height());
    y_line->setLine(0, pEvent->y(), this->width(), pEvent->y());
    x_y_text->setPos(pEvent->x(), pEvent->y()-14>=0? pEvent->y() - 14: pEvent->y());
    this->chart()->mapToValue(pEvent->pos());
    x_y_text->setText("("+QString::number(this->chart()->mapToValue(pEvent->pos()).x()) + ", " + QString::number(this->chart()->mapToValue(pEvent->pos()).y()) + ")");
    // 把x坐标发出去
    //int nX = this->chart()->mapToValue(pEvent->pos()).x();
    //if (nX != m_oldPosOfX) {
    //    m_oldPosOfX = nX;
    //    emit sendXpos(m_oldPosOfX);
    //}
}

void CReWriteQChartViewCamFov::mouseMoveEvent(QMouseEvent* pEvent)
{
    if (m_pDownAndLeftPoints == nullptr &&  m_pUpAndRightPoints == nullptr)
        return;
    if (m_pCSchCamParamCal == nullptr)
        return;
    double dHeightBottom = m_pUpAndRightPoints->at(0).y();
    double dHeightTop = m_pDownAndLeftPoints->at(1).y();
    double dHeightMiddle = m_pDownAndLeftPoints->at(0).y();
    double dWidthBottom = m_pUpAndRightPoints->at(1).x() - m_pUpAndRightPoints->at(0).x();
    double dWidthTop= m_pDownAndLeftPoints->at(2).x()- m_pDownAndLeftPoints->at(1).x();
    double dWidthMiddle = m_pUpAndRightPoints->at(2).x() - m_pDownAndLeftPoints->at(0).x();
    double width = 0;
    double camFOVwidth = 0;
    if (m_bMiddleButtonPressed)
    {
        QPoint oDeltaPos = pEvent->pos() - m_oPrePos;
        this->chart()->scroll(-oDeltaPos.x(), oDeltaPos.y());
        m_oPrePos = pEvent->pos();
    }
    __super::mouseMoveEvent(pEvent);
    double height = this->chart()->mapToValue(pEvent->pos()).y();
    // 绘制线

    if (m_pCSchCamParamCal->m_dLengthLaserToFovTop >= 0)
    {
        //情况1，2，3
        camFOVwidth = (m_pCSchCamParamCal->m_dCamWidthFovBottom - m_pCSchCamParamCal->m_dCamWidthFovTop)
            / (m_pCSchCamParamCal->m_dHeightMeasurementBottom - m_pCSchCamParamCal->m_dHeightMeasurementTop)
            * (height - m_pCSchCamParamCal->m_dHeightMeasurementTop)
            + m_pCSchCamParamCal->m_dCamWidthFovTop;
    }
    else
    {
        camFOVwidth= (m_pCSchCamParamCal->m_dCamWidthFovBottom - m_pCSchCamParamCal->m_dCamWidthFovTop)
            / (m_pCSchCamParamCal->m_dHeightMeasurementBottom - m_pCSchCamParamCal->m_dHeightMeasurementTop- m_pCSchCamParamCal->m_dLengthLaserToFovTop)
            * (height - m_pCSchCamParamCal->m_dHeightMeasurementTop- m_pCSchCamParamCal->m_dLengthLaserToFovTop)
            + m_pCSchCamParamCal->m_dCamWidthFovTop;
    }

    if (height<dHeightTop || height>dHeightBottom)
    {
        y_line->setLine(0, pEvent->y(), this->width(), pEvent->y());
        y_text->setPos(0,0);
        x_y_pos_text->setPos(0, 0);
        y_text->setText("");
        x_y_pos_text->setText("");
    }
    else if(height>= dHeightTop &&height<=dHeightMiddle)
    {
        y_line->setLine(0, pEvent->y(), this->width(), pEvent->y());
        y_text->setPos(12,12);
        x_y_pos_text->setPos(pEvent->x(), pEvent->y() - 14 >= 0 ? pEvent->y() - 14 : pEvent->y());

        width = dWidthTop + (dWidthMiddle- dWidthTop) * (height - dHeightTop) / (dHeightMiddle- dHeightTop);
        y_text->setText(QString::fromLocal8Bit("垂直高度:     ") + QString::number(height, 'f', 2)
            + QString::fromLocal8Bit("mm \n水平测量范围: ") + QString::number(width, 'f', 2) + QString::fromLocal8Bit("mm \n水平分辨率:   ")
            + QString::number(camFOVwidth /m_pCSchCamParamCal->m_SensorParam.iSensorWidth, 'f', 3) + QString::fromLocal8Bit("mm/px \n垂直分辨率:   ")
            + QString::number(camFOVwidth / m_pCSchCamParamCal->m_SensorParam.iSensorWidth 
                / std::sin(m_pCSchCamParamCal->m_dCamAngle * toRadian), 'f', 3) + "mm/px");
        x_y_pos_text->setText("(" + QString::number(this->chart()->mapToValue(pEvent->pos()).x(), 'f', 2) + ","
            + QString::number(this->chart()->mapToValue(pEvent->pos()).y(), 'f', 2) + ") "
            + QString::fromLocal8Bit("水平范围:") + QString::number(width, 'f', 2) + "mm "
            + QString::fromLocal8Bit("水平Res:") + QString::number(camFOVwidth / m_pCSchCamParamCal->m_SensorParam.iSensorWidth, 'f', 3) + "mm/px "
            + QString::fromLocal8Bit("垂直Res:") + QString::number(camFOVwidth / m_pCSchCamParamCal->m_SensorParam.iSensorWidth
                / std::sin(m_pCSchCamParamCal->m_dCamAngle * toRadian), 'f', 3) + "mm/px ");
    }
    else
    {
        y_line->setLine(0, pEvent->y(), this->width(), pEvent->y());
        y_text->setPos(12, 12);
        x_y_pos_text->setPos(pEvent->x(), pEvent->y() - 16 >= 0 ? pEvent->y() - 16 : pEvent->y());
 
        width = dWidthMiddle + (dWidthBottom- dWidthMiddle) * (height - dHeightMiddle) / (dHeightBottom- dHeightMiddle);
        y_text->setText(QString::fromLocal8Bit("垂直高度:     ") + QString::number(height, 'f', 2)
            + QString::fromLocal8Bit("mm \n水平测量范围: ") + QString::number(width, 'f', 2) + QString::fromLocal8Bit("mm \n水平分辨率:   ")
            + QString::number(camFOVwidth / m_pCSchCamParamCal->m_SensorParam.iSensorWidth, 'f', 3) + QString::fromLocal8Bit("mm/px \n垂直分辨率:   ")
            + QString::number(camFOVwidth / m_pCSchCamParamCal->m_SensorParam.iSensorWidth
                / std::sin(m_pCSchCamParamCal->m_dCamAngle * toRadian), 'f', 3) + "mm/px");
        x_y_pos_text->setText("(" + QString::number(this->chart()->mapToValue(pEvent->pos()).x(), 'f', 2) + ","
            + QString::number(this->chart()->mapToValue(pEvent->pos()).y(), 'f', 2) + ") "
            + QString::fromLocal8Bit("水平范围:") + QString::number(width, 'f', 2) + "mm "
            + QString::fromLocal8Bit("水平Res:") + QString::number(camFOVwidth / m_pCSchCamParamCal->m_SensorParam.iSensorWidth, 'f', 3) + "mm/px "
            + QString::fromLocal8Bit("垂直Res:") + QString::number(camFOVwidth / m_pCSchCamParamCal->m_SensorParam.iSensorWidth
                / std::sin(m_pCSchCamParamCal->m_dCamAngle * toRadian), 'f', 3) + "mm/px ");
    }
}

// 鼠标按键
void CReWriteQChartView::mousePressEvent(QMouseEvent* pEvent)
{

    if (pEvent->button() == Qt::LeftButton)
    {
        m_bMiddleButtonPressed = true;
        m_oPrePos = pEvent->pos();
        this->setCursor(Qt::OpenHandCursor);
    }
    __super::mousePressEvent(pEvent);
}

void CReWriteQChartViewCamFov::mousePressEvent(QMouseEvent* pEvent)
{
    if (m_pDownAndLeftPoints == nullptr &&  m_pUpAndRightPoints == nullptr)
        return;
    if (pEvent->button() == Qt::LeftButton)
    {
        m_bMiddleButtonPressed = true;
        m_oPrePos = pEvent->pos();
        this->setCursor(Qt::OpenHandCursor);
    }
    __super::mousePressEvent(pEvent);
}
// 鼠标抬起
void CReWriteQChartView::mouseReleaseEvent(QMouseEvent* pEvent)
{
    if (pEvent->button() == Qt::LeftButton)
    {
        m_bMiddleButtonPressed = false;
        this->setCursor(Qt::ArrowCursor);
    }
    __super::mouseReleaseEvent(pEvent);
}

void CReWriteQChartViewCamFov::mouseReleaseEvent(QMouseEvent* pEvent)
{
    if (m_pDownAndLeftPoints == nullptr && m_pUpAndRightPoints == nullptr)
        return;
    if (pEvent->button() == Qt::LeftButton)
    {
        m_bMiddleButtonPressed = false;
        this->setCursor(Qt::ArrowCursor);
    }
    __super::mouseReleaseEvent(pEvent);
}

void CReWriteQChartView::wheelEvent(QWheelEvent* pEvent)
{
    qreal rVal = std::pow(0.999, pEvent->delta()); // 设置比例
    // 1. 读取视图基本信息
    QRectF oPlotAreaRect = this->chart()->plotArea();
    QPointF oCenterPoint = oPlotAreaRect.center();
    // 2. 水平调整
    oPlotAreaRect.setWidth(oPlotAreaRect.width() * rVal);
    // 3. 竖直调整
    oPlotAreaRect.setHeight(oPlotAreaRect.height() * rVal);
    // 4.1 计算视点，视点不变，围绕中心缩放
    //QPointF oNewCenterPoint(oCenterPoint);
    // 4.2 计算视点，让鼠标点击的位置移动到窗口中心
    //QPointF oNewCenterPoint(pEvent->pos());
    // 4.3 计算视点，让鼠标点击的位置尽量保持不动(等比换算，存在一点误差)
    QPointF oNewCenterPoint(2 * oCenterPoint - pEvent->pos() - (oCenterPoint - pEvent->pos()) / rVal);
    // 5. 设置视点
    oPlotAreaRect.moveCenter(oNewCenterPoint);
    // 6. 提交缩放调整
    this->chart()->zoomIn(oPlotAreaRect);
    __super::wheelEvent(pEvent);
}

void CReWriteQChartViewCamFov::wheelEvent(QWheelEvent* pEvent)
{
    qreal rVal = std::pow(0.999, pEvent->delta()); // 设置比例
    // 1. 读取视图基本信息
    QRectF oPlotAreaRect = this->chart()->plotArea();
    QPointF oCenterPoint = oPlotAreaRect.center();
    // 2. 水平调整
    oPlotAreaRect.setWidth(oPlotAreaRect.width() * rVal);
    // 3. 竖直调整
    oPlotAreaRect.setHeight(oPlotAreaRect.height() * rVal);
    // 4.1 计算视点，视点不变，围绕中心缩放
    //QPointF oNewCenterPoint(oCenterPoint);
    // 4.2 计算视点，让鼠标点击的位置移动到窗口中心
    //QPointF oNewCenterPoint(pEvent->pos());
    // 4.3 计算视点，让鼠标点击的位置尽量保持不动(等比换算，存在一点误差)
    QPointF oNewCenterPoint(2 * oCenterPoint - pEvent->pos() - (oCenterPoint - pEvent->pos()) / rVal);
    // 5. 设置视点
    oPlotAreaRect.moveCenter(oNewCenterPoint);
    // 6. 提交缩放调整
    this->chart()->zoomIn(oPlotAreaRect);
    __super::wheelEvent(pEvent);
}

void CReWriteQChartViewCamFov::enterEvent(QEvent* pEvent)
{
    if (m_pDownAndLeftPoints && m_pUpAndRightPoints)
    {
        y_line->setVisible(true);
        y_text->setVisible(true);
        x_y_pos_text->setVisible(true);
        __super::enterEvent(pEvent);
    }
}

void CReWriteQChartView::enterEvent(QEvent* pEvent)
{
    x_line->setVisible(true);
    y_line->setVisible(true);
    x_y_text->setVisible(true);
    __super::enterEvent(pEvent);
}

void CReWriteQChartView::leaveEvent(QEvent* pEvent)
{
    x_line->setVisible(false);
    y_line->setVisible(false);
    x_y_text->setVisible(false);
    __super::leaveEvent(pEvent);
}

void CReWriteQChartViewCamFov::leaveEvent(QEvent* pEvent)
{
    y_line->setVisible(false);
    __super::leaveEvent(pEvent);
}