#include "CReWriteQchartView.h"
#include <cmath>
#include "ScheimpflugCamera.h"
//#include <qtextformat.h>
CReWriteQChartView::CReWriteQChartView(QWidget* pParent /*= nullptr*/) :
    QChartView(pParent),
    m_bMiddleButtonPressed(false),
    m_oPrePos(0, 0)
{
    // ������
    x_line = new QGraphicsLineItem();
    // ������ɫ
    x_line->setPen(QPen(QColor(100, 100, 100)));
    x_line->setZValue(2);
    y_line = new QGraphicsLineItem();
    y_line->setPen(QPen(QColor(100, 100, 100)));
    y_line->setZValue(2);
    x_y_text = new QGraphicsSimpleTextItem();
    x_y_text->setFont(QFont());
    x_y_text->font().setPointSize(10);
    // ��ӵ�scene�С�
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
    // ������
    y_line = new QGraphicsLineItem();
    y_line->setPen(QPen(QColor(100, 100, 100)));
    y_line->setZValue(10);
    y_text = new QGraphicsSimpleTextItem();
    y_text->setFont(QFont());
    y_text->font().setPointSize(12);
    x_y_pos_text= new QGraphicsSimpleTextItem();
    x_y_pos_text->setFont(QFont());
    x_y_pos_text->font().setPointSize(12);
    // ��ӵ�scene�С�
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
// ����ƶ�
void CReWriteQChartView::mouseMoveEvent(QMouseEvent* pEvent)
{
    if (m_bMiddleButtonPressed)
    {
        QPoint oDeltaPos = pEvent->pos() - m_oPrePos;
        this->chart()->scroll(-oDeltaPos.x(), oDeltaPos.y());
        m_oPrePos = pEvent->pos();
    }

    __super::mouseMoveEvent(pEvent);
    // ������
    x_line->setLine(pEvent->x(), 0, pEvent->x(), this->height());
    y_line->setLine(0, pEvent->y(), this->width(), pEvent->y());
    x_y_text->setPos(pEvent->x(), pEvent->y()-14>=0? pEvent->y() - 14: pEvent->y());
    this->chart()->mapToValue(pEvent->pos());
    x_y_text->setText("("+QString::number(this->chart()->mapToValue(pEvent->pos()).x()) + ", " + QString::number(this->chart()->mapToValue(pEvent->pos()).y()) + ")");
    // ��x���귢��ȥ
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
    // ������

    if (m_pCSchCamParamCal->m_dLengthLaserToFovTop >= 0)
    {
        //���1��2��3
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
        y_text->setText(QString::fromLocal8Bit("��ֱ�߶�:     ") + QString::number(height, 'f', 2)
            + QString::fromLocal8Bit("mm \nˮƽ������Χ: ") + QString::number(width, 'f', 2) + QString::fromLocal8Bit("mm \nˮƽ�ֱ���:   ")
            + QString::number(camFOVwidth /m_pCSchCamParamCal->m_SensorParam.iSensorWidth, 'f', 3) + QString::fromLocal8Bit("mm/px \n��ֱ�ֱ���:   ")
            + QString::number(camFOVwidth / m_pCSchCamParamCal->m_SensorParam.iSensorWidth 
                / std::sin(m_pCSchCamParamCal->m_dCamAngle * toRadian), 'f', 3) + "mm/px");
        x_y_pos_text->setText("(" + QString::number(this->chart()->mapToValue(pEvent->pos()).x(), 'f', 2) + ","
            + QString::number(this->chart()->mapToValue(pEvent->pos()).y(), 'f', 2) + ") "
            + QString::fromLocal8Bit("ˮƽ��Χ:") + QString::number(width, 'f', 2) + "mm "
            + QString::fromLocal8Bit("ˮƽRes:") + QString::number(camFOVwidth / m_pCSchCamParamCal->m_SensorParam.iSensorWidth, 'f', 3) + "mm/px "
            + QString::fromLocal8Bit("��ֱRes:") + QString::number(camFOVwidth / m_pCSchCamParamCal->m_SensorParam.iSensorWidth
                / std::sin(m_pCSchCamParamCal->m_dCamAngle * toRadian), 'f', 3) + "mm/px ");
    }
    else
    {
        y_line->setLine(0, pEvent->y(), this->width(), pEvent->y());
        y_text->setPos(12, 12);
        x_y_pos_text->setPos(pEvent->x(), pEvent->y() - 16 >= 0 ? pEvent->y() - 16 : pEvent->y());
 
        width = dWidthMiddle + (dWidthBottom- dWidthMiddle) * (height - dHeightMiddle) / (dHeightBottom- dHeightMiddle);
        y_text->setText(QString::fromLocal8Bit("��ֱ�߶�:     ") + QString::number(height, 'f', 2)
            + QString::fromLocal8Bit("mm \nˮƽ������Χ: ") + QString::number(width, 'f', 2) + QString::fromLocal8Bit("mm \nˮƽ�ֱ���:   ")
            + QString::number(camFOVwidth / m_pCSchCamParamCal->m_SensorParam.iSensorWidth, 'f', 3) + QString::fromLocal8Bit("mm/px \n��ֱ�ֱ���:   ")
            + QString::number(camFOVwidth / m_pCSchCamParamCal->m_SensorParam.iSensorWidth
                / std::sin(m_pCSchCamParamCal->m_dCamAngle * toRadian), 'f', 3) + "mm/px");
        x_y_pos_text->setText("(" + QString::number(this->chart()->mapToValue(pEvent->pos()).x(), 'f', 2) + ","
            + QString::number(this->chart()->mapToValue(pEvent->pos()).y(), 'f', 2) + ") "
            + QString::fromLocal8Bit("ˮƽ��Χ:") + QString::number(width, 'f', 2) + "mm "
            + QString::fromLocal8Bit("ˮƽRes:") + QString::number(camFOVwidth / m_pCSchCamParamCal->m_SensorParam.iSensorWidth, 'f', 3) + "mm/px "
            + QString::fromLocal8Bit("��ֱRes:") + QString::number(camFOVwidth / m_pCSchCamParamCal->m_SensorParam.iSensorWidth
                / std::sin(m_pCSchCamParamCal->m_dCamAngle * toRadian), 'f', 3) + "mm/px ");
    }
}

// ��갴��
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
// ���̧��
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
    qreal rVal = std::pow(0.999, pEvent->delta()); // ���ñ���
    // 1. ��ȡ��ͼ������Ϣ
    QRectF oPlotAreaRect = this->chart()->plotArea();
    QPointF oCenterPoint = oPlotAreaRect.center();
    // 2. ˮƽ����
    oPlotAreaRect.setWidth(oPlotAreaRect.width() * rVal);
    // 3. ��ֱ����
    oPlotAreaRect.setHeight(oPlotAreaRect.height() * rVal);
    // 4.1 �����ӵ㣬�ӵ㲻�䣬Χ����������
    //QPointF oNewCenterPoint(oCenterPoint);
    // 4.2 �����ӵ㣬���������λ���ƶ�����������
    //QPointF oNewCenterPoint(pEvent->pos());
    // 4.3 �����ӵ㣬���������λ�þ������ֲ���(�ȱȻ��㣬����һ�����)
    QPointF oNewCenterPoint(2 * oCenterPoint - pEvent->pos() - (oCenterPoint - pEvent->pos()) / rVal);
    // 5. �����ӵ�
    oPlotAreaRect.moveCenter(oNewCenterPoint);
    // 6. �ύ���ŵ���
    this->chart()->zoomIn(oPlotAreaRect);
    __super::wheelEvent(pEvent);
}

void CReWriteQChartViewCamFov::wheelEvent(QWheelEvent* pEvent)
{
    qreal rVal = std::pow(0.999, pEvent->delta()); // ���ñ���
    // 1. ��ȡ��ͼ������Ϣ
    QRectF oPlotAreaRect = this->chart()->plotArea();
    QPointF oCenterPoint = oPlotAreaRect.center();
    // 2. ˮƽ����
    oPlotAreaRect.setWidth(oPlotAreaRect.width() * rVal);
    // 3. ��ֱ����
    oPlotAreaRect.setHeight(oPlotAreaRect.height() * rVal);
    // 4.1 �����ӵ㣬�ӵ㲻�䣬Χ����������
    //QPointF oNewCenterPoint(oCenterPoint);
    // 4.2 �����ӵ㣬���������λ���ƶ�����������
    //QPointF oNewCenterPoint(pEvent->pos());
    // 4.3 �����ӵ㣬���������λ�þ������ֲ���(�ȱȻ��㣬����һ�����)
    QPointF oNewCenterPoint(2 * oCenterPoint - pEvent->pos() - (oCenterPoint - pEvent->pos()) / rVal);
    // 5. �����ӵ�
    oPlotAreaRect.moveCenter(oNewCenterPoint);
    // 6. �ύ���ŵ���
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