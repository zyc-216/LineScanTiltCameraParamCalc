#include "ScheimpflugCamera.h"
#include <cmath>
#include <qfiledialog.h>
#include <QFileInfo>
#define RELEASE_PTR(ptr)    \
    if (ptr)                \
    {                       \
        delete ptr;         \
        ptr = nullptr;      \
    }                       \


scheimCamera::scheimCamera(QWidget * parent)
    : QMainWindow(parent)
{
    QColor qcolor;
    QFont qfont;
    qcolor.setRgb(255, 0, 0);
    qfont.setPointSize(9);
    ui.setupUi(this);
    //chart XZRange
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_chartXZRange = new CReWriteQChartView(ui.page);
    m_chartXZRange->setObjectName(QString::fromUtf8("ChartXZRange"));
    sizePolicy.setHeightForWidth(m_chartXZRange->sizePolicy().hasHeightForWidth());
    m_chartXZRange->setSizePolicy(sizePolicy);
    m_chartXZRange->setMinimumSize(QSize(200, 0));
    ui.gridLayout_9->addWidget(m_chartXZRange, 0, 0, 1, 1);
    //chart 梯形
    m_chartTrapezoidLine = new CReWriteQChartViewCamFov(ui.page_5);
    m_chartTrapezoidLine->setObjectName(QString::fromUtf8("ChartTrapezoidLine"));
    sizePolicy.setHeightForWidth(m_chartTrapezoidLine->sizePolicy().hasHeightForWidth());
    m_chartTrapezoidLine->setSizePolicy(sizePolicy);
    ui.gridLayout_8->addWidget(m_chartTrapezoidLine, 0, 0, 1, 1);

    //chart Xresolution-Z
    m_chartXresolutionZ = new CReWriteQChartView(ui.page_2);
    m_chartXresolutionZ->setObjectName(QString::fromUtf8("ChartXresolutionZ"));
    sizePolicy.setHeightForWidth(m_chartXresolutionZ->sizePolicy().hasHeightForWidth());
    m_chartXresolutionZ->setSizePolicy(sizePolicy);
    ui.gridLayout_5->addWidget(m_chartXresolutionZ, 0, 0, 1, 1);
    //chart Zresolution-Z
    m_chartZresolutionZ = new CReWriteQChartView(ui.page_3);
    m_chartZresolutionZ->setObjectName(QString::fromUtf8("ChartZresolutionZ"));
    sizePolicy.setHeightForWidth(m_chartZresolutionZ->sizePolicy().hasHeightForWidth());
    m_chartZresolutionZ->setSizePolicy(sizePolicy);
    ui.gridLayout_6->addWidget(m_chartZresolutionZ, 0, 0, 1, 1);
    //chart Xresolution-Zresolution
    m_chartXresolutionZresolution = new CReWriteQChartView(ui.page_4);
    m_chartXresolutionZresolution->setObjectName(QString::fromUtf8("ChartXresolutionZresolution"));
    sizePolicy.setHeightForWidth(m_chartXresolutionZresolution->sizePolicy().hasHeightForWidth());
    m_chartXresolutionZresolution->setSizePolicy(sizePolicy);
    ui.gridLayout_7->addWidget(m_chartXresolutionZresolution, 0, 0, 1, 1);
   
    
    
    m_indexColColorID = ui.tableWidget->columnCount() - 1;
    this->resize(1800, 900);
    ui.stackedWidget->setCurrentIndex(4);
    //抗锯齿
    m_chartXZRange->setRenderHint(QPainter::Antialiasing);
    m_chartXresolutionZ->setRenderHint(QPainter::Antialiasing);
    m_chartZresolutionZ->setRenderHint(QPainter::Antialiasing);
    m_chartXresolutionZresolution->setRenderHint(QPainter::Antialiasing);
    m_chartTrapezoidLine->setRenderHint(QPainter::Antialiasing);
    //隐藏表格id列
    ui.tableWidget->hideColumn(m_indexColColorID);
    //表格表头大小自适应
    ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //表格表头名字
    QList<QString> columnNames;
    columnNames << "Width" << "Height" << QString::fromLocal8Bit("像元尺寸\n(μm)") << QString::fromLocal8Bit("焦距\n(mm)")
        << QString::fromLocal8Bit("基距\n(mm)") << QString::fromLocal8Bit("相机倾角\n(°)")
        << QString::fromLocal8Bit("安装高度\n(mm)") << QString::fromLocal8Bit("水平偏移\n(mm)")
        << QString::fromLocal8Bit("激光扇角\n(°)") << QString::fromLocal8Bit("沙姆角\n(°)")
        << QString::fromLocal8Bit("近端水平范围\n(mm)") << QString::fromLocal8Bit("远端水平范围\n(mm)")
        << QString::fromLocal8Bit("近端垂直高度\n(mm)") << QString::fromLocal8Bit("远端垂直高度\n(mm)")
        << QString::fromLocal8Bit("近端水平分辨\n率(mm/px)") << QString::fromLocal8Bit("远端水平分辨\n率(mm/px)")
        << QString::fromLocal8Bit("近端垂直分辨\n率(mm/px)") << QString::fromLocal8Bit("远端垂直分辨\n率(mm/px)");
    ui.tableWidget->setHorizontalHeaderLabels(columnNames);
    //信号与槽
    connect(ui.pushButtonXZ, &QPushButton::clicked, this, &scheimCamera::pushButtonXZClicked);
    connect(ui.pushButtonXresolutionZ, &QPushButton::clicked, this, &scheimCamera::pushButtonXresolutionZClicked);
    connect(ui.pushButtonXZ_2, &QPushButton::clicked, this, &scheimCamera::pushButtonZresolutionZClicked);
    connect(ui.pushButtonXZ_3, &QPushButton::clicked, this, &scheimCamera::pushButtonXresolutionZresolutionClicked);
    connect(ui.pushButton, &QPushButton::clicked, this, &scheimCamera::pushButtonTrapezoid);
    connect(ui.pushButtonAdd, &QPushButton::clicked, this, &scheimCamera::pushButtonAdd);
    connect(ui.pushButtonRefresh, &QPushButton::clicked, this, &scheimCamera::pushButtonRefresh);
    connect(ui.pushButtonSave, &QPushButton::clicked, this, &scheimCamera::pushButtonSave);
    connect(ui.pushButtonLoad, &QPushButton::clicked, this, &scheimCamera::pushButtonLoad);
    connect(ui.tableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(tableWidgetItemClicked(QTableWidgetItem*)));
    connect(ui.tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(tableWidgetItemChanged(QTableWidgetItem*)));
    connect(ui.comboBox_2, SIGNAL(activated(const QString&)), this, SLOT(selectMeasurementLine(const QString&)));

    m_pAxisXForMeasureRange = new QValueAxis();
    m_pAxisZForMeasureRange = new QValueAxis();
    m_pAxisXForMeasureRange->setTitleText("X(mm)");
    m_pAxisXForMeasureRange->setTitleFont(qfont);
    m_pAxisZForMeasureRange->setTitleText("Z(mm)");
    m_pAxisZForMeasureRange->setTitleFont(qfont);
    //

    m_pAxisZForWidthResolution = new QValueAxis();
    m_pAxisWidthResolution = new QValueAxis();
    m_pAxisWidthResolution->setTitleText("Xresolution(mm/px)");
    m_pAxisWidthResolution->setTitleFont(qfont);
    m_pAxisZForWidthResolution->setTitleText("Z(mm)");
    m_pAxisZForWidthResolution->setTitleFont(qfont);

    m_pAxisHeightResolution = new QValueAxis();
    m_pAxisZForHeightResolution = new QValueAxis();
    m_pAxisHeightResolution->setTitleText("Zresolution(mm/px)");
    m_pAxisHeightResolution->setTitleFont(qfont);
    m_pAxisZForHeightResolution->setTitleText("Z(mm)");
    m_pAxisZForHeightResolution->setTitleFont(qfont);

    //
    m_pAxisHeightForHeightWidthResolution = new QValueAxis();
    m_pAxisWidthForHeightWidthResolution = new QValueAxis();
    m_pAxisHeightForHeightWidthResolution->setTitleText("Zresolution(mm/px)");
    m_pAxisHeightForHeightWidthResolution->setTitleFont(qfont);
    m_pAxisWidthForHeightWidthResolution->setTitleText("Xresolution(mm/px)");
    m_pAxisWidthForHeightWidthResolution->setTitleFont(qfont);

    //
    m_pAxisZRange = new QValueAxis(); //Z 因变量
    m_pAxisXRange = new QValueAxis(); //X 自变量

    QString::fromLocal8Bit("垂直方向(mm)");
    m_pAxisZRange->setTitleText(QString::fromLocal8Bit("垂直方向(mm)"));
    m_pAxisXRange->setTitleText(QString::fromLocal8Bit("水平方向(mm)"));
    m_pAxisZRange->setTitleFont(qfont);
    m_pAxisXRange->setTitleFont(qfont);

    //设置input默认值
    ui.LineEditPixelSize->setText(QString::number(6, 'f', 1));
    ui.height->setText(QString::number(832));
    ui.width->setText(QString::number(2560));
    ui.LineEditBaseDistance->setText(QString::number(400, 'f', 1));
    ui.LineEditCameraAngle->setText(QString::number(15, 'f', 1));
    ui.LineEditFocalLength->setText(QString::number(12, 'f', 1));
    ui.lineEditLaserFan->setText(QString::number(75, 'f', 1));
    ui.lineEditCamVerticalLength->setText(QString::number(0, 'f', 1));
    ui.lineEditCamHorizontalOffset->setText(QString::number(0, 'f', 1));
    QPixmap pixmap(".\\scheimpCam.png");
    ui.labelImg->setPixmap(pixmap);


    m_strTempDBTableName = "paramsTable";
}

scheimCamera::~scheimCamera()
{
    const char* strTempDBName = ".\\temp.db";
    m_readWriteSqliteDBTemp.OpenDB("temp.db");
    if (m_readWriteSqliteDBTemp.GetDataCounts(m_strTempDBTableName.c_str()) > 30) //temp中缓存超过30条，全部删除
    {
        std::remove(strTempDBName);
    }
    m_readWriteSqliteDBTemp.CloseDB();
    saveToTemp();
    //释放内存
    RELEASE_PTR(m_pAxisXForMeasureRange);
    RELEASE_PTR(m_pAxisZForMeasureRange);
    RELEASE_PTR(m_pAxisZForWidthResolution);
    RELEASE_PTR(m_pAxisWidthResolution);
    RELEASE_PTR(m_pAxisZForHeightResolution);
    RELEASE_PTR(m_pAxisHeightResolution);
    RELEASE_PTR(m_pAxisHeightForHeightWidthResolution);
    RELEASE_PTR(m_pAxisWidthForHeightWidthResolution);
    RELEASE_PTR(m_pAxisXRange);
    RELEASE_PTR(m_pAxisZRange);
    for (auto iter = m_listpLineseriesForMeasureRange.begin(); iter != m_listpLineseriesForMeasureRange.end(); ++iter)
    {
        RELEASE_PTR((*iter));
    }
    for (auto iter = m_listpLineseriesForWidthResolution.begin(); iter != m_listpLineseriesForWidthResolution.end(); ++iter)
    {
        RELEASE_PTR((*iter));
    }
    for (auto iter = m_listpLineseriesForHeightResolution.begin(); iter != m_listpLineseriesForHeightResolution.end(); ++iter)
    {
        RELEASE_PTR((*iter));
    }
    for (auto iter = m_listpLineseriesForHeightWidthResolution.begin(); iter != m_listpLineseriesForHeightWidthResolution.end(); ++iter)
    {
        RELEASE_PTR((*iter));
    }
    for (auto iter = m_listpLineseriesUpAndRight.begin(); iter != m_listpLineseriesUpAndRight.end(); ++iter)
    {
        RELEASE_PTR((*iter));
    }
    for (auto iter = m_listpLineseriesDownAndLeft.begin(); iter != m_listpLineseriesDownAndLeft.end(); ++iter)
    {
        RELEASE_PTR((*iter));
    }
    for (auto iter = m_listpLineseriesLaserOrigin.begin(); iter != m_listpLineseriesLaserOrigin.end(); ++iter)
    {
        RELEASE_PTR((*iter));
    }
    for (auto iter = m_listpLineseriesLaserBottom.begin(); iter != m_listpLineseriesLaserBottom.end(); ++iter)
    {
        RELEASE_PTR((*iter));
    }
    for (auto iter = m_listpAreaSeries.begin(); iter != m_listpAreaSeries.end(); ++iter)
    {
        RELEASE_PTR((*iter));
    }
    for (auto iter = m_listpAreaSeriesLaser.begin(); iter != m_listpAreaSeriesLaser.end(); ++iter)
    {
        RELEASE_PTR((*iter));
    }
    for (auto iter = m_listpAreaLinearGradient.begin(); iter != m_listpAreaLinearGradient.end(); ++iter)
    {
        RELEASE_PTR((*iter));
    }
    for (auto iter = m_listpAreaLaserLinearGradient.begin(); iter != m_listpAreaLaserLinearGradient.end(); ++iter)
    {
        RELEASE_PTR((*iter));
    }
    for (auto iter = m_listpPushButtonDelete.begin(); iter != m_listpPushButtonDelete.end(); ++iter)
    {
        RELEASE_PTR((*iter));
    }
    for (auto iter = m_listpPushButtonHideShowCam.begin(); iter != m_listpPushButtonHideShowCam.end(); ++iter)
    {
        RELEASE_PTR((*iter));
    }
    for (auto iter = m_listpPushButtonHideShowLaser.begin(); iter != m_listpPushButtonHideShowLaser.end(); ++iter)
    {
        RELEASE_PTR((*iter));
    }

}



bool scheimCamera::SetInputParams(int index)
{
    bool bRet = false;
    std::list<CSchCamParamCal>::iterator iter = m_calScheCamDataForUI.m_listCSchCamParamCal.begin();
    while (index > 0)
    {
        iter++;
        index--;
    }
    iter->m_SensorParam.dPixelSize = ui.LineEditPixelSize->text().toDouble();
    iter->m_SensorParam.iSensorHeight = ui.height->text().toInt();
    iter->m_SensorParam.iSensorWidth = ui.width->text().toInt();
    iter->m_dBaseDistance = ui.LineEditBaseDistance->text().toDouble();
    iter->m_dCamAngle = ui.LineEditCameraAngle->text().toDouble();
    iter->m_dF = ui.LineEditFocalLength->text().toDouble();
    iter->m_dLaserFanAngle = ui.lineEditLaserFan->text().toDouble();
    iter->m_dCamVerticalHeight = ui.lineEditCamVerticalLength->text().toDouble();
    iter->m_dCamHorizontalOffset = ui.lineEditCamHorizontalOffset->text().toDouble();
    bRet = true;
    return bRet;
}



bool scheimCamera::GetOutputParams(int index)
{
    m_calScheCamDataForUI.CalOutputParams(index);
    std::list<CSchCamParamCal>::iterator iter = m_calScheCamDataForUI.m_listCSchCamParamCal.begin();
    while (index > 0)
    {
        iter++;
        index--;
    }
    //ui.LineEditScheimpflugAngle->setText(QString::number(iter->m_dScheimpflugAngle, 'f', 3));
    //ui.LineEditCloseRange->setText(QString::number(iter->m_dMinWidthMeasurement, 'f', 3));
    //ui.LineEditFarRange->setText(QString::number(iter->m_dMaxWidthMeasurement, 'f', 3));
    //ui.LineEditVerticalRange->setText(QString::number(iter->m_dHeightMeasurement, 'f', 3));
    //ui.LineEditCloseHorizonPrecison->setText(QString::number(iter->m_dWidthResolutionFovTop, 'f', 3));
    //ui.LineEditFarHorizonPrecison->setText(QString::number(iter->m_dWidthResolutionFovBottom, 'f', 3));
    //ui.LineEditCloseVerticalPrecison->setText(QString::number(iter->m_dHeightResolutionFovTop, 'f', 3));
    //ui.LineEditFarVerticalPrecison->setText(QString::number(iter->m_dHeightResolutionFovBottom, 'f', 3));
    return true;
}





void scheimCamera::pushButtonXZClicked()
{
    ui.stackedWidget->setCurrentIndex(0);
}

void scheimCamera::pushButtonXresolutionZClicked()
{
    ui.stackedWidget->setCurrentIndex(1);
}

void scheimCamera::pushButtonAdd()
{
    if (!isInputParamsValid())
    {
        return;
    }
    disconnect(ui.tableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(tableWidgetItemClicked(QTableWidgetItem*)));
    disconnect(ui.tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(tableWidgetItemChanged(QTableWidgetItem*)));
    if (!SaveInputParams())
    {
        connect(ui.tableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(tableWidgetItemClicked(QTableWidgetItem*)));
        connect(ui.tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(tableWidgetItemChanged(QTableWidgetItem*)));
        return;
    }
    int TableRowIndex = ui.tableWidget->rowCount() - 1;
    ui.tableWidget->setItem(TableRowIndex, 0, new QTableWidgetItem(QString::number(ui.width->text().toInt())));
    ui.tableWidget->setItem(TableRowIndex, 1, new QTableWidgetItem(QString::number(ui.height->text().toInt())));
    ui.tableWidget->setItem(TableRowIndex, 2, new QTableWidgetItem(QString::number(ui.LineEditPixelSize->text().toDouble())));
    ui.tableWidget->setItem(TableRowIndex, 3, new QTableWidgetItem(QString::number(ui.LineEditFocalLength->text().toDouble())));
    ui.tableWidget->setItem(TableRowIndex, 4, new QTableWidgetItem(QString::number(ui.LineEditBaseDistance->text().toDouble())));
    ui.tableWidget->setItem(TableRowIndex, 5, new QTableWidgetItem(QString::number(ui.LineEditCameraAngle->text().toDouble())));
    ui.tableWidget->setItem(TableRowIndex, 6, new QTableWidgetItem(QString::number(ui.lineEditCamVerticalLength->text().toDouble())));
    ui.tableWidget->setItem(TableRowIndex, 7, new QTableWidgetItem(QString::number(ui.lineEditCamHorizontalOffset->text().toDouble())));
    ui.tableWidget->setItem(TableRowIndex, 8, new QTableWidgetItem(QString::number(ui.lineEditLaserFan->text().toDouble())));

    int index = m_calScheCamDataForUI.m_listCSchCamParamCal.size() - 1;
    m_calScheCamDataForUI.CalOutputParams(index);
    std::list<CSchCamParamCal>::iterator iter = m_calScheCamDataForUI.m_listCSchCamParamCal.begin();
    while (index > 0)
    {
        iter++;
        index--;
    }
    ui.tableWidget->setItem(TableRowIndex, 9, new QTableWidgetItem(QString::number(iter->m_dScheimpflugAngle, 'f', 3)));
    ui.tableWidget->setItem(TableRowIndex, 10, new QTableWidgetItem(QString::number(iter->m_dMinWidthMeasurement, 'f', 3)));
    ui.tableWidget->setItem(TableRowIndex, 11, new QTableWidgetItem(QString::number(iter->m_dMaxWidthMeasurement, 'f', 3)));
    ui.tableWidget->setItem(TableRowIndex, 12, new QTableWidgetItem(QString::number(iter->m_dHeightMeasurementTop, 'f', 3)));
    ui.tableWidget->setItem(TableRowIndex, 13, new QTableWidgetItem(QString::number(iter->m_dHeightMeasurementBottom,'f', 3)));
    ui.tableWidget->setItem(TableRowIndex, 14, new QTableWidgetItem(QString::number(iter->m_dWidthResolutionFovTop, 'f', 3)));
    ui.tableWidget->setItem(TableRowIndex, 15, new QTableWidgetItem(QString::number(iter->m_dWidthResolutionFovBottom, 'f', 3)));
    ui.tableWidget->setItem(TableRowIndex, 16, new QTableWidgetItem(QString::number(iter->m_dHeightResolutionFovTop, 'f', 3)));
    ui.tableWidget->setItem(TableRowIndex, 17, new QTableWidgetItem(QString::number(iter->m_dHeightResolutionFovBottom, 'f', 3)));

    ShowLinesAndAreas(m_calScheCamDataForUI.m_listCSchCamParamCal.size() - 1);
    
    connect(ui.tableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(tableWidgetItemClicked(QTableWidgetItem*)));
    connect(ui.tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(tableWidgetItemChanged(QTableWidgetItem*)));
    //saveTemp(ui.tableWidget->rowCount() - 1);
    //设置输出列和颜色列不能编辑
    for (int i = 9; i < 18; ++i)
    {
        for (int j = ui.tableWidget->rowCount()-1; j < ui.tableWidget->rowCount(); ++j)
        {
            ui.tableWidget->item(j, i)->setFlags(ui.tableWidget->item(j,i)->flags() & (~Qt::ItemIsEditable));
        }
    }
    for (int j = ui.tableWidget->rowCount() - 1; j < ui.tableWidget->rowCount(); ++j)
    {
        ui.tableWidget->item(j, ui.tableWidget->columnCount() - 3)->
            setFlags(ui.tableWidget->item(j, ui.tableWidget->columnCount() - 3)->flags() & (~Qt::ItemIsEditable));
    }
    if (ui.comboBox_2->count() == 1) //第一次添加，手动触发measurementline
    {
        selectMeasurementLine(ui.comboBox_2->itemText(0));
    }

}

void scheimCamera::pushButtonZresolutionZClicked()
{
    ui.stackedWidget->setCurrentIndex(2);
}

void scheimCamera::pushButtonXresolutionZresolutionClicked()
{
    ui.stackedWidget->setCurrentIndex(3);
}

void scheimCamera::saveToTemp(int iRow)
{
    //从表格里读取数据
    std::vector<long long> colWidth;
    std::vector<long long> colHeight;
    std::vector<double> colPixelSize;
    std::vector<double> colFocalLength;
    std::vector<double> colBaseDistance;
    std::vector<double> colCamAngle;
    std::vector<double> colCamHeight;
    std::vector<double> colCamWidthOffset;
    std::vector<double> colLaserFanAngle;
    std::vector<double> colScheimpflugAngle;
    std::vector<void*> vecPtrCols{ &colWidth,&colHeight,&colPixelSize,&colFocalLength ,&colBaseDistance,&colCamAngle ,&colCamHeight,
        &colCamWidthOffset,&colLaserFanAngle, &colScheimpflugAngle };

    int iColItem = 0;
    for (int iCol = 0; iCol < ui.tableWidget->columnCount(); ++iCol)
    {
        if (iColItem == m_readWriteSqliteDBTemp.m_tableMapColNamesTypes[m_strTempDBTableName].vecColTypes.size())
        {
            break;
        }
        if (nullptr == ui.tableWidget->item(0, iCol)) //碰到pushButton等控件了，不进行操作
        {
            continue;
        }
        TYPE iColType = m_readWriteSqliteDBTemp.m_tableMapColNamesTypes[m_strTempDBTableName].vecColTypes.at(iColItem);
        if (TYPE::INT == iColType)
        {
            ((std::vector<int>*)vecPtrCols[iColItem])->push_back(ui.tableWidget->item(iRow, iCol)->text().toInt());
        }
        if (TYPE::INT64 == iColType)
        {
            ((std::vector<long long>*)vecPtrCols[iColItem])->push_back(ui.tableWidget->item(iRow, iCol)->text().toLongLong());
        }
        if (TYPE::INTEGER == iColType)
        {
            ((std::vector<long long>*)vecPtrCols[iColItem])->push_back(ui.tableWidget->item(iRow, iCol)->text().toLongLong());
        }
        if (TYPE::DOUBLE == iColType)
        {
            ((std::vector<double>*)vecPtrCols[iColItem])->push_back(ui.tableWidget->item(iRow, iCol)->text().toDouble());
        }
        iColItem++;
    }

    bool bret = m_readWriteSqliteDBTemp.Append(m_strTempDBTableName.c_str(), 1, { &colWidth,&colHeight ,&colPixelSize,&colFocalLength ,&colBaseDistance,&colCamAngle
        ,&colCamHeight,&colCamWidthOffset,
        &colLaserFanAngle, &colScheimpflugAngle });
}

void scheimCamera::saveToTemp()
{
    //temp数据库打开
    std::string strSqlCreateTable = "CREATE TABLE " + m_strTempDBTableName + "(width INT64, height INT64, pixelSize double, focalLength double," +
        "baseDistance double, camAngle double, camHeight double, camWidthOffset double, laserFanAngle double, ScheimpflugAngle double)";
    m_readWriteSqliteDBTemp.OpenDB("temp.db");
    m_readWriteSqliteDBTemp.CreateTable(strSqlCreateTable.c_str(), m_strTempDBTableName.c_str());
    //从表格里读取数据
    std::vector<long long> colWidth;
    std::vector<long long> colHeight;
    std::vector<double> colPixelSize;
    std::vector<double> colFocalLength;
    std::vector<double> colBaseDistance;
    std::vector<double> colCamAngle;
    std::vector<double> colCamHeight;
    std::vector<double> colCamWidthOffset;
    std::vector<double> colLaserFanAngle;
    std::vector<double> colScheimpflugAngle;
    std::vector<void*> vecPtrCols{ &colWidth,&colHeight,&colPixelSize,&colFocalLength ,&colBaseDistance,&colCamAngle ,&colCamHeight,
        &colCamWidthOffset,&colLaserFanAngle, &colScheimpflugAngle };

    int iColItem = 0;
    for (int iCol = 0; iCol < ui.tableWidget->columnCount(); ++iCol)
    {
        if (iColItem == m_readWriteSqliteDBTemp.m_tableMapColNamesTypes[m_strTempDBTableName].vecColTypes.size())
        {
            break;
        }
        if (nullptr == ui.tableWidget->item(0, iCol)) //碰到pushButton等控件了，不进行操作
        {
            continue;
        }
        TYPE iColType = m_readWriteSqliteDBTemp.m_tableMapColNamesTypes[m_strTempDBTableName].vecColTypes.at(iColItem);
        if (TYPE::INT == iColType)
        {
            for (int iRow = 0; iRow < ui.tableWidget->rowCount(); ++iRow)
            {
                ((std::vector<int>*)vecPtrCols[iColItem])->push_back(ui.tableWidget->item(iRow, iCol)->text().toInt());
            }
        }
        if (TYPE::INT64 == iColType)
        {
            for (int iRow = 0; iRow < ui.tableWidget->rowCount(); ++iRow)
            {
                ((std::vector<long long>*)vecPtrCols[iColItem])->push_back(ui.tableWidget->item(iRow, iCol)->text().toLongLong());
            }
        }
        if (TYPE::INTEGER == iColType)
        {
            for (int iRow = 0; iRow < ui.tableWidget->rowCount(); ++iRow)
            {
                ((std::vector<long long>*)vecPtrCols[iColItem])->push_back(ui.tableWidget->item(iRow, iCol)->text().toLongLong());
            }
        }
        if (TYPE::DOUBLE == iColType)
        {
            for (int iRow = 0; iRow < ui.tableWidget->rowCount(); ++iRow)
            {
                ((std::vector<double>*)vecPtrCols[iColItem])->push_back(ui.tableWidget->item(iRow, iCol)->text().toDouble());
            }
        }
        iColItem++;
    }
    m_readWriteSqliteDBTemp.Append(m_strTempDBTableName.c_str(), ui.tableWidget->rowCount(), { &colWidth,&colHeight ,&colPixelSize,&colFocalLength ,&colBaseDistance,&colCamAngle
        ,&colCamHeight,&colCamWidthOffset,
        &colLaserFanAngle, &colScheimpflugAngle });

    m_readWriteSqliteDBTemp.CloseDB();
}

bool scheimCamera::isInputParamsValid()
{
    bool bRet = false;
    double toRadian = std::acos(-1) / 180;
    double sensorHeightInMm = ui.LineEditPixelSize->text().toDouble()* std::pow(10, -3) * ui.height->text().toInt();
    double lengthOpticalToSensorMiddle = ui.LineEditFocalLength->text().toDouble();
    double dAngleMiddleOpticalSensorTop = std::atan(0.5 * sensorHeightInMm / lengthOpticalToSensorMiddle);
    QFont ft;
    QPalette pe;
    ft.setPointSize(10);
    ui.label_2->setFont(ft);
    if (0 >= ui.width->text().toInt())
    {
        ui.width->setStyleSheet("QLineEdit{border:1px solid rgb(255, 0, 0);}"); //红色边框
        pe.setColor(QPalette::WindowText, Qt::red);
        ui.label_2->setPalette(pe);
        ui.label_2->setText(QString::fromLocal8Bit("传感器平面尺寸参数不正确"));
        return bRet;
    }
    if( 0 >= ui.height->text().toInt())
    {
        ui.height->setStyleSheet("QLineEdit{border:1px solid rgb(255, 0, 0);}"); //红色边框
        pe.setColor(QPalette::WindowText, Qt::red);
        ui.label_2->setPalette(pe);
        ui.label_2->setText(QString::fromLocal8Bit("传感器平面尺寸参数不正确"));
        return bRet;
    }
    if( 0 >= ui.LineEditPixelSize->text().toDouble())
    {
        ui.LineEditPixelSize->setStyleSheet("QLineEdit{border:1px solid rgb(255, 0, 0);}"); //红色边框
        pe.setColor(QPalette::WindowText, Qt::red);
        ui.label_2->setPalette(pe);
        ui.label_2->setText(QString::fromLocal8Bit("像元尺寸应大于0μm"));
        return bRet;
    }
    if( 0 >= ui.LineEditFocalLength->text().toDouble())
    {
        ui.LineEditFocalLength->setStyleSheet("QLineEdit{border:1px solid rgb(255, 0, 0);}"); //红色边框
        pe.setColor(QPalette::WindowText, Qt::red);
        ui.label_2->setPalette(pe);
        ui.label_2->setText(QString::fromLocal8Bit("焦距应大于0mm"));
        return bRet;
    }
    if( 0 >= ui.LineEditBaseDistance->text().toDouble())
    {
        ui.LineEditBaseDistance->setStyleSheet("QLineEdit{border:1px solid rgb(255, 0, 0);}"); //红色边框
        pe.setColor(QPalette::WindowText, Qt::red);
        ui.label_2->setPalette(pe);
        ui.label_2->setText(QString::fromLocal8Bit("基距应大于0mm"));
        return bRet;
    }
    if( 0 >= ui.LineEditCameraAngle->text().toDouble())
    {
        ui.LineEditCameraAngle->setStyleSheet("QLineEdit{border:1px solid rgb(255, 0, 0);}"); //红色边框
        pe.setColor(QPalette::WindowText, Qt::red);
        ui.label_2->setPalette(pe);
        ui.label_2->setText(QString::fromLocal8Bit("相机倾角应大于0°"));
        return bRet;
    }
    if ( ui.LineEditCameraAngle->text().toDouble()>=90)
    {
        ui.LineEditCameraAngle->setStyleSheet("QLineEdit{border:1px solid rgb(255, 0, 0);}"); //红色边框
        pe.setColor(QPalette::WindowText, Qt::red);
        ui.label_2->setPalette(pe);
        ui.label_2->setText(QString::fromLocal8Bit("相机倾角应小于90°"));
        return bRet;
    }
    if( 0 >= ui.lineEditLaserFan->text().toDouble())
    {
        ui.lineEditLaserFan->setStyleSheet("QLineEdit{border:1px solid rgb(255, 0, 0);}"); //红色边框
        pe.setColor(QPalette::WindowText, Qt::red);
        ui.label_2->setPalette(pe);
        ui.label_2->setText(QString::fromLocal8Bit("激光扇角应大于0°"));
        return bRet;
    }
    if ( ui.lineEditLaserFan->text().toDouble()>=180)
    {
        ui.lineEditLaserFan->setStyleSheet("QLineEdit{border:1px solid rgb(255, 0, 0);}"); //红色边框
        pe.setColor(QPalette::WindowText, Qt::red);
        ui.label_2->setPalette(pe);
        ui.label_2->setText(QString::fromLocal8Bit("激光扇角应小于180°"));
        return bRet;
    }
    if (ui.LineEditCameraAngle->text().toDouble() <= (dAngleMiddleOpticalSensorTop / toRadian))
    {
        ui.LineEditCameraAngle->setStyleSheet("QLineEdit{border:1px solid rgb(255, 0, 0);}"); //红色边框
        ui.LineEditFocalLength->setStyleSheet("QLineEdit{border:1px solid rgb(255, 0, 0);}");
        ui.LineEditPixelSize->setStyleSheet("QLineEdit{border:1px solid rgb(255, 0, 0);}");
        ui.width->setStyleSheet("QLineEdit{border:1px solid rgb(255, 0, 0);}");
        ui.height->setStyleSheet("QLineEdit{border:1px solid rgb(255, 0, 0);}");
        pe.setColor(QPalette::WindowText, Qt::red);
        ui.label_2->setPalette(pe);
        ui.label_2->setText(QString::fromLocal8Bit("传感器尺寸太大 或 焦距太小 或 相机倾角太小"));
        return bRet;
    }

    ui.LineEditCameraAngle->setStyleSheet("QLineEdit{border:1px solid rgb(0, 0, 0);}"); //黑色边框
    ui.LineEditFocalLength->setStyleSheet("QLineEdit{border:1px solid rgb(0, 0, 0);}");
    ui.LineEditPixelSize->setStyleSheet("QLineEdit{border:1px solid rgb(0, 0, 0);}");
    ui.LineEditBaseDistance->setStyleSheet("QLineEdit{border:1px solid rgb(0, 0, 0);}");
    ui.LineEditCameraAngle->setStyleSheet("QLineEdit{border:1px solid rgb(0, 0, 0);}");
    ui.lineEditCamVerticalLength->setStyleSheet("QLineEdit{border:1px solid rgb(0, 0, 0);}");
    ui.lineEditCamHorizontalOffset->setStyleSheet("QLineEdit{border:1px solid rgb(0, 0, 0);}");
    ui.width->setStyleSheet("QLineEdit{border:1px solid rgb(0, 0, 0);}");
    ui.height->setStyleSheet("QLineEdit{border:1px solid rgb(0, 0, 0);}");
    ui.lineEditLaserFan->setStyleSheet("QLineEdit{border:1px solid rgb(0, 0, 0);}");
    pe.setColor(QPalette::WindowText, Qt::darkGreen);
    ui.label_2->setPalette(pe);
    ui.label_2->setText(QString::fromLocal8Bit("参数正常"));
    
    bRet = true;
    return bRet;
}

void scheimCamera::pushButtonTrapezoid()
{
    ui.stackedWidget->setCurrentIndex(4);
}

void scheimCamera::tableWidgetItemClicked(QTableWidgetItem* item)
{
    int iRow = item->row();
    int iCol = item->column();
    std::list<CSchCamParamCal>::iterator  iterCal = m_calScheCamDataForUI.m_listCSchCamParamCal.begin();
    int colorID = ui.tableWidget->model()->index(iRow, m_indexColColorID).data().toInt();
    int indexOfLinesToBeDelete = -1;
    //找到对应的lines
    for (std::map<int*, colorHidden>::iterator iter = m_colorTable.colorTaken.begin(); iter != m_colorTable.colorTaken.end(); iter++)
    {
        if (colorID == (iter->first)[6] && nullptr != iter->second.pGradient) //找到对应的line
        {
            QLinearGradient* lineGradientToBeDelete = iter->second.pGradient;
            for (std::list<QLinearGradient*>::iterator iterLineGradient = m_listpAreaLinearGradient.begin();
                iterLineGradient != m_listpAreaLinearGradient.end();
                iterLineGradient++)
            {
                indexOfLinesToBeDelete++;
                if (*iterLineGradient == lineGradientToBeDelete)
                {
                    break;
                }
            }
            break;
        }
    }
    while (indexOfLinesToBeDelete > 0)
    {
        iterCal++;
        indexOfLinesToBeDelete--;
    }
    //更新ui界面上的input
    //input
    ui.LineEditPixelSize->setText(QString::number(iterCal->m_SensorParam.dPixelSize, 'f', 3));
    ui.height->setText(QString::number(iterCal->m_SensorParam.iSensorHeight));
    ui.width->setText(QString::number(iterCal->m_SensorParam.iSensorWidth));
    ui.LineEditBaseDistance->setText(QString::number(iterCal->m_dBaseDistance, 'f', 3));
    ui.LineEditCameraAngle->setText(QString::number(iterCal->m_dCamAngle, 'f', 3));
    ui.LineEditFocalLength->setText(QString::number(iterCal->m_dF, 'f', 3));
    ui.lineEditLaserFan->setText(QString::number(iterCal->m_dLaserFanAngle, 'f', 3));
    ui.lineEditCamVerticalLength->setText(QString::number(iterCal->m_dCamVerticalHeight, 'f', 3));
    ui.lineEditCamHorizontalOffset->setText(QString::number(iterCal->m_dCamHorizontalOffset, 'f', 3));
}

void scheimCamera::flushAxisAndLines(std::list<QLineSeries*>& listpLines,QValueAxis* &axisIndependent, QValueAxis*& axisDependent, QChartView* chartView
    ,double minIndependent,double maxIndependent,double minDependent,double maxDependent)
{
    bool isFirstForRange = true;
    for (std::list<QLineSeries*>::iterator iter = listpLines.begin();
        iter != listpLines.end(); iter++)
    {
        if (*iter == nullptr)
        {
            return;
        }
        (*iter)->detachAxis(axisIndependent);
        (*iter)->detachAxis(axisDependent);
        if (isFirstForRange)
        {
            chartView->chart()->removeAxis(axisIndependent);
            chartView->chart()->removeAxis(axisDependent);
        }
        chartView->chart()->removeSeries((*iter));
        chartView->chart()->addSeries((*iter));
        if (isFirstForRange)
        {
            int tickCount = 15;
            int DependentTickCount = 9;
            axisIndependent->setRange(minIndependent, maxIndependent);
            axisDependent->setRange(minDependent, maxDependent);
            axisDependent->setMinorTickCount(0);
            axisIndependent->setMinorTickCount(0);
            axisDependent->setLineVisible(true);
            axisIndependent->setTickCount(tickCount);
            axisDependent->setTickCount(DependentTickCount);
            //axisDependent->applyNiceNumbers();
            //axisIndependent->applyNiceNumbers();
            chartView->chart()->addAxis(axisIndependent, Qt::AlignBottom);
            chartView->chart()->addAxis(axisDependent, Qt::AlignLeft);
        }
        (*iter)->attachAxis(axisIndependent);
        (*iter)->attachAxis(axisDependent);        
        isFirstForRange = false;
    }
}

void scheimCamera::pushButtonDelete()
{
    m_deleteMessageBox = QMessageBox::question(this, QString::fromLocal8Bit(" "), QString::fromLocal8Bit("确定删除方案？"));
    if (m_deleteMessageBox == QMessageBox::Yes)
    {}
    else if (m_deleteMessageBox == QMessageBox::No)
    {
        return;
    }
    disconnect(ui.tableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(tableWidgetItemClicked(QTableWidgetItem*)));
    disconnect(ui.tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(tableWidgetItemChanged(QTableWidgetItem*)));
    m_chartTrapezoidLine->m_pDownAndLeftPoints = nullptr;
    m_chartTrapezoidLine->m_pUpAndRightPoints = nullptr;
    //对应删除的calculators ,lines，gradient，points的迭代器
    std::list<CSchCamParamCal>::iterator  iterCal                                = m_calScheCamDataForUI.m_listCSchCamParamCal.begin();
    std::list<PointsSet>::iterator        iterPointsSet                          = m_calScheCamDataForUI.m_listPointsSet.begin();
    std::list<QLineSeries*>::iterator     iterLineseriesForMeasureRange          = m_listpLineseriesForMeasureRange.begin();
    std::list<QLineSeries*>::iterator     iterLineseriesForWidthResolution       = m_listpLineseriesForWidthResolution.begin();
    std::list<QLineSeries*>::iterator     iterLineseriesForHeightResolution      = m_listpLineseriesForHeightResolution.begin();
    std::list<QLineSeries*>::iterator     iterLineseriesForHeightWidthResolution = m_listpLineseriesForHeightWidthResolution.begin();
    std::list<QLineSeries*>::iterator     iterLineseriesUpAndRight               = m_listpLineseriesUpAndRight.begin();
    std::list<QLineSeries*>::iterator     iterLineseriesDownAndLeft              = m_listpLineseriesDownAndLeft.begin();
    std::list<QLineSeries*>::iterator     iterLineseriesLaserOrigin              = m_listpLineseriesLaserOrigin.begin();
    std::list<QLineSeries*>::iterator     iterLineseriesLaserBottom              = m_listpLineseriesLaserBottom.begin();
    std::list<QAreaSeries*>::iterator     iterLineseriesAreaSeries               = m_listpAreaSeries.begin();
    std::list<QAreaSeries*>::iterator     iterLineseriesAreaSeriesLaser          = m_listpAreaSeriesLaser.begin();
    std::list<QLinearGradient*>::iterator iterLinearGradient                     = m_listpAreaLinearGradient.begin();
    std::list<QLinearGradient*>::iterator iterLinearGradientLaser                = m_listpAreaLaserLinearGradient.begin();
    std::list<QPushButton*>::iterator     iterPushButtonDelete                   = m_listpPushButtonDelete.begin();
    std::list<QPushButton*>::iterator     iterPushButtonHideShowCam              = m_listpPushButtonHideShowCam.begin();
    std::list<QPushButton*>::iterator     iterPushButtonHideShowLaser            = m_listpPushButtonHideShowLaser.begin();
    //找到对应的line，删除，释放内存，并将map中颜色对应的line*置为null
    //这里会内存泄漏吗？？？
    QPushButton* pSenderObj = qobject_cast<QPushButton*>(sender());
    if (pSenderObj == nullptr)
    {
        return;
    }
    QModelIndex qIndex = ui.tableWidget->indexAt(QPoint(pSenderObj->frameGeometry().x(), pSenderObj->frameGeometry().y()));
    int row = qIndex.row();
    int column = qIndex.column();
    int colorID = ui.tableWidget->model()->index(row, m_indexColColorID).data().toInt();
    int indexOfLinesToBeDelete = -1;
    int indexOfLinesToBeDelete1 = -1;
    QString color = ui.tableWidget->model()->index(row, m_indexColColorID - 2).data().toString();
    //找到对应的lines
    for (std::map<int*, colorHidden>::iterator iter = m_colorTable.colorTaken.begin(); iter != m_colorTable.colorTaken.end(); iter++)
    {
        if (colorID == (iter->first)[6]&&nullptr!=iter->second.pGradient) //找到对应的line
        {
            QLinearGradient* lineGradientToBeDelete = iter->second.pGradient;
            for (std::list<QLinearGradient*>::iterator iterLineGradient = m_listpAreaLinearGradient.begin();
                iterLineGradient != m_listpAreaLinearGradient.end();
                iterLineGradient++)
            {
                indexOfLinesToBeDelete++;
                if (*iterLineGradient == lineGradientToBeDelete)
                {
                    break;
                }
            }
            iter->second.pGradient = nullptr; //置null
            break;
        }
    }

    //根据index，更新所有迭代器到需要删除的lines，points，gradients
    indexOfLinesToBeDelete1 = indexOfLinesToBeDelete;
    while (indexOfLinesToBeDelete > 0)
    {
        iterCal                                ++;
        iterPointsSet                          ++;
        iterLineseriesForMeasureRange          ++;
        iterLineseriesForWidthResolution       ++;
        iterLineseriesForHeightResolution      ++;
        iterLineseriesForHeightWidthResolution ++;
        iterLineseriesUpAndRight               ++;
        iterLineseriesDownAndLeft              ++;
        iterLineseriesLaserOrigin              ++;
        iterLineseriesLaserBottom              ++;
        iterLineseriesAreaSeries               ++;
        iterLineseriesAreaSeriesLaser          ++;
        iterLinearGradient                     ++;
        iterLinearGradientLaser                ++;
        iterPushButtonDelete                   ++;
        iterPushButtonHideShowCam              ++;
        iterPushButtonHideShowLaser            ++;
        indexOfLinesToBeDelete--;
    }
    //根据index，更新line的标签，减一
    auto iterArea = iterLineseriesAreaSeries;
    auto iterAreaLaser = iterLineseriesAreaSeriesLaser;
    auto iterMeasureRange = iterLineseriesForMeasureRange;
    auto iterWidthResolution = iterLineseriesForWidthResolution;
    auto iterHeightResolution = iterLineseriesForHeightResolution;
    auto iterHeightWidthResolution =iterLineseriesForHeightWidthResolution;
    iterArea++;
    iterAreaLaser++;
    iterMeasureRange++;
    iterWidthResolution++;
    iterHeightResolution++;
    iterHeightWidthResolution++;
    for (; iterArea != m_listpAreaSeries.end(); iterArea++)
    {
        (*iterArea)->setName(QString(std::to_string(indexOfLinesToBeDelete1+1).c_str()) + QString::fromLocal8Bit(":相机(梯形)"));
        (*iterAreaLaser)->setName(QString(std::to_string(indexOfLinesToBeDelete1 + 1).c_str()) + QString::fromLocal8Bit(":激光(三角)"));
        (*iterMeasureRange)->setName(QString::fromLocal8Bit("方案") + QString((std::to_string(indexOfLinesToBeDelete1 + 1) + " ").c_str()));
        (*iterWidthResolution)->setName(QString::fromLocal8Bit("方案") + QString((std::to_string(indexOfLinesToBeDelete1 + 1) + " ").c_str()));
        (*iterHeightResolution)->setName(QString::fromLocal8Bit("方案") + QString((std::to_string(indexOfLinesToBeDelete1 + 1) + " ").c_str()));
        (*iterHeightWidthResolution)->setName(QString::fromLocal8Bit("方案") + QString((std::to_string(indexOfLinesToBeDelete1 + 1) + " ").c_str()));

        indexOfLinesToBeDelete1++;
        iterAreaLaser++;
        iterMeasureRange++;
        iterWidthResolution++;
        iterHeightResolution++;
        iterHeightWidthResolution++;
    }
    //删除所有calculators,lines，points， ,且chart要remove，axis要detach
    m_calScheCamDataForUI.m_listCSchCamParamCal.erase(iterCal);
    m_calScheCamDataForUI.m_listPointsSet.erase(iterPointsSet);
    DeleteLine(m_listpLineseriesForMeasureRange, iterLineseriesForMeasureRange, m_pAxisZForMeasureRange, m_pAxisXForMeasureRange,
        m_chartXZRange);
    DeleteLine(m_listpLineseriesForWidthResolution, iterLineseriesForWidthResolution, m_pAxisZForWidthResolution,
        m_pAxisWidthResolution, m_chartXresolutionZ);
    DeleteLine(m_listpLineseriesForHeightResolution, iterLineseriesForHeightResolution, m_pAxisZForHeightResolution,
        m_pAxisHeightResolution, m_chartZresolutionZ);
    DeleteLine(m_listpLineseriesForHeightWidthResolution, iterLineseriesForHeightWidthResolution, m_pAxisHeightForHeightWidthResolution,
        m_pAxisWidthForHeightWidthResolution, m_chartXresolutionZresolution);
    DeleteLine(m_listpLineseriesUpAndRight, iterLineseriesUpAndRight, m_pAxisZRange, m_pAxisXRange, m_chartTrapezoidLine);
    DeleteLine(m_listpLineseriesDownAndLeft, iterLineseriesDownAndLeft, m_pAxisZRange, m_pAxisXRange, m_chartTrapezoidLine);
    DeleteLine(m_listpLineseriesLaserOrigin, iterLineseriesLaserOrigin, m_pAxisZRange, m_pAxisXRange, m_chartTrapezoidLine);
    DeleteLine(m_listpLineseriesLaserBottom, iterLineseriesLaserBottom, m_pAxisZRange, m_pAxisXRange, m_chartTrapezoidLine);
    DeleteArea(m_listpAreaSeries, iterLineseriesAreaSeries, m_pAxisZRange, m_pAxisXRange, m_chartTrapezoidLine);
    DeleteArea( m_listpAreaSeriesLaser, iterLineseriesAreaSeriesLaser, m_pAxisZRange, m_pAxisXRange, m_chartTrapezoidLine);
    m_listpAreaLinearGradient.erase(iterLinearGradient);
    m_listpAreaLaserLinearGradient.erase(iterLinearGradientLaser);
    
    ////删除temp表中相应行
    //char strDeleteSql[1024] = { 0 };
    //sprintf_s(strDeleteSql,1024,"DELETE FROM %s WHERE width = %d and height = %d and pixelSize = %f and focalLength = %f and baseDistance = %f "
    //    "and camAngle = %f and camHeight = %f and camWidthOffset = %f and laserFanAngle = %f",
    //    m_strTempDBTableName,ui.tableWidget->item(row,0)->text().toInt(),
    //    ui.tableWidget->item(row, 1)->text().toInt(),
    //    ui.tableWidget->item(row, 2)->text().toDouble(),
    //    ui.tableWidget->item(row, 3)->text().toDouble(),
    //    ui.tableWidget->item(row, 4)->text().toDouble(),
    //    ui.tableWidget->item(row, 5)->text().toDouble(),
    //    ui.tableWidget->item(row, 6)->text().toDouble(),
    //    ui.tableWidget->item(row, 7)->text().toDouble(),
    //    ui.tableWidget->item(row, 8)->text().toDouble());
    //char* pErrMsg = nullptr;
    //if (SQLITE_OK != sqlite3_exec(m_readWriteSqliteDBTemp.m_pSqlitedb, strDeleteSql, NULL, NULL, &pErrMsg))
    //{
    //    qDebug() << "操作发生失败，失败原因:" << pErrMsg << endl;;
    //    sqlite3_free(pErrMsg);
    //}
    //删除表格中的一行
    delete *iterPushButtonDelete;
    *iterPushButtonDelete = nullptr;
    m_listpPushButtonDelete.erase(iterPushButtonDelete);
    delete *iterPushButtonHideShowCam;
    *iterPushButtonHideShowCam = nullptr;
    m_listpPushButtonHideShowCam.erase(iterPushButtonHideShowCam);
    delete* iterPushButtonHideShowLaser;
    *iterPushButtonHideShowLaser = nullptr;
    m_listpPushButtonHideShowLaser.erase(iterPushButtonHideShowLaser);
    //释放一行中的item内存
    for (int iCol = 0; iCol < ui.tableWidget->columnCount(); ++iCol) 
    {
        if (ui.tableWidget->item(row, iCol))
        {
            delete ui.tableWidget->item(row, iCol);
            //ui.tableWidget->item(row, iCol) = nullptr;
        }
    }
    ui.tableWidget->removeRow(row);
    
    for (int i = 0; i < ui.comboBox_2->count(); i++)
    {
        if (ui.comboBox_2->itemText(i) == color)
        {
            ui.comboBox_2->removeItem(i);
        }
    }
    connect(ui.tableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(tableWidgetItemClicked(QTableWidgetItem*)));
    connect(ui.tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(tableWidgetItemChanged(QTableWidgetItem*)));



    if (ui.comboBox_2->count() > 0 ) //手动触发measurementline
    {
        selectMeasurementLine(ui.comboBox_2->currentText());
    }
    if (ui.comboBox_2->count() == 0)
    {
        m_chartTrapezoidLine->y_line->setVisible(false);
        m_chartTrapezoidLine->y_text->setVisible(false);
        m_chartTrapezoidLine->x_y_pos_text->setVisible(false);
    }
}

void scheimCamera::pushButtonSave()
{
    QFileDialog fileDialog;
    QString strSavingPath = fileDialog.getSaveFileName(this, tr("Open File"), "/CameraParams", tr("Text File(*.db)"));
    if (strSavingPath == "")
    {
    //    m_selectPathMessageBox = QMessageBox::critical(this, QString::fromLocal8Bit(" "), QString::fromLocal8Bit("文件名不能为空！"));
        return;
    }
    //const char* strFileName = "CameraParams.db";
    std::string strTableName = "paramsTable";
    std::string strSqlCreateTable = "CREATE TABLE " + strTableName + "(width INT64, height INT64, pixelSize double, focalLength double,"+
        "baseDistance double, camAngle double, camHeight double, camWidthOffset double, laserFanAngle double, ScheimpflugAngle double)";

    m_readWriteSqliteDB.OpenDB(strSavingPath.toStdString().c_str());
    m_readWriteSqliteDB.CreateTable(strSqlCreateTable.c_str(), strTableName.c_str());

    //从表格里读取数据
    std::vector<long long> colWidth;
    std::vector<long long> colHeight;
    std::vector<double> colPixelSize;
    std::vector<double> colFocalLength;
    std::vector<double> colBaseDistance;
    std::vector<double> colCamAngle;
    std::vector<double> colCamHeight;
    std::vector<double> colCamWidthOffset;
    std::vector<double> colLaserFanAngle;
    std::vector<double> colScheimpflugAngle;
    std::vector<void*> vecPtrCols{ &colWidth,&colHeight,&colPixelSize,&colFocalLength ,&colBaseDistance,&colCamAngle ,&colCamHeight,
        &colCamWidthOffset,&colLaserFanAngle, &colScheimpflugAngle };

    int iColItem = 0;
    for (int iCol = 0; iCol < ui.tableWidget->columnCount(); ++iCol)
    {
        if (iColItem == m_readWriteSqliteDB.m_tableMapColNamesTypes[strTableName].vecColTypes.size())
        {
            break;
        }
        if (nullptr == ui.tableWidget->item(0, iCol)) //碰到pushButton等控件了，不进行操作
        {
            continue;
        }
        TYPE iColType = m_readWriteSqliteDB.m_tableMapColNamesTypes[strTableName].vecColTypes.at(iColItem);
        if (TYPE::INT == iColType)
        {
            for (int iRow = 0; iRow < ui.tableWidget->rowCount(); ++iRow)
            {
                ((std::vector<int>*)vecPtrCols[iColItem])->push_back(ui.tableWidget->item(iRow, iCol)->text().toInt());
            }
        }
        if (TYPE::INT64 == iColType)
        {
            for (int iRow = 0; iRow < ui.tableWidget->rowCount(); ++iRow)
            {
                ((std::vector<long long>*)vecPtrCols[iColItem])->push_back(ui.tableWidget->item(iRow, iCol)->text().toLongLong());
            }
        }
        if (TYPE::INTEGER == iColType)
        {
            for (int iRow = 0; iRow < ui.tableWidget->rowCount(); ++iRow)
            {
                ((std::vector<long long>*)vecPtrCols[iColItem])->push_back(ui.tableWidget->item(iRow, iCol)->text().toLongLong());
            }
        }
        if (TYPE::DOUBLE == iColType)
        {
            for (int iRow = 0; iRow < ui.tableWidget->rowCount(); ++iRow)
            {
                ((std::vector<double>*)vecPtrCols[iColItem])->push_back(ui.tableWidget->item(iRow, iCol)->text().toDouble());
            }
        }
        iColItem++;
    }
    m_readWriteSqliteDB.Append(strTableName.c_str(), ui.tableWidget->rowCount(), { &colWidth,&colHeight ,&colPixelSize,&colFocalLength ,&colBaseDistance,&colCamAngle
        ,&colCamHeight,&colCamWidthOffset,
        &colLaserFanAngle, &colScheimpflugAngle });
    m_readWriteSqliteDB.CloseDB();
    QMessageBox::about(this, QString::fromLocal8Bit(" "), QString::fromLocal8Bit("保存成功！"));
}

void scheimCamera::pushButtonLoad()
{
    m_deleteMessageBox = QMessageBox::question(this, QString::fromLocal8Bit(" "), 
        QString::fromLocal8Bit("导入新方案会清空当前所有方案，是否继续？"));
    if (m_deleteMessageBox == QMessageBox::Yes)
    {
    }
    else if (m_deleteMessageBox == QMessageBox::No)
    {
        return;
    }
    QFileDialog fileDialog;
    QString strLoadPath = fileDialog.getOpenFileName(this, tr("Open File"), "", tr("All(*.db)"));
    if (strLoadPath == "")
    {
        return;
    }
    disconnect(ui.tableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(tableWidgetItemClicked(QTableWidgetItem*)));
    disconnect(ui.tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(tableWidgetItemChanged(QTableWidgetItem*)));
    //清空所有方案资源
    for (std::map<int*, colorHidden>::iterator iter = m_colorTable.colorTaken.begin(); iter != m_colorTable.colorTaken.end(); iter++)
    {
        if (iter->second.pGradient)
        {
            int indexOfLinesToBeDelete = -1;
            m_chartTrapezoidLine->m_pDownAndLeftPoints = nullptr;
            m_chartTrapezoidLine->m_pUpAndRightPoints = nullptr;
            //对应删除的calculators ,lines，gradient，points的迭代器
            std::list<CSchCamParamCal>::iterator  iterCal = m_calScheCamDataForUI.m_listCSchCamParamCal.begin();
            std::list<PointsSet>::iterator        iterPointsSet = m_calScheCamDataForUI.m_listPointsSet.begin();
            std::list<QLineSeries*>::iterator     iterLineseriesForMeasureRange = m_listpLineseriesForMeasureRange.begin();
            std::list<QLineSeries*>::iterator     iterLineseriesForWidthResolution = m_listpLineseriesForWidthResolution.begin();
            std::list<QLineSeries*>::iterator     iterLineseriesForHeightResolution = m_listpLineseriesForHeightResolution.begin();
            std::list<QLineSeries*>::iterator     iterLineseriesForHeightWidthResolution = m_listpLineseriesForHeightWidthResolution.begin();
            std::list<QLineSeries*>::iterator     iterLineseriesUpAndRight = m_listpLineseriesUpAndRight.begin();
            std::list<QLineSeries*>::iterator     iterLineseriesDownAndLeft = m_listpLineseriesDownAndLeft.begin();
            std::list<QLineSeries*>::iterator     iterLineseriesLaserOrigin = m_listpLineseriesLaserOrigin.begin();
            std::list<QLineSeries*>::iterator     iterLineseriesLaserBottom = m_listpLineseriesLaserBottom.begin();
            std::list<QAreaSeries*>::iterator     iterLineseriesAreaSeries = m_listpAreaSeries.begin();
            std::list<QAreaSeries*>::iterator     iterLineseriesAreaSeriesLaser = m_listpAreaSeriesLaser.begin();
            std::list<QLinearGradient*>::iterator iterLinearGradient = m_listpAreaLinearGradient.begin();
            std::list<QLinearGradient*>::iterator iterLinearGradientLaser = m_listpAreaLaserLinearGradient.begin();
            std::list<QPushButton*>::iterator     iterPushButtonDelete = m_listpPushButtonDelete.begin();
            std::list<QPushButton*>::iterator     iterPushButtonHideShowCam = m_listpPushButtonHideShowCam.begin();
            std::list<QPushButton*>::iterator     iterPushButtonHideShowLaser = m_listpPushButtonHideShowLaser.begin();
            //找到对应的line，删除，释放内存，并将map中颜色对应的line*置为null
       
            QLinearGradient* lineGradientToBeDelete = iter->second.pGradient;
            for (std::list<QLinearGradient*>::iterator iterLineGradient = m_listpAreaLinearGradient.begin();
                iterLineGradient != m_listpAreaLinearGradient.end();
                iterLineGradient++)
            {
                indexOfLinesToBeDelete++;
                if (*iterLineGradient == lineGradientToBeDelete)
                {
                    break;
                }
            }
                
            //根据index，更新所有迭代器到需要删除的lines，points，gradients
            while (indexOfLinesToBeDelete > 0)
            {
                iterCal++;
                iterPointsSet++;
                iterLineseriesForMeasureRange++;
                iterLineseriesForWidthResolution++;
                iterLineseriesForHeightResolution++;
                iterLineseriesForHeightWidthResolution++;
                iterLineseriesUpAndRight++;
                iterLineseriesDownAndLeft++;
                iterLineseriesLaserOrigin++;
                iterLineseriesLaserBottom++;
                iterLineseriesAreaSeries++;
                iterLineseriesAreaSeriesLaser++;
                iterLinearGradient++;
                iterLinearGradientLaser++;
                iterPushButtonDelete++;
                iterPushButtonHideShowCam++;
                iterPushButtonHideShowLaser++;
                indexOfLinesToBeDelete--;
            }
            //删除所有calculators,lines，points， ,且chart要remove，axis要detach
            m_calScheCamDataForUI.m_listCSchCamParamCal.erase(iterCal);
            m_calScheCamDataForUI.m_listPointsSet.erase(iterPointsSet);
            DeleteLine(m_listpLineseriesForMeasureRange, iterLineseriesForMeasureRange, m_pAxisZForMeasureRange, m_pAxisXForMeasureRange,
                m_chartXZRange);
            DeleteLine(m_listpLineseriesForWidthResolution, iterLineseriesForWidthResolution, m_pAxisZForWidthResolution,
                m_pAxisWidthResolution, m_chartXresolutionZ);
            DeleteLine(m_listpLineseriesForHeightResolution, iterLineseriesForHeightResolution, m_pAxisZForHeightResolution,
                m_pAxisHeightResolution, m_chartZresolutionZ);
            DeleteLine(m_listpLineseriesForHeightWidthResolution, iterLineseriesForHeightWidthResolution, m_pAxisHeightForHeightWidthResolution,
                m_pAxisWidthForHeightWidthResolution, m_chartXresolutionZresolution);
            DeleteLine(m_listpLineseriesUpAndRight, iterLineseriesUpAndRight, m_pAxisZRange, m_pAxisXRange, m_chartTrapezoidLine);
            DeleteLine(m_listpLineseriesDownAndLeft, iterLineseriesDownAndLeft, m_pAxisZRange, m_pAxisXRange, m_chartTrapezoidLine);
            DeleteLine(m_listpLineseriesLaserOrigin, iterLineseriesLaserOrigin, m_pAxisZRange, m_pAxisXRange, m_chartTrapezoidLine);
            DeleteLine(m_listpLineseriesLaserBottom, iterLineseriesLaserBottom, m_pAxisZRange, m_pAxisXRange, m_chartTrapezoidLine);
            DeleteArea(m_listpAreaSeries, iterLineseriesAreaSeries, m_pAxisZRange, m_pAxisXRange, m_chartTrapezoidLine);
            DeleteArea(m_listpAreaSeriesLaser, iterLineseriesAreaSeriesLaser, m_pAxisZRange, m_pAxisXRange, m_chartTrapezoidLine);
            m_listpAreaLinearGradient.erase(iterLinearGradient);
            m_listpAreaLaserLinearGradient.erase(iterLinearGradientLaser);

            //删除表格中的一行
            delete* iterPushButtonDelete;
            *iterPushButtonDelete = nullptr;
            m_listpPushButtonDelete.erase(iterPushButtonDelete);
            delete* iterPushButtonHideShowCam;
            *iterPushButtonHideShowCam = nullptr;
            m_listpPushButtonHideShowCam.erase(iterPushButtonHideShowCam);
            delete* iterPushButtonHideShowLaser;
            *iterPushButtonHideShowLaser = nullptr;
            m_listpPushButtonHideShowLaser.erase(iterPushButtonHideShowLaser);

            iter->second.pGradient = nullptr;
            iter->second.isCamHidden = false;
            iter->second.isLaserHidden = false;
        }
    }
    //释放table中的item内存
    for (int iRow = 0; iRow < ui.tableWidget->rowCount(); ++iRow)
    {
        for (int iCol = 0; iCol < ui.tableWidget->columnCount(); ++iCol)
        {
            if (ui.tableWidget->item(iRow, iCol))
            {
                delete ui.tableWidget->item(iRow, iCol);
                //ui.tableWidget->item(row, iCol) = nullptr;
            }
        }
        ui.tableWidget->removeRow(iRow);
    }

    for (int i = 0; i < ui.comboBox_2->count(); i++)
    {
        ui.comboBox_2->removeItem(i);
    }
    ui.comboBox_2->clear();
    m_chartTrapezoidLine->y_line->setVisible(false);
    m_chartTrapezoidLine->y_text->setVisible(false);
    m_chartTrapezoidLine->x_y_pos_text->setVisible(false);

    //打开数据库
    std::string strTableName = "paramsTable";
    m_readWriteSqliteDB.OpenDB(strLoadPath.toStdString().c_str());
    int iDataCount = m_readWriteSqliteDB.GetDataCounts(strTableName.c_str());
    m_readWriteSqliteDB.Read(strTableName.c_str(), 0, iDataCount);
    TableMapData& tableMapData = m_readWriteSqliteDB.GetTableData(strTableName.c_str());
    std::vector<long long>* pVecWidth = tableMapData.m_mapINTEGER["width"];
    std::vector<long long>* pVecHeight= tableMapData.m_mapINTEGER["height"];
    std::vector<double>* pVecPixelSize = tableMapData.m_mapREAL["pixelSize"];
    std::vector<double>* pVecFocalLength = tableMapData.m_mapREAL["focalLength"];
    std::vector<double>* pVecBaseDistance = tableMapData.m_mapREAL["baseDistance"];
    std::vector<double>* pVecCamAngle = tableMapData.m_mapREAL["camAngle"];
    std::vector<double>* pVecCamHeight = tableMapData.m_mapREAL["camHeight"];
    std::vector<double>* pVecCamWidthOffset= tableMapData.m_mapREAL["camWidthOffset"];
    std::vector<double>* pVecLaserFanAngle = tableMapData.m_mapREAL["laserFanAngle"];
    for (int i = 0; i < iDataCount; ++i)
    {
        ui.LineEditPixelSize->setText(QString::number(pVecPixelSize->at(i), 'f', 3));
        ui.height->setText(QString::number(pVecHeight->at(i)));
        ui.width->setText(QString::number(pVecWidth->at(i)));
        ui.LineEditBaseDistance->setText(QString::number(pVecBaseDistance->at(i), 'f', 3));
        ui.LineEditCameraAngle->setText(QString::number(pVecCamAngle->at(i), 'f', 3));
        ui.LineEditFocalLength->setText(QString::number(pVecFocalLength->at(i), 'f', 3));
        ui.lineEditLaserFan->setText(QString::number(pVecLaserFanAngle->at(i), 'f', 3));
        ui.lineEditCamVerticalLength->setText(QString::number(pVecCamHeight->at(i), 'f', 3));
        ui.lineEditCamHorizontalOffset->setText(QString::number(pVecCamWidthOffset->at(i), 'f', 3));
        if (!isInputParamsValid())
        {
            std::string waringStr = "方案" + std::to_string(i) + "导入失败,参数无效。";
            m_deleteMessageBox = QMessageBox::warning(this, QString::fromLocal8Bit(" "),
                QString::fromLocal8Bit(waringStr.c_str()));
            continue;
        }
        pushButtonAdd();
    }
    m_readWriteSqliteDB.CloseDB();
    connect(ui.tableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(tableWidgetItemClicked(QTableWidgetItem*)));
    connect(ui.tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(tableWidgetItemChanged(QTableWidgetItem*)));
    QMessageBox::about(this, QString::fromLocal8Bit(" "), QString::fromLocal8Bit("导入成功！"));
}

void scheimCamera::flushAxisAndAreas(std::list<QAreaSeries*>& listpAreaSeries, std::list<QAreaSeries*>& listpAreaSeriesLaser,
    QValueAxis*& axisIndependent, QValueAxis*& axisDependent, QChartView* chartView,
    double minIndependent, double maxIndependent, double minDependent, double maxDependent)
{
    bool isFirstForRange = true;
    for (std::list<QAreaSeries*>::iterator iterpAreaSeries = listpAreaSeries.begin(), iterpAreaSeriesLaser = listpAreaSeriesLaser.begin();
        iterpAreaSeries != listpAreaSeries.end() && iterpAreaSeriesLaser != listpAreaSeriesLaser.end();
        iterpAreaSeries++, iterpAreaSeriesLaser++)
    {
        (*iterpAreaSeries)->detachAxis(axisIndependent);
        (*iterpAreaSeries)->detachAxis(axisDependent);
        (*iterpAreaSeriesLaser)->detachAxis(axisIndependent);
        (*iterpAreaSeriesLaser)->detachAxis(axisDependent);
        if (isFirstForRange)
        {
            chartView->chart()->removeAxis(axisIndependent);
            chartView->chart()->removeAxis(axisDependent);
        }
        chartView->chart()->removeSeries(*iterpAreaSeries);
        chartView->chart()->removeSeries(*iterpAreaSeriesLaser);
        chartView->chart()->addSeries(*iterpAreaSeries);
        chartView->chart()->addSeries(*iterpAreaSeriesLaser);
        if (isFirstForRange)
        {
            int rangeMinIndependent = minIndependent < 0 ? (int)(minIndependent / 10 - 1) * 10 : (int)(minIndependent / 10 + 1) * 10;
            int rangeMaxIndependent= maxIndependent < 0 ? (int)(maxIndependent / 10 - 1) * 10 : (int)(maxIndependent / 10 + 1) * 10;
            if (rangeMinIndependent >= 0)
            {
                axisIndependent->setRange(0, rangeMaxIndependent);/*m_calScheCamDataForUI.ApplyRangeNumber(minIndependent),*/
            }
            else if(rangeMaxIndependent<=0)
            {
                axisIndependent->setRange(rangeMinIndependent, 0);
            }
            else
            {
                axisIndependent->setRange(-std::max(std::abs(rangeMinIndependent),rangeMaxIndependent), std::max(std::abs(rangeMinIndependent), rangeMaxIndependent));
            }/*  m_calScheCamDataForUI.ApplyRangeNumber(maxIndependent));*/// range.rangeTrapezoidXMin, range.rangeTrapezoidXMax);
            axisDependent->setRange(minDependent, 
                maxDependent < 0 ? (int)(maxDependent / 10 - 1) * 10 : (int)(maxDependent / 10 + 1) * 10);// range.rangeTrapezoidZMin, range.rangeTrapezoidZMax);
            axisIndependent->setMinorTickCount(0);
            axisDependent->setMinorTickCount(0);
            //int tickCount = (m_calScheCamDataForUI.ApplyRangeNumber(maxIndependent) / 1000) % 2 == 0 ? ((m_calScheCamDataForUI.ApplyRangeNumber(maxIndependent) / 1000) + 1)
            //    : ((m_calScheCamDataForUI.ApplyRangeNumber(maxIndependent) / 1000));
            int tickCount= ((rangeMaxIndependent-rangeMinIndependent) / 1000) % 2 == 0 ? ((rangeMaxIndependent - rangeMinIndependent) / 1000)*2 + 1
                    : ((rangeMaxIndependent - rangeMinIndependent) / 1000)*2+1;
            int DependentTickCount = 9;
            tickCount = tickCount >= 19 ? 19 : tickCount;
            tickCount = tickCount <= 15 ? 15 : tickCount;
            axisIndependent->setTickCount( tickCount);
            axisDependent->setTickCount(DependentTickCount);
            //axisIndependent->applyNiceNumbers();
            //axisDependent->applyNiceNumbers();
            axisIndependent->setLineVisible(true);
            axisDependent->setLineVisible(true);
            chartView->chart()->addAxis(axisIndependent, Qt::AlignBottom);
            chartView->chart()->addAxis(axisDependent, Qt::AlignLeft);
        }
        (*iterpAreaSeries)->attachAxis(axisIndependent);
        (*iterpAreaSeries)->attachAxis(axisDependent);
        (*iterpAreaSeriesLaser)->attachAxis(axisIndependent);
        (*iterpAreaSeriesLaser)->attachAxis(axisDependent);
        isFirstForRange = false;
    }


}

void scheimCamera::DeleteArea(std::list<QAreaSeries*>& listAreas, std::list<QAreaSeries*>::iterator& iterAreaToBeDelete, 
    QValueAxis*& axisIndependent, QValueAxis*& axisDependent, QChartView* chartView)
{
    (*iterAreaToBeDelete)->detachAxis(axisIndependent);
    (*iterAreaToBeDelete)->detachAxis(axisDependent);
    chartView->chart()->removeSeries(*iterAreaToBeDelete);
    delete* iterAreaToBeDelete;
    *iterAreaToBeDelete = nullptr;
    listAreas.erase(iterAreaToBeDelete);
}

void scheimCamera::HideLine(std::list<QLineSeries*>::iterator& iterLineToBeHide, QValueAxis*& axisIndependent, QValueAxis*& axisDependent, QChartView* chartView)
{
    (*iterLineToBeHide)->detachAxis(axisIndependent);
    (*iterLineToBeHide)->detachAxis(axisDependent);
    chartView->chart()->removeSeries(*iterLineToBeHide);
}

void scheimCamera::ShowLine(std::list<QLineSeries*>::iterator& iterLineToBeShow, QValueAxis*& axisIndependent, QValueAxis*& axisDependent, QChartView* chartView)
{
    chartView->chart()->addSeries(*iterLineToBeShow);
    (*iterLineToBeShow)->attachAxis(axisIndependent);
    (*iterLineToBeShow)->attachAxis(axisDependent);
}

void scheimCamera::HideArea(std::list<QAreaSeries*>::iterator& iterAreaToBeHide, QValueAxis*& axisIndependent, QValueAxis*& axisDependent, QChartView* chartView)
{
    (*iterAreaToBeHide)->detachAxis(axisIndependent);
    (*iterAreaToBeHide)->detachAxis(axisDependent);
    chartView->chart()->removeSeries(*iterAreaToBeHide);
}

void scheimCamera::ShowArea(std::list<QAreaSeries*>::iterator& iterAreaToBeShow, QValueAxis*& axisIndependent, QValueAxis*& axisDependent, QChartView* chartView)
{
    chartView->chart()->addSeries(*iterAreaToBeShow);
    (*iterAreaToBeShow)->attachAxis(axisIndependent);
    (*iterAreaToBeShow)->attachAxis(axisDependent);
}

void scheimCamera::HideAreaCam(int row)
{
    std::list<QAreaSeries*>::iterator     iterLineseriesAreaSeries = m_listpAreaSeries.begin();
    std::list<QPushButton*>::iterator     iterPushButtonShowHideCam = m_listpPushButtonHideShowCam.begin();
   
    int colorID = ui.tableWidget->model()->index(row, m_indexColColorID).data().toInt();

    int indexOfLinesToBeHideShow = -1;
    bool* pIsHidden = nullptr;
    //找到对应的lines
    for (std::map<int*, colorHidden>::iterator iter = m_colorTable.colorTaken.begin(); iter != m_colorTable.colorTaken.end(); iter++)
    {
        if (colorID == (iter->first)[6] && nullptr != iter->second.pGradient) //找到对应的line
        {
            QLinearGradient* lineGradientToBeHideShow = iter->second.pGradient;
            pIsHidden = &iter->second.isCamHidden;
            for (std::list<QLinearGradient*>::iterator iterLineGradient = m_listpAreaLinearGradient.begin();
                iterLineGradient != m_listpAreaLinearGradient.end();
                iterLineGradient++)
            {
                indexOfLinesToBeHideShow++;
                if (*iterLineGradient == lineGradientToBeHideShow)
                {
                    break;
                }
            }
            break;
        }
    }
    //根据index，更新所有迭代器到需要隐藏显示的lines，points，gradients
    while (indexOfLinesToBeHideShow > 0)
    {
        //iterLineseriesUpAndRight++;
        //iterLineseriesDownAndLeft++;
        iterLineseriesAreaSeries++;
        iterPushButtonShowHideCam++;
        indexOfLinesToBeHideShow--;
    }
    //隐藏或者显示
    if (nullptr == pIsHidden)
    {
        return;
    }

    HideArea(iterLineseriesAreaSeries, m_pAxisXRange, m_pAxisZRange, m_chartTrapezoidLine);
    *pIsHidden = true;
    (*iterPushButtonShowHideCam)->setText(QString::fromLocal8Bit("显示"));

}

void scheimCamera::HideAreaLaser(int row)
{
    //对应隐藏显示的lines的迭代器
    std::list<QAreaSeries*>::iterator     iterLineseriesAreaSeriesLaser = m_listpAreaSeriesLaser.begin();
    std::list<QPushButton*>::iterator    iterPushButtonShowHideLaser = m_listpPushButtonHideShowLaser.begin();

    int colorID = ui.tableWidget->model()->index(row, m_indexColColorID).data().toInt();

    int indexOfLinesToBeHideShow = -1;
    bool* pIsHidden = nullptr;
    //找到对应的lines
    for (std::map<int*, colorHidden>::iterator iter = m_colorTable.colorTaken.begin(); iter != m_colorTable.colorTaken.end(); iter++)
    {
        if (colorID == (iter->first)[6] && nullptr != iter->second.pGradient) //找到对应的line
        {
            QLinearGradient* lineGradientToBeHideShow = iter->second.pGradient;
            pIsHidden = &iter->second.isLaserHidden;
            for (std::list<QLinearGradient*>::iterator iterLineGradient = m_listpAreaLinearGradient.begin();
                iterLineGradient != m_listpAreaLinearGradient.end();
                iterLineGradient++)
            {
                indexOfLinesToBeHideShow++;
                if (*iterLineGradient == lineGradientToBeHideShow)
                {
                    break;
                }
            }
            break;
        }
    }
    //根据index，更新所有迭代器到需要隐藏显示的lines，points，gradients
    while (indexOfLinesToBeHideShow > 0)
    {
        iterLineseriesAreaSeriesLaser++;
        iterPushButtonShowHideLaser++;
        indexOfLinesToBeHideShow--;
    }
    //隐藏或者显示
    if (nullptr == pIsHidden)
    {
        return;
    }

    HideArea(iterLineseriesAreaSeriesLaser, m_pAxisXRange, m_pAxisZRange, m_chartTrapezoidLine);
    *pIsHidden = true;
    (*iterPushButtonShowHideLaser)->setText(QString::fromLocal8Bit("显示"));

}


void scheimCamera::tableWidgetItemChanged(QTableWidgetItem* item)
{
    int iRow = item->row();
    int iCol = item->column();
    int index = 0;
    std::list<CSchCamParamCal>::iterator  iterCal = m_calScheCamDataForUI.m_listCSchCamParamCal.begin();
    std::list<PointsSet>::iterator iterPointsSet = m_calScheCamDataForUI.m_listPointsSet.begin();
    int colorID = ui.tableWidget->model()->index(iRow, m_indexColColorID).data().toInt();
    int indexOfLinesToBeDelete = -1;
    //找到对应的lines
    for (std::map<int*, colorHidden>::iterator iter = m_colorTable.colorTaken.begin(); iter != m_colorTable.colorTaken.end(); iter++)
    {
        if (colorID == (iter->first)[6] && nullptr != iter->second.pGradient) //找到对应的line
        {
            QLinearGradient* lineGradientToBeDelete = iter->second.pGradient;
            for (std::list<QLinearGradient*>::iterator iterLineGradient = m_listpAreaLinearGradient.begin();
                iterLineGradient != m_listpAreaLinearGradient.end();
                iterLineGradient++)
            {
                indexOfLinesToBeDelete++;
                if (*iterLineGradient == lineGradientToBeDelete)
                {
                    break;
                }
            }
            break;
        }
    }
    index = indexOfLinesToBeDelete;
    while (indexOfLinesToBeDelete > 0)
    {
        iterCal++;
        iterPointsSet++;
        indexOfLinesToBeDelete--;
    }

    //更新row对应的计算器
    iterCal->m_SensorParam.iSensorWidth= ui.tableWidget->model()->index(iRow, 0).data().toInt();
    iterCal->m_SensorParam.iSensorHeight = ui.tableWidget->model()->index(iRow, 1).data().toInt();
    iterCal->m_SensorParam.dPixelSize= ui.tableWidget->model()->index(iRow, 2).data().toDouble();
    iterCal->m_dF= ui.tableWidget->model()->index(iRow, 3).data().toDouble();
    iterCal->m_dBaseDistance = ui.tableWidget->model()->index(iRow, 4).data().toDouble();
    iterCal->m_dCamAngle= ui.tableWidget->model()->index(iRow, 5).data().toDouble();
    iterCal->m_dCamVerticalHeight = ui.tableWidget->model()->index(iRow, 6).data().toDouble();
    iterCal->m_dCamHorizontalOffset= ui.tableWidget->model()->index(iRow, 7).data().toDouble();
    iterCal->m_dLaserFanAngle = ui.tableWidget->model()->index(iRow, 8).data().toDouble();

    //更新ui界面上的input
    ui.LineEditPixelSize->setText(QString::number(iterCal->m_SensorParam.dPixelSize, 'f', 3));
    ui.height->setText(QString::number(iterCal->m_SensorParam.iSensorHeight));
    ui.width->setText(QString::number(iterCal->m_SensorParam.iSensorWidth));
    ui.LineEditBaseDistance->setText(QString::number(iterCal->m_dBaseDistance, 'f', 3));
    ui.LineEditCameraAngle->setText(QString::number(iterCal->m_dCamAngle, 'f', 3));
    ui.LineEditFocalLength->setText(QString::number(iterCal->m_dF, 'f', 3));
    ui.lineEditLaserFan->setText(QString::number(iterCal->m_dLaserFanAngle, 'f', 3));
    ui.lineEditCamVerticalLength->setText(QString::number(iterCal->m_dCamVerticalHeight, 'f', 3));
    ui.lineEditCamHorizontalOffset->setText(QString::number(iterCal->m_dCamHorizontalOffset, 'f', 3));

    if (!isInputParamsValid())
    {
        for (int j = 0; j < 9; ++j)  //前9列为输入
        {
            ui.tableWidget->item(iRow, j)->setBackgroundColor(QColor(255, 90, 90));
        }
        for (int j = 9; j < 18; ++j) //9-17列为输出
        {
            if (ui.tableWidget->item(iRow, j))
                ui.tableWidget->item(iRow, j)->setText(QString("NaN"));
        }
        return;
    }
    else
    {
        for (int j = 0; j < 9; ++j)
        {
            if (ui.tableWidget->item(iRow, j))
                ui.tableWidget->item(iRow, j)->setBackgroundColor(QColor(255, 255, 255));
        }
    }
    
    m_calScheCamDataForUI.CalOutputParams(index);
    ui.tableWidget->item(iRow, 9)->setText(QString::number(iterCal->m_dScheimpflugAngle, 'f', 3));
    ui.tableWidget->item(iRow, 10)->setText(QString::number(iterCal->m_dMinWidthMeasurement, 'f', 3));
    ui.tableWidget->item(iRow, 11)->setText(QString::number(iterCal->m_dMaxWidthMeasurement, 'f', 3));
    ui.tableWidget->item(iRow, 12)->setText(QString::number(iterCal->m_dHeightMeasurementTop, 'f', 3));
    ui.tableWidget->item(iRow, 13)->setText(QString::number(iterCal->m_dHeightMeasurementBottom, 'f', 3));
    ui.tableWidget->item(iRow, 14)->setText(QString::number(iterCal->m_dWidthResolutionFovTop, 'f', 3));
    ui.tableWidget->item(iRow, 15)->setText(QString::number(iterCal->m_dWidthResolutionFovBottom, 'f', 3));
    ui.tableWidget->item(iRow, 16)->setText(QString::number(iterCal->m_dHeightResolutionFovTop, 'f', 3));
    ui.tableWidget->item(iRow, 17)->setText(QString::number(iterCal->m_dHeightResolutionFovBottom, 'f', 3));
    ShowLinesAndAreas(index);
    for (int iRow = 0; iRow < ui.tableWidget->rowCount(); ++iRow)
    {
        if (QString::fromLocal8Bit("显示") == ((QPushButton*)ui.tableWidget->cellWidget(iRow, 18))->text()) //相机显示隐藏列
            HideAreaCam(iRow);
        if (QString::fromLocal8Bit("显示") == ((QPushButton*)ui.tableWidget->cellWidget(iRow, 19))->text()) //激光显示隐藏列
            HideAreaLaser(iRow);
    }
    if (ui.tableWidget->item(iRow, 20)->text() == ui.comboBox_2->itemText(ui.comboBox_2->currentIndex()))
    {
        m_chartTrapezoidLine->m_pUpAndRightPoints = &(iterPointsSet->m_PointsUpAndRight);
        m_chartTrapezoidLine->m_pDownAndLeftPoints = &(iterPointsSet->m_PointsDownAndLeft);
        m_chartTrapezoidLine->m_pCSchCamParamCal = &(*iterCal);
    }
}

void scheimCamera::selectMeasurementLine(const QString& text)
{
    if (QString::fromLocal8Bit("红" )== text)
    {
        m_chartTrapezoidLine->y_line->setPen(QPen(QColor(213, 0, 0)));
    }
    if (QString::fromLocal8Bit("绿") == text)
    {
        m_chartTrapezoidLine->y_line->setPen(QPen(QColor(0, 213, 0)));
    }
    if (QString::fromLocal8Bit("蓝") == text)
    {
        m_chartTrapezoidLine->y_line->setPen(QPen(QColor(0, 0, 213)));
    }
    if (QString::fromLocal8Bit("黄") == text)
    {
        m_chartTrapezoidLine->y_line->setPen(QPen(QColor(213, 213, 0)));
    }
    if (QString::fromLocal8Bit("紫") == text)
    {
        m_chartTrapezoidLine->y_line->setPen(QPen(QColor(213, 0, 213)));
    }
    if (QString::fromLocal8Bit("青") == text)
    {
        m_chartTrapezoidLine->y_line->setPen(QPen(QColor(0, 213, 213)));
    }

    int colorID=-1;
    std::list<PointsSet>::iterator iterPointsSet = m_calScheCamDataForUI.m_listPointsSet.begin();
    std::list<CSchCamParamCal>::iterator   iterCalc = m_calScheCamDataForUI.m_listCSchCamParamCal.begin();
    int indexOfLinesToBeHideShow = -1;
    bool* pIsHidden = nullptr;
    for (int iRow = 0; iRow < ui.tableWidget->rowCount(); ++iRow)
    {
        if (ui.tableWidget->item(iRow, ui.tableWidget->columnCount() - 3)->text() == text)
            colorID = ui.tableWidget->model()->index(iRow, m_indexColColorID).data().toInt();
    }
    //找到对应的lines
    for (std::map<int*, colorHidden>::iterator iter = m_colorTable.colorTaken.begin(); iter != m_colorTable.colorTaken.end(); iter++)
    {
        if (colorID == (iter->first)[6] && nullptr != iter->second.pGradient) //找到对应的line
        {
            QLinearGradient* lineGradientToBeHideShow = iter->second.pGradient;
            //pIsHidden = &iter->second.isCamHidden;
            for (std::list<QLinearGradient*>::iterator iterLineGradient = m_listpAreaLinearGradient.begin();
                iterLineGradient != m_listpAreaLinearGradient.end();
                iterLineGradient++)
            {
                indexOfLinesToBeHideShow++;
                if (*iterLineGradient == lineGradientToBeHideShow)
                {
                    break;
                }
            }
            break;
        }
    }
    //根据index，更新所有迭代器到需要隐藏显示的lines，points，gradients
    while (indexOfLinesToBeHideShow > 0)
    {
        iterPointsSet++;
        iterCalc++;
        indexOfLinesToBeHideShow--;
    }
    m_chartTrapezoidLine->m_pUpAndRightPoints = &(iterPointsSet->m_PointsUpAndRight);
    m_chartTrapezoidLine->m_pDownAndLeftPoints = &(iterPointsSet->m_PointsDownAndLeft);
    m_chartTrapezoidLine->m_pCSchCamParamCal = &(*iterCalc);
}




void scheimCamera::DeleteLine(std::list<QLineSeries*>& listLines, std::list<QLineSeries*>::iterator& iterLineToBeDelete,
    QValueAxis*& axisIndependent, QValueAxis*& axisDependent, QChartView* chartView)
{
    (*iterLineToBeDelete)->detachAxis(axisIndependent);
    (*iterLineToBeDelete)->detachAxis(axisDependent);
    chartView->chart()->removeSeries(*iterLineToBeDelete);
    delete *iterLineToBeDelete;
    *iterLineToBeDelete = nullptr;
    listLines.erase(iterLineToBeDelete);
}


void scheimCamera::pushButtonShowHideCam()
{
    //对应隐藏显示的lines的迭代器
    //std::list<QLineSeries*>::iterator     iterLineseriesUpAndRight = m_listpLineseriesUpAndRight.begin();
    //std::list<QLineSeries*>::iterator     iterLineseriesDownAndLeft = m_listpLineseriesDownAndLeft.begin();
    std::list<QAreaSeries*>::iterator     iterLineseriesAreaSeries = m_listpAreaSeries.begin();
    std::list<QPushButton*>::iterator     iterPushButtonShowHideCam = m_listpPushButtonHideShowCam.begin();
    //找到对应的line,不显示
    QPushButton* pSenderObj = qobject_cast<QPushButton*>(sender());
    if (pSenderObj == nullptr)
    {
        return;
    }
    QModelIndex qIndex = ui.tableWidget->indexAt(QPoint(pSenderObj->frameGeometry().x(), pSenderObj->frameGeometry().y()));
    int row = qIndex.row();
    int column = qIndex.column();
    int colorID = ui.tableWidget->model()->index(row, m_indexColColorID).data().toInt();

    int indexOfLinesToBeHideShow = -1;
    bool* pIsHidden = nullptr;
    //找到对应的lines
    for (std::map<int*, colorHidden>::iterator iter = m_colorTable.colorTaken.begin(); iter != m_colorTable.colorTaken.end(); iter++)
    {
        if (colorID == (iter->first)[6] && nullptr != iter->second.pGradient) //找到对应的line
        {
            QLinearGradient* lineGradientToBeHideShow = iter->second.pGradient;
            pIsHidden = &iter->second.isCamHidden;
            for (std::list<QLinearGradient*>::iterator iterLineGradient = m_listpAreaLinearGradient.begin();
                iterLineGradient != m_listpAreaLinearGradient.end();
                iterLineGradient++)
            {
                indexOfLinesToBeHideShow++;
                if (*iterLineGradient == lineGradientToBeHideShow)
                {
                    break;
                }
            }
            break;
        }
    }
    //根据index，更新所有迭代器到需要隐藏显示的lines，points，gradients
    while (indexOfLinesToBeHideShow > 0)
    {
        //iterLineseriesUpAndRight++;
        //iterLineseriesDownAndLeft++;
        iterLineseriesAreaSeries++;
        iterPushButtonShowHideCam++;
        indexOfLinesToBeHideShow--;
    }
    //隐藏或者显示
    //if (nullptr == pIsHidden)
    //{
    //    return;
    //}
   // if (false == *pIsHidden)
    if((*iterPushButtonShowHideCam)->text()==QString::fromLocal8Bit("隐藏"))
    {
        HideArea(iterLineseriesAreaSeries,m_pAxisXRange, m_pAxisZRange, m_chartTrapezoidLine);
        *pIsHidden = true;
        (*iterPushButtonShowHideCam)->setText(QString::fromLocal8Bit("显示"));
    }
    else
    {
        ShowArea(iterLineseriesAreaSeries, m_pAxisXRange, m_pAxisZRange, m_chartTrapezoidLine);
        *pIsHidden = false;
        (*iterPushButtonShowHideCam)->setText(QString::fromLocal8Bit("隐藏"));
    }
}

void scheimCamera::pushButtonShowHideLaser()
{
    //对应隐藏显示的lines的迭代器
    std::list<QAreaSeries*>::iterator     iterLineseriesAreaSeriesLaser = m_listpAreaSeriesLaser.begin();
    std::list<QPushButton*>::iterator    iterPushButtonShowHideLaser = m_listpPushButtonHideShowLaser.begin();
    //找到对应的line,不显示
    QPushButton* pSenderObj = qobject_cast<QPushButton*>(sender());
    if (pSenderObj == nullptr)
    {
        return;
    }
    QModelIndex qIndex = ui.tableWidget->indexAt(QPoint(pSenderObj->frameGeometry().x(), pSenderObj->frameGeometry().y()));
    int row = qIndex.row();
    int column = qIndex.column();
    int colorID = ui.tableWidget->model()->index(row, m_indexColColorID).data().toInt();

    int indexOfLinesToBeHideShow = -1;
    bool* pIsHidden = nullptr;
    //找到对应的lines
    for (std::map<int*, colorHidden>::iterator iter = m_colorTable.colorTaken.begin(); iter != m_colorTable.colorTaken.end(); iter++)
    {
        if (colorID == (iter->first)[6] && nullptr != iter->second.pGradient) //找到对应的line
        {
            QLinearGradient* lineGradientToBeHideShow = iter->second.pGradient;
            pIsHidden = &iter->second.isLaserHidden;
            for (std::list<QLinearGradient*>::iterator iterLineGradient = m_listpAreaLinearGradient.begin();
                iterLineGradient != m_listpAreaLinearGradient.end();
                iterLineGradient++)
            {
                indexOfLinesToBeHideShow++;
                if (*iterLineGradient == lineGradientToBeHideShow)
                {
                    break;
                }
            }
            break;
        }
    }
    //根据index，更新所有迭代器到需要隐藏显示的lines，points，gradients
    while (indexOfLinesToBeHideShow > 0)
    {
        iterLineseriesAreaSeriesLaser++;
        iterPushButtonShowHideLaser++;
        indexOfLinesToBeHideShow--;
    }
    //隐藏或者显示
    //if (nullptr == pIsHidden)
    //{
    //    return;
    //}
    //if (false == *pIsHidden)
    if ((*iterPushButtonShowHideLaser)->text() == QString::fromLocal8Bit("隐藏"))
    {
        HideArea(iterLineseriesAreaSeriesLaser, m_pAxisXRange, m_pAxisZRange, m_chartTrapezoidLine);
        *pIsHidden = true;
        (*iterPushButtonShowHideLaser)->setText(QString::fromLocal8Bit("显示"));
    }
    else
    {
        ShowArea(iterLineseriesAreaSeriesLaser, m_pAxisXRange, m_pAxisZRange, m_chartTrapezoidLine);
        *pIsHidden = false;
        (*iterPushButtonShowHideLaser)->setText(QString::fromLocal8Bit("隐藏"));
    }
}

void scheimCamera::pushButtonRefresh()
{
    m_calScheCamDataForUI.UpdatePointsRange();
    RangesMaxAndMin& range = m_calScheCamDataForUI.m_rangesMaxAndMin;
    flushAxisAndLines(m_listpLineseriesForMeasureRange, m_pAxisZForMeasureRange, m_pAxisXForMeasureRange, m_chartXZRange,
        range.rangeZMin, range.rangeZMax, range.rangeXMin, range.rangeXMax);
    flushAxisAndLines(m_listpLineseriesForWidthResolution, m_pAxisZForWidthResolution, m_pAxisWidthResolution, m_chartXresolutionZ,
        range.rangeZMin, range.rangeZMax, range.rangeXMinResolution, range.rangeXMaxResolution);
    flushAxisAndLines(m_listpLineseriesForHeightResolution, m_pAxisZForHeightResolution, m_pAxisHeightResolution, m_chartZresolutionZ,
        range.rangeZMin, range.rangeZMax, range.rangeZMinResolution, range.rangeZMaxResolution);
    flushAxisAndLines(m_listpLineseriesForHeightWidthResolution, m_pAxisHeightForHeightWidthResolution, m_pAxisWidthForHeightWidthResolution,
        m_chartXresolutionZresolution, range.rangeZMinResolution, range.rangeZMaxResolution,
        range.rangeXMinResolution, range.rangeXMaxResolution);
    flushAxisAndAreas(m_listpAreaSeries, m_listpAreaSeriesLaser, m_pAxisXRange, m_pAxisZRange, m_chartTrapezoidLine,
        range.rangeTrapezoidXMin, range.rangeTrapezoidXMax, range.rangeTrapezoidZMin, range.rangeTrapezoidZMax);
    
    for (std::list<QPushButton*>::iterator iter = m_listpPushButtonHideShowCam.begin(); iter != m_listpPushButtonHideShowCam.end(); ++iter)
    {
        (*iter)->setText(QString::fromLocal8Bit("隐藏"));
    }
    for (std::list<QPushButton*>::iterator iter = m_listpPushButtonHideShowLaser.begin(); iter != m_listpPushButtonHideShowLaser.end(); ++iter)
    {
        (*iter)->setText(QString::fromLocal8Bit("隐藏"));
    }
}


bool scheimCamera::SaveInputParams()
{
    bool bRet = false;
    bool GotFreeColor = false;
    int index = 0;
    QColor dark;
    QColor light;
    std::string color;
    Qt::GlobalColor qtColor;
    std::map<int*, colorHidden>::iterator iter = m_colorTable.colorTaken.begin();
    for (;iter != m_colorTable.colorTaken.end(); iter++)
    {
        if (nullptr == iter->second.pGradient)
        {
            dark = QColor((iter->first)[0], (iter->first)[1], (iter->first)[2]);
            light = QColor((iter->first)[3], (iter->first)[4], (iter->first)[5]);
            switch ((iter->first)[6])
            {
            case 0:
                color = "红";
                qtColor = Qt::red;
                break;
            case 1:
                color = "绿";
                qtColor = Qt::green;
                break;
            case 2:
                color = "蓝";
                qtColor = Qt::blue;
                break;
            case 3:
                color = "黄";
                qtColor = Qt::yellow;
                break;
            case 4:
                color = "紫";
                qtColor = Qt::magenta;
                break;
            case 5:
                color = "青";
                qtColor = Qt::cyan;
                break;
            default:
                break;
            }
            GotFreeColor = true;
            break;
        }
    }
    if (!GotFreeColor)
    {
        m_upTo6MessageBox = QMessageBox::critical(this, QString::fromLocal8Bit(" "), QString::fromLocal8Bit("最多6个方案！"));
        //弹出提示框
        return bRet;
    }
    m_calScheCamDataForUI.m_listCSchCamParamCal.emplace_back();
    m_calScheCamDataForUI.m_listPointsSet.push_back(PointsSet());
    m_listpLineseriesForMeasureRange.push_back(std::move(new QLineSeries()));
    m_listpLineseriesForMeasureRange.back()->setPen(QPen(qtColor,2));
    m_listpLineseriesForMeasureRange.back()->setName(QString::fromLocal8Bit("方案")+(QString(std::to_string(m_listpLineseriesForMeasureRange.size()).c_str())+" "));
    m_listpLineseriesForWidthResolution.push_back(std::move(new QLineSeries()));
    m_listpLineseriesForWidthResolution.back()->setPen(QPen(qtColor,2));
    m_listpLineseriesForWidthResolution.back()->setName(QString::fromLocal8Bit("方案") + (QString(std::to_string(m_listpLineseriesForWidthResolution.size()).c_str()) + " "));
    m_listpLineseriesForHeightResolution.push_back(std::move(new QLineSeries()));
    m_listpLineseriesForHeightResolution.back()->setPen(QPen(qtColor,2));
    m_listpLineseriesForHeightResolution.back()->setName(QString::fromLocal8Bit("方案") + (QString(std::to_string(m_listpLineseriesForHeightResolution.size()).c_str()) + " "));
    m_listpLineseriesForHeightWidthResolution.push_back(std::move(new QLineSeries()));
    m_listpLineseriesForHeightWidthResolution.back()->setPen(QPen(qtColor,2));
    m_listpLineseriesForHeightWidthResolution.back()->setName(QString::fromLocal8Bit("方案") + (QString(std::to_string(m_listpLineseriesForHeightWidthResolution.size()).c_str()) + " "));

    m_listpLineseriesUpAndRight.push_back(std::move(new QLineSeries()));
    m_listpLineseriesDownAndLeft.push_back(std::move(new QLineSeries()));
    m_listpLineseriesLaserOrigin.push_back(std::move(new QLineSeries()));
    m_listpLineseriesLaserBottom.push_back(std::move(new QLineSeries()));
    m_listpAreaSeries.push_back(std::move(new QAreaSeries(m_listpLineseriesUpAndRight.back(), m_listpLineseriesDownAndLeft.back())));
    m_listpAreaSeries.back()->setName(QString(std::to_string(m_listpAreaSeries.size()).c_str())+ QString::fromLocal8Bit(":相机(梯形)"));
    m_listpAreaSeriesLaser.push_back(std::move(new QAreaSeries(m_listpLineseriesLaserOrigin.back(),
        m_listpLineseriesLaserBottom.back())));
    m_listpAreaSeriesLaser.back()->setName(QString(std::to_string(m_listpAreaSeriesLaser.size()).c_str())+ QString::fromLocal8Bit(":激光(三角)"));
    m_listpAreaSeries.back()->setOpacity(0.3); //透明度
    m_listpAreaSeriesLaser.back()->setOpacity(0.3); //透明度
    m_listpAreaLinearGradient.push_back(std::move(new QLinearGradient(QPointF(0, 0), QPointF(0, 1))));
    m_listpAreaLinearGradient.back()->setColorAt(0.0, light);
    m_listpAreaLinearGradient.back()->setColorAt(1.0, light);
    iter->second.pGradient = m_listpAreaLinearGradient.back();
    m_listpAreaLinearGradient.back()->setCoordinateMode(QGradient::ObjectMode);
    m_listpAreaSeriesLaser.back()->setBrush(*m_listpAreaLinearGradient.back());
    m_listpAreaLaserLinearGradient.push_back(std::move(new QLinearGradient(QPointF(0, 0), QPointF(0, 1))));
    m_listpAreaLaserLinearGradient.back()->setColorAt(0.0, dark);
    m_listpAreaLaserLinearGradient.back()->setColorAt(1.0, dark);
    m_listpAreaLaserLinearGradient.back()->setCoordinateMode(QGradient::ObjectMode);
    m_listpAreaSeries.back()->setBrush(*m_listpAreaLaserLinearGradient.back());
    m_listpPushButtonDelete.push_back(std::move(new QPushButton(QString::fromLocal8Bit("删除"))));
    m_listpPushButtonHideShowCam.push_back(std::move(new QPushButton(QString::fromLocal8Bit("隐藏"))));
    m_listpPushButtonHideShowLaser.push_back(std::move(new QPushButton(QString::fromLocal8Bit("隐藏"))));
    index = m_calScheCamDataForUI.m_listCSchCamParamCal.size() - 1;
    if (index < 0)
    {
        return bRet;
    }
    SetInputParams(index);

    ui.tableWidget->insertRow(ui.tableWidget->rowCount());
    int TableRowIndex = ui.tableWidget->rowCount() - 1;
    QPushButton* pushButtonDelete = m_listpPushButtonDelete.back();
    QPushButton* pushButtonHideShowCam = m_listpPushButtonHideShowCam.back();
    QPushButton* pushButtonHideShowLaser = m_listpPushButtonHideShowLaser.back();
    ui.tableWidget->setCellWidget(TableRowIndex, 18, pushButtonHideShowCam);
    ui.tableWidget->setCellWidget(TableRowIndex, 19, pushButtonHideShowLaser);
    ui.tableWidget->setItem(TableRowIndex, 20, new QTableWidgetItem(QString::fromLocal8Bit(color.c_str())));
    ui.tableWidget->setCellWidget(TableRowIndex, 21, pushButtonDelete);
    ui.tableWidget->setItem(TableRowIndex, 22, new QTableWidgetItem(QString::number((iter->first)[6])));
    ui.comboBox_2->addItem(QString::fromLocal8Bit(color.c_str()));

    connect(pushButtonDelete, &QPushButton::clicked, this, &scheimCamera::pushButtonDelete);
    connect(pushButtonHideShowCam, &QPushButton::clicked, this, &scheimCamera::pushButtonShowHideCam);
    connect(pushButtonHideShowLaser, &QPushButton::clicked, this, &scheimCamera::pushButtonShowHideLaser);
    bRet = true;
    return bRet;
}


CCalScheCamDataForUI::CCalScheCamDataForUI()
{
}

CCalScheCamDataForUI::~CCalScheCamDataForUI()
{
}



void CCalScheCamDataForUI::CalOutputParams(int index)
{
    std::list<CSchCamParamCal>::iterator iter = m_listCSchCamParamCal.begin();
    while (index > 0)
    {
        iter++;
        index--;
    }
    iter->Calculate();
}



void CCalScheCamDataForUI::CalLinesPoints(int index)
{
    std::list<CSchCamParamCal>::iterator iterCSchCamParamCal = m_listCSchCamParamCal.begin();
    std::list<PointsSet>::iterator iterPoinsSet = m_listPointsSet.begin();
    while (index > 0)
    {
        iterCSchCamParamCal++;
        iterPoinsSet++;
        index--;
    }
    double toRadian = std::acos(-1) / 180;
    if (LaserFullOverCam == iterCSchCamParamCal->LaserCamFov|| CamFullOverLaser == iterCSchCamParamCal->LaserCamFov)
    {
        iterPoinsSet->m_PointsForMeasureRange[0] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementTop, 
                                                            iterCSchCamParamCal->m_dMinWidthMeasurement);
        iterPoinsSet->m_PointsForMeasureRange[2] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementBottom,
                                                             iterCSchCamParamCal->m_dMaxWidthMeasurement);
        iterPoinsSet->m_PointsForMeasureRange[1] = (iterPoinsSet->m_PointsForMeasureRange[0] + iterPoinsSet->m_PointsForMeasureRange[2]) / 2;
        iterPoinsSet->m_PointsForWidthResolution[0] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementTop, 
                                                        iterCSchCamParamCal->m_dWidthResolutionFovTop);
        iterPoinsSet->m_PointsForWidthResolution[2] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementBottom,
                                                        iterCSchCamParamCal->m_dWidthResolutionFovBottom);
        iterPoinsSet->m_PointsForWidthResolution[1] = (iterPoinsSet->m_PointsForWidthResolution[0]+ iterPoinsSet->m_PointsForWidthResolution[2]) / 2;
        iterPoinsSet->m_PointsForHeightResolution[0] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementTop,
                                                                iterCSchCamParamCal->m_dHeightResolutionFovTop);
        iterPoinsSet->m_PointsForHeightResolution[2] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementBottom,
                                                                iterCSchCamParamCal->m_dHeightResolutionFovBottom);
        iterPoinsSet->m_PointsForHeightResolution[1] = (iterPoinsSet->m_PointsForHeightResolution[0]+ iterPoinsSet->m_PointsForHeightResolution[2]) / 2;
        iterPoinsSet->m_PointsForHeightWidthResolution[0] = QPointF(iterCSchCamParamCal->m_dHeightResolutionFovTop,
                                                                    iterCSchCamParamCal->m_dWidthResolutionFovTop);
        iterPoinsSet->m_PointsForHeightWidthResolution[2] = QPointF(iterCSchCamParamCal->m_dHeightResolutionFovBottom,
                                                                    iterCSchCamParamCal->m_dWidthResolutionFovBottom);
        iterPoinsSet->m_PointsForHeightWidthResolution[1] = (iterPoinsSet->m_PointsForHeightWidthResolution[0]+ iterPoinsSet->m_PointsForHeightWidthResolution[2]) / 2;
    }
    else if (LaserIntersectCam == iterCSchCamParamCal->LaserCamFov)
    {
        iterPoinsSet->m_PointsForMeasureRange[0] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementTop, 
                                                iterCSchCamParamCal->m_dMinWidthMeasurement);
        iterPoinsSet->m_PointsForMeasureRange[1] = QPointF(iterCSchCamParamCal->m_dHeightLaserFovIntersection,
                                                            iterCSchCamParamCal->m_dLaserWidthAtFovIntersection);
        iterPoinsSet->m_PointsForMeasureRange[2] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementBottom,
                                                             iterCSchCamParamCal->m_dMaxWidthMeasurement);
        iterPoinsSet->m_PointsForWidthResolution[0] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementTop,
                                                                iterCSchCamParamCal->m_dWidthResolutionFovTop);
        iterPoinsSet->m_PointsForWidthResolution[1] = QPointF(iterCSchCamParamCal->m_dHeightLaserFovIntersection,
            iterCSchCamParamCal->m_dLaserWidthAtFovIntersection / iterCSchCamParamCal->m_SensorParam.iSensorWidth);
        iterPoinsSet->m_PointsForWidthResolution[2] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementBottom,
                                                                iterCSchCamParamCal->m_dWidthResolutionFovBottom);
        iterPoinsSet->m_PointsForHeightResolution[0] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementTop,
                                                                 iterCSchCamParamCal->m_dHeightResolutionFovTop);
        iterPoinsSet->m_PointsForHeightResolution[1] = QPointF(iterCSchCamParamCal->m_dHeightLaserFovIntersection,
            iterCSchCamParamCal->m_dLaserWidthAtFovIntersection / iterCSchCamParamCal->m_SensorParam.iSensorWidth / std::sin(iterCSchCamParamCal->m_dCamAngle * toRadian));
        iterPoinsSet->m_PointsForHeightResolution[2] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementBottom,
                                                                iterCSchCamParamCal->m_dHeightResolutionFovBottom);
        iterPoinsSet->m_PointsForHeightWidthResolution[0] = QPointF(iterCSchCamParamCal->m_dHeightResolutionFovTop,
                                                                iterCSchCamParamCal->m_dWidthResolutionFovTop);
        iterPoinsSet->m_PointsForHeightWidthResolution[1] = QPointF(iterCSchCamParamCal->m_dLaserWidthAtFovIntersection
            / iterCSchCamParamCal->m_SensorParam.iSensorWidth / std::sin(iterCSchCamParamCal->m_dCamAngle * toRadian),
            iterCSchCamParamCal->m_dLaserWidthAtFovIntersection
            / iterCSchCamParamCal->m_SensorParam.iSensorWidth);
        iterPoinsSet->m_PointsForHeightWidthResolution[2] = QPointF(iterCSchCamParamCal->m_dHeightResolutionFovBottom,
                                                                iterCSchCamParamCal->m_dWidthResolutionFovBottom);
    }
   /* else if (CamFullOverLaser == iterCSchCamParamCal->LaserCamFov)
    {
        iterPoinsSet->m_PointsForMeasureRange[0] = QPointF(dHeightIndex, iterCSchCamParamCal->m_dMinWidthMeasurement);
        iterPoinsSet->m_PointsForMeasureRange[1] = QPointF(dHeightIndex + iterCSchCamParamCal->m_dHeightMeasurement / 2,
            (iterCSchCamParamCal->m_dMinWidthMeasurement + iterCSchCamParamCal->m_dMaxWidthMeasurement) / 2);
        iterPoinsSet->m_PointsForMeasureRange[2] = QPointF(dHeightIndex + iterCSchCamParamCal->m_dHeightMeasurement,
            iterCSchCamParamCal->m_dMaxWidthMeasurement);
        iterPoinsSet->m_PointsForWidthResolution[0] = QPointF(dHeightIndex, iterCSchCamParamCal->m_dMinWidthMeasurement / iterCSchCamParamCal->m_SensorParam.iSensorWidth);
        iterPoinsSet->m_PointsForWidthResolution[1] = QPointF(dHeightIndex + iterCSchCamParamCal->m_dHeightMeasurement / 2,
            (iterCSchCamParamCal->m_dMinWidthMeasurement + iterCSchCamParamCal->m_dMaxWidthMeasurement) / 2 / iterCSchCamParamCal->m_SensorParam.iSensorWidth);
        iterPoinsSet->m_PointsForWidthResolution[2] = QPointF(dHeightIndex + iterCSchCamParamCal->m_dHeightMeasurement,
            iterCSchCamParamCal->m_dMaxWidthMeasurement / iterCSchCamParamCal->m_SensorParam.iSensorWidth);
        iterPoinsSet->m_PointsForHeightResolution[0] = QPointF(dHeightIndex, iterCSchCamParamCal->m_dMinWidthMeasurement / iterCSchCamParamCal->m_SensorParam.iSensorWidth
            / std::sin(iterCSchCamParamCal->m_dCamAngle * toRadian));
        iterPoinsSet->m_PointsForHeightResolution[1] = QPointF(dHeightIndex + iterCSchCamParamCal->m_dHeightMeasurement / 2,
            (iterCSchCamParamCal->m_dMinWidthMeasurement + iterCSchCamParamCal->m_dMaxWidthMeasurement) / 2 / iterCSchCamParamCal->m_SensorParam.iSensorWidth
            / std::sin(iterCSchCamParamCal->m_dCamAngle * toRadian));
        iterPoinsSet->m_PointsForHeightResolution[2] = QPointF(dHeightIndex + iterCSchCamParamCal->m_dHeightMeasurement,
            iterCSchCamParamCal->m_dMaxWidthMeasurement / iterCSchCamParamCal->m_SensorParam.iSensorWidth
            / std::sin(iterCSchCamParamCal->m_dCamAngle * toRadian));
        iterPoinsSet->m_PointsForHeightWidthResolution[0] = QPointF(iterCSchCamParamCal->m_dMinWidthMeasurement / iterCSchCamParamCal->m_SensorParam.iSensorWidth
            / std::sin(iterCSchCamParamCal->m_dCamAngle * toRadian),
            iterCSchCamParamCal->m_dMinWidthMeasurement / iterCSchCamParamCal->m_SensorParam.iSensorWidth);
        iterPoinsSet->m_PointsForHeightWidthResolution[1] = QPointF((iterCSchCamParamCal->m_dMinWidthMeasurement + iterCSchCamParamCal->m_dMaxWidthMeasurement) / 2
            / iterCSchCamParamCal->m_SensorParam.iSensorWidth
            / std::sin(iterCSchCamParamCal->m_dCamAngle * toRadian),
            (iterCSchCamParamCal->m_dMinWidthMeasurement + iterCSchCamParamCal->m_dMaxWidthMeasurement) / 2
            / iterCSchCamParamCal->m_SensorParam.iSensorWidth);
        iterPoinsSet->m_PointsForHeightWidthResolution[2] = QPointF(iterCSchCamParamCal->m_dMaxWidthMeasurement / iterCSchCamParamCal->m_SensorParam.iSensorWidth
            / std::sin(iterCSchCamParamCal->m_dCamAngle * toRadian),
            iterCSchCamParamCal->m_dMaxWidthMeasurement / iterCSchCamParamCal->m_SensorParam.iSensorWidth);
    }*/
    else if(CamTiltTooMuchAndFullOverLaser== iterCSchCamParamCal->LaserCamFov)
    {
        iterPoinsSet->m_PointsForMeasureRange[0] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementTop,
            iterCSchCamParamCal->m_dMinWidthMeasurement);
        iterPoinsSet->m_PointsForMeasureRange[1] = iterPoinsSet->m_PointsForMeasureRange[0];
        iterPoinsSet->m_PointsForMeasureRange[2] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementBottom,
            iterCSchCamParamCal->m_dMaxWidthMeasurement);
        iterPoinsSet->m_PointsForWidthResolution[0] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementTop,
                                                            iterCSchCamParamCal->m_dWidthResolutionFovTop);
        iterPoinsSet->m_PointsForWidthResolution[1] = iterPoinsSet->m_PointsForWidthResolution[0];
        iterPoinsSet->m_PointsForWidthResolution[2] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementBottom,
                                                            iterCSchCamParamCal->m_dWidthResolutionFovBottom);
        iterPoinsSet->m_PointsForHeightResolution[0] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementTop,
                                                                iterCSchCamParamCal->m_dHeightResolutionFovTop);
        iterPoinsSet->m_PointsForHeightResolution[1] = iterPoinsSet->m_PointsForHeightResolution[0];
        iterPoinsSet->m_PointsForHeightResolution[2] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementBottom,
                                                                iterCSchCamParamCal->m_dHeightResolutionFovBottom);
        iterPoinsSet->m_PointsForHeightWidthResolution[0] = QPointF(iterCSchCamParamCal->m_dHeightResolutionFovTop,
                                                                        iterCSchCamParamCal->m_dWidthResolutionFovTop);
        iterPoinsSet->m_PointsForHeightWidthResolution[1] = iterPoinsSet->m_PointsForHeightWidthResolution[0];
        iterPoinsSet->m_PointsForHeightWidthResolution[2] = QPointF(iterCSchCamParamCal->m_dHeightResolutionFovBottom,
                                                                        iterCSchCamParamCal->m_dWidthResolutionFovBottom);
    }
    else if (CamTiltTooMuchAndIntersect == iterCSchCamParamCal->LaserCamFov)
    {
        iterPoinsSet->m_PointsForMeasureRange[0] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementTop,
                                                            iterCSchCamParamCal->m_dMinWidthMeasurement);
        iterPoinsSet->m_PointsForMeasureRange[1] = QPointF(iterCSchCamParamCal->m_dHeightLaserFovIntersection,
                                                    iterCSchCamParamCal->m_dLaserWidthAtFovIntersection);
        iterPoinsSet->m_PointsForMeasureRange[2] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementBottom,
                                                             iterCSchCamParamCal->m_dMaxWidthMeasurement);
        iterPoinsSet->m_PointsForWidthResolution[0] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementTop,
                                                                iterCSchCamParamCal->m_dWidthResolutionFovTop);
        iterPoinsSet->m_PointsForWidthResolution[1] = QPointF(iterCSchCamParamCal->m_dHeightLaserFovIntersection,
            iterCSchCamParamCal->m_dLaserWidthAtFovIntersection / iterCSchCamParamCal->m_SensorParam.iSensorWidth);
        iterPoinsSet->m_PointsForWidthResolution[2] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementBottom,
                                                             iterCSchCamParamCal->m_dWidthResolutionFovBottom);
        iterPoinsSet->m_PointsForHeightResolution[0] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementTop,
                                                                iterCSchCamParamCal->m_dHeightResolutionFovTop);
        iterPoinsSet->m_PointsForHeightResolution[1] = QPointF(iterCSchCamParamCal->m_dHeightLaserFovIntersection,
            iterCSchCamParamCal->m_dLaserWidthAtFovIntersection / iterCSchCamParamCal->m_SensorParam.iSensorWidth 
                                / std::sin(iterCSchCamParamCal->m_dCamAngle * toRadian));
        iterPoinsSet->m_PointsForHeightResolution[2] = QPointF(iterCSchCamParamCal->m_dHeightMeasurementBottom,
                                                                    iterCSchCamParamCal->m_dHeightResolutionFovBottom);
        iterPoinsSet->m_PointsForHeightWidthResolution[0] = QPointF(iterCSchCamParamCal->m_dHeightResolutionFovTop,
                                                            iterCSchCamParamCal->m_dWidthResolutionFovTop);
        iterPoinsSet->m_PointsForHeightWidthResolution[1] = QPointF(iterCSchCamParamCal->m_dLaserWidthAtFovIntersection
            / iterCSchCamParamCal->m_SensorParam.iSensorWidth
            / std::sin(iterCSchCamParamCal->m_dCamAngle * toRadian),
            iterCSchCamParamCal->m_dLaserWidthAtFovIntersection / iterCSchCamParamCal->m_SensorParam.iSensorWidth);
        iterPoinsSet->m_PointsForHeightWidthResolution[2] = QPointF(iterCSchCamParamCal->m_dHeightResolutionFovBottom,
                                                             iterCSchCamParamCal->m_dWidthResolutionFovBottom);
    }
}



void CCalScheCamDataForUI::CalAreasPoints(int index)
{
    std::list<CSchCamParamCal>::iterator iterCSchCamParamCal = m_listCSchCamParamCal.begin();
    std::list<PointsSet>::iterator iterPoinsSet = m_listPointsSet.begin();
    while (index > 0)
    {
        iterCSchCamParamCal++;
        iterPoinsSet++;
        index--;
    }
    double dHorizontalOffset = iterCSchCamParamCal->m_dCamHorizontalOffset;
    //相机
    if (LaserFullOverCam == iterCSchCamParamCal->LaserCamFov || CamFullOverLaser == iterCSchCamParamCal->LaserCamFov)
    {
        iterPoinsSet->m_PointsUpAndRight[0] = QPointF(-iterCSchCamParamCal->m_dMaxWidthMeasurement / 2 + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightMeasurementBottom);
        iterPoinsSet->m_PointsUpAndRight[1] = QPointF(iterCSchCamParamCal->m_dMaxWidthMeasurement / 2 + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightMeasurementBottom);
        iterPoinsSet->m_PointsUpAndRight[2] = QPointF((iterCSchCamParamCal->m_dMaxWidthMeasurement + iterCSchCamParamCal->m_dMinWidthMeasurement) / 2 / 2
            + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightMeasurementTop + iterCSchCamParamCal->m_dHeightMeasure / 2);
        iterPoinsSet->m_PointsDownAndLeft[0] = QPointF(-(iterCSchCamParamCal->m_dMaxWidthMeasurement + iterCSchCamParamCal->m_dMinWidthMeasurement) / 2 / 2
            + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightMeasurementTop + iterCSchCamParamCal->m_dHeightMeasure / 2);
        iterPoinsSet->m_PointsDownAndLeft[1] = QPointF(-iterCSchCamParamCal->m_dMinWidthMeasurement / 2 + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightMeasurementTop);
        iterPoinsSet->m_PointsDownAndLeft[2] = QPointF(iterCSchCamParamCal->m_dMinWidthMeasurement / 2 + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightMeasurementTop);
    }
    else if (LaserIntersectCam == iterCSchCamParamCal->LaserCamFov)
    {
        iterPoinsSet->m_PointsUpAndRight[0] = QPointF(-iterCSchCamParamCal->m_dMaxWidthMeasurement / 2 + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightMeasurementBottom);
        iterPoinsSet->m_PointsUpAndRight[1] = QPointF(iterCSchCamParamCal->m_dMaxWidthMeasurement / 2 + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightMeasurementBottom);
        iterPoinsSet->m_PointsUpAndRight[2] = QPointF(iterCSchCamParamCal->m_dLaserWidthAtFovIntersection/2 + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightLaserFovIntersection);
        iterPoinsSet->m_PointsDownAndLeft[0] = QPointF(-iterCSchCamParamCal->m_dLaserWidthAtFovIntersection / 2 + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightLaserFovIntersection);
        iterPoinsSet->m_PointsDownAndLeft[1] = QPointF(-iterCSchCamParamCal->m_dMinWidthMeasurement / 2 + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightMeasurementTop);
        iterPoinsSet->m_PointsDownAndLeft[2] = QPointF(iterCSchCamParamCal->m_dMinWidthMeasurement / 2 + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightMeasurementTop);
    }
    else if (CamTiltTooMuchAndFullOverLaser == iterCSchCamParamCal->LaserCamFov)
    {
        iterPoinsSet->m_PointsUpAndRight[0] = QPointF(-iterCSchCamParamCal->m_dMaxWidthMeasurement / 2 + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightMeasurementBottom);
        iterPoinsSet->m_PointsUpAndRight[1] = QPointF(iterCSchCamParamCal->m_dMaxWidthMeasurement / 2 + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightMeasurementBottom);
        iterPoinsSet->m_PointsUpAndRight[2] = QPointF((iterCSchCamParamCal->m_dMaxWidthMeasurement + iterCSchCamParamCal->m_dMinWidthMeasurement) / 2 / 2
            + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightMeasurementTop + iterCSchCamParamCal->m_dHeightMeasure / 2);
        iterPoinsSet->m_PointsDownAndLeft[0] = QPointF(-(iterCSchCamParamCal->m_dMaxWidthMeasurement + iterCSchCamParamCal->m_dMinWidthMeasurement) / 2 / 2
            + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightMeasurementTop + iterCSchCamParamCal->m_dHeightMeasure / 2);
        iterPoinsSet->m_PointsDownAndLeft[1] = QPointF(-iterCSchCamParamCal->m_dMinWidthMeasurement / 2 + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightMeasurementTop);
        iterPoinsSet->m_PointsDownAndLeft[2] = QPointF(iterCSchCamParamCal->m_dMinWidthMeasurement / 2 + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightMeasurementTop);
    }
    else if (CamTiltTooMuchAndIntersect == iterCSchCamParamCal->LaserCamFov)
    {
        iterPoinsSet->m_PointsUpAndRight[0] = QPointF(-iterCSchCamParamCal->m_dMaxWidthMeasurement / 2 + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightMeasurementBottom);
        iterPoinsSet->m_PointsUpAndRight[1] = QPointF(iterCSchCamParamCal->m_dMaxWidthMeasurement / 2 + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightMeasurementBottom);
        iterPoinsSet->m_PointsUpAndRight[2] = QPointF(iterCSchCamParamCal->m_dLaserWidthAtFovIntersection/2+ dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightLaserFovIntersection);
        iterPoinsSet->m_PointsDownAndLeft[0] = QPointF(-iterCSchCamParamCal->m_dLaserWidthAtFovIntersection / 2 + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightLaserFovIntersection);
        iterPoinsSet->m_PointsDownAndLeft[1] = QPointF(-iterCSchCamParamCal->m_dMinWidthMeasurement / 2 + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightMeasurementTop);
        iterPoinsSet->m_PointsDownAndLeft[2] = QPointF(iterCSchCamParamCal->m_dMinWidthMeasurement / 2 + dHorizontalOffset,
            iterCSchCamParamCal->m_dHeightMeasurementTop);
    }
    //激光
    iterPoinsSet->m_PointsLaserOrigin[0] = QPointF(-0.00001 + dHorizontalOffset, 0 + iterCSchCamParamCal->m_dCamVerticalHeight);
    iterPoinsSet->m_PointsLaserOrigin[1] = QPointF(0.00001 + dHorizontalOffset, 0 + iterCSchCamParamCal->m_dCamVerticalHeight);
    iterPoinsSet->m_PointsLaserBottom[0] = QPointF(-iterCSchCamParamCal->m_dLaserWidthFovBottom / 2 + dHorizontalOffset, 
        iterCSchCamParamCal->m_dHeightMeasurementBottom);
    iterPoinsSet->m_PointsLaserBottom[1] = QPointF(iterCSchCamParamCal->m_dLaserWidthFovBottom / 2 + dHorizontalOffset, 
        iterCSchCamParamCal->m_dHeightMeasurementBottom);
}

void CCalScheCamDataForUI::UpdatePointsRange()
{
    m_rangesMaxAndMin.rangeZMax = DBL_MIN;
    m_rangesMaxAndMin.rangeXMax = DBL_MIN;
    m_rangesMaxAndMin.rangeZMin = DBL_MAX;
    m_rangesMaxAndMin.rangeXMin = DBL_MAX;
    m_rangesMaxAndMin.rangeXMaxResolution = DBL_MIN;
    m_rangesMaxAndMin.rangeXMinResolution = DBL_MAX;
    m_rangesMaxAndMin.rangeZMaxResolution = DBL_MIN;
    m_rangesMaxAndMin.rangeZMinResolution = DBL_MAX;
    m_rangesMaxAndMin.rangeTrapezoidXMax = DBL_MIN;
    m_rangesMaxAndMin.rangeTrapezoidXMin = DBL_MAX;
    m_rangesMaxAndMin.rangeTrapezoidZMax = DBL_MIN;
    m_rangesMaxAndMin.rangeTrapezoidZMin = DBL_MAX;
    for (std::list<PointsSet>::iterator iter = m_listPointsSet.begin(); iter != m_listPointsSet.end(); ++iter)
    {
        for (int i = 0; i < iter->m_PointsForMeasureRange.size(); ++i)
        {
            m_rangesMaxAndMin.rangeZMin = std::min(m_rangesMaxAndMin.rangeZMin, iter->m_PointsForMeasureRange[i].x());
            m_rangesMaxAndMin.rangeZMax = std::max(m_rangesMaxAndMin.rangeZMax, iter->m_PointsForMeasureRange[i].x());
            m_rangesMaxAndMin.rangeXMin = std::min(m_rangesMaxAndMin.rangeXMin, iter->m_PointsForMeasureRange[i].y());
            m_rangesMaxAndMin.rangeXMax = std::max(m_rangesMaxAndMin.rangeXMax, iter->m_PointsForMeasureRange[i].y());
        }
        for (int i = 0; i < iter->m_PointsForWidthResolution.size(); ++i)
        {
            m_rangesMaxAndMin.rangeXMinResolution = std::min(m_rangesMaxAndMin.rangeXMinResolution, iter->m_PointsForWidthResolution[i].y());
            m_rangesMaxAndMin.rangeXMaxResolution = std::max(m_rangesMaxAndMin.rangeXMaxResolution, iter->m_PointsForWidthResolution[i].y());
        }
        for (int i = 0; i < iter->m_PointsForHeightResolution.size(); ++i)
        {
            m_rangesMaxAndMin.rangeZMinResolution = std::min(m_rangesMaxAndMin.rangeZMinResolution, iter->m_PointsForHeightResolution[i].y());
            m_rangesMaxAndMin.rangeZMaxResolution = std::max(m_rangesMaxAndMin.rangeZMaxResolution, iter->m_PointsForHeightResolution[i].y());
        }
        for (int i = 0; i < iter->m_PointsUpAndRight.size(); ++i)
        {
            m_rangesMaxAndMin.rangeTrapezoidXMin = std::min(m_rangesMaxAndMin.rangeTrapezoidXMin, iter->m_PointsUpAndRight[i].x());
            m_rangesMaxAndMin.rangeTrapezoidXMax = std::max(m_rangesMaxAndMin.rangeTrapezoidXMax, iter->m_PointsUpAndRight[i].x());
            m_rangesMaxAndMin.rangeTrapezoidZMin = std::min(m_rangesMaxAndMin.rangeTrapezoidZMin, iter->m_PointsUpAndRight[i].y());
            m_rangesMaxAndMin.rangeTrapezoidZMax = std::max(m_rangesMaxAndMin.rangeTrapezoidZMax, iter->m_PointsUpAndRight[i].y());
        }
        for (int i = 0; i < iter->m_PointsDownAndLeft.size(); ++i)
        {
            m_rangesMaxAndMin.rangeTrapezoidXMin = std::min(m_rangesMaxAndMin.rangeTrapezoidXMin, iter->m_PointsDownAndLeft[i].x());
            m_rangesMaxAndMin.rangeTrapezoidXMax = std::max(m_rangesMaxAndMin.rangeTrapezoidXMax, iter->m_PointsDownAndLeft[i].x());
            m_rangesMaxAndMin.rangeTrapezoidZMin = std::min(m_rangesMaxAndMin.rangeTrapezoidZMin, iter->m_PointsDownAndLeft[i].y());
            m_rangesMaxAndMin.rangeTrapezoidZMax = std::max(m_rangesMaxAndMin.rangeTrapezoidZMax, iter->m_PointsDownAndLeft[i].y());
        }
        for (int i = 0; i < iter->m_PointsLaserBottom.size(); ++i)
        {
        /*    m_rangesMaxAndMin.rangeTrapezoidXMin = std::min(m_rangesMaxAndMin.rangeTrapezoidXMin, iter->m_PointsLaserBottom[i].x());
            m_rangesMaxAndMin.rangeTrapezoidXMax = std::max(m_rangesMaxAndMin.rangeTrapezoidXMax, iter->m_PointsLaserBottom[i].x());
       */     m_rangesMaxAndMin.rangeTrapezoidZMin = std::min(m_rangesMaxAndMin.rangeTrapezoidZMin, iter->m_PointsLaserBottom[i].y());
            m_rangesMaxAndMin.rangeTrapezoidZMax = std::max(m_rangesMaxAndMin.rangeTrapezoidZMax, iter->m_PointsLaserBottom[i].y());
        }
        for (int i = 0; i < iter->m_PointsLaserOrigin.size(); ++i)
        {
          /*  m_rangesMaxAndMin.rangeTrapezoidXMin = std::min(m_rangesMaxAndMin.rangeTrapezoidXMin, iter->m_PointsLaserOrigin[i].x());
            m_rangesMaxAndMin.rangeTrapezoidXMax = std::max(m_rangesMaxAndMin.rangeTrapezoidXMax, iter->m_PointsLaserOrigin[i].x());
         */   m_rangesMaxAndMin.rangeTrapezoidZMin = std::min(m_rangesMaxAndMin.rangeTrapezoidZMin, iter->m_PointsLaserOrigin[i].y());
            m_rangesMaxAndMin.rangeTrapezoidZMax = std::max(m_rangesMaxAndMin.rangeTrapezoidZMax, iter->m_PointsLaserOrigin[i].y());
        }
    }
}

int CCalScheCamDataForUI::ApplyRangeNumber(int iNumber)
{
    int time = 0;
    while (1)
    {
        if (iNumber / 10 == 0)
            break;
        time++;
        iNumber /= 10;
    }
    if (iNumber == 0)
        return iNumber;
    int iret = iNumber>0?(iNumber + 1):(iNumber-1);
    while (time > 0)
    {
        iret *= 10;
        time--;
    }
    return iret;
}


void scheimCamera::ShowLinesAndAreas(int index)
{
    m_calScheCamDataForUI.CalLinesPoints(index);
    m_calScheCamDataForUI.CalAreasPoints(index);
    std::list<PointsSet>::iterator iterPointsSet = m_calScheCamDataForUI.m_listPointsSet.begin();
    std::list<QLineSeries*>::iterator iterLineseriesForMeasureRange = m_listpLineseriesForMeasureRange.begin();
    std::list<QLineSeries*>::iterator iterLineseriesForWidthResolution = m_listpLineseriesForWidthResolution.begin();
    std::list<QLineSeries*>::iterator iterLineseriesForHeightResolution = m_listpLineseriesForHeightResolution.begin();
    std::list<QLineSeries*>::iterator iterLineseriesForHeightWidthResolution = m_listpLineseriesForHeightWidthResolution.begin();
    std::list<QLineSeries*>::iterator iterLineseriesUpAndRight = m_listpLineseriesUpAndRight.begin();
    std::list<QLineSeries*>::iterator iterLineseriesDownAndLeft = m_listpLineseriesDownAndLeft.begin();
    std::list<QLineSeries*>::iterator iterLineseriesLaserOrigin = m_listpLineseriesLaserOrigin.begin();
    std::list<QLineSeries*>::iterator iterLineseriesLaserBottom = m_listpLineseriesLaserBottom.begin();
    std::list<QAreaSeries*>::iterator iterLineseriesAreaSeries = m_listpAreaSeries.begin();
    std::list<QAreaSeries*>::iterator iterLineseriesAreaSeriesLaser = m_listpAreaSeriesLaser.begin();
    while (index > 0)
    {
        iterPointsSet++;
        iterLineseriesForMeasureRange++;
        iterLineseriesForWidthResolution++;
        iterLineseriesForHeightResolution++;
        iterLineseriesForHeightWidthResolution++;
        iterLineseriesUpAndRight++;
        iterLineseriesDownAndLeft++;
        iterLineseriesLaserOrigin++;
        iterLineseriesLaserBottom++;
        iterLineseriesAreaSeries++;
        iterLineseriesAreaSeriesLaser++;
        index--;
    }
    //坐标范围确定
    m_calScheCamDataForUI.UpdatePointsRange();
    RangesMaxAndMin& range = m_calScheCamDataForUI.m_rangesMaxAndMin;
    //
    (*iterLineseriesForMeasureRange)->clear();
    (*iterLineseriesForMeasureRange)->replace(iterPointsSet->m_PointsForMeasureRange);
    flushAxisAndLines(m_listpLineseriesForMeasureRange, m_pAxisZForMeasureRange, m_pAxisXForMeasureRange, m_chartXZRange,
        range.rangeZMin, range.rangeZMax, range.rangeXMin, range.rangeXMax);
    //
    (*iterLineseriesForWidthResolution)->clear();
    (*iterLineseriesForWidthResolution)->replace(iterPointsSet->m_PointsForWidthResolution);
    flushAxisAndLines(m_listpLineseriesForWidthResolution, m_pAxisZForWidthResolution, m_pAxisWidthResolution, m_chartXresolutionZ,
        range.rangeZMin, range.rangeZMax, range.rangeXMinResolution, range.rangeXMaxResolution);
    //
    (*iterLineseriesForHeightResolution)->clear();
    (*iterLineseriesForHeightResolution)->replace(iterPointsSet->m_PointsForHeightResolution);
    flushAxisAndLines(m_listpLineseriesForHeightResolution, m_pAxisZForHeightResolution, m_pAxisHeightResolution, m_chartZresolutionZ,
        range.rangeZMin, range.rangeZMax, range.rangeZMinResolution, range.rangeZMaxResolution);
    
   (*iterLineseriesForHeightWidthResolution)->clear();
    (*iterLineseriesForHeightWidthResolution)->replace(iterPointsSet->m_PointsForHeightWidthResolution);
    flushAxisAndLines(m_listpLineseriesForHeightWidthResolution, m_pAxisHeightForHeightWidthResolution, m_pAxisWidthForHeightWidthResolution,
        m_chartXresolutionZresolution, range.rangeZMinResolution, range.rangeZMaxResolution,
        range.rangeXMinResolution, range.rangeXMaxResolution);


    //
    (*iterLineseriesUpAndRight)->clear();
    (*iterLineseriesDownAndLeft)->clear();
    (*iterLineseriesLaserOrigin)->clear();
    (*iterLineseriesLaserBottom)->clear();
    (*iterLineseriesUpAndRight)->replace(iterPointsSet->m_PointsUpAndRight);
    (*iterLineseriesDownAndLeft)->replace(iterPointsSet->m_PointsDownAndLeft);
    (*iterLineseriesLaserOrigin)->replace(iterPointsSet->m_PointsLaserOrigin);
    (*iterLineseriesLaserBottom)->replace(iterPointsSet->m_PointsLaserBottom);
    
    flushAxisAndAreas(m_listpAreaSeries, m_listpAreaSeriesLaser, m_pAxisXRange, m_pAxisZRange, m_chartTrapezoidLine,
        range.rangeTrapezoidXMin, range.rangeTrapezoidXMax, range.rangeTrapezoidZMin, range.rangeTrapezoidZMax);
}

