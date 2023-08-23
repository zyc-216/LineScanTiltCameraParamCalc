/********************************************************************************
** Form generated from reading UI file 'ScheimpflugCamera.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHEIMPFLUGCAMERA_H
#define UI_SCHEIMPFLUGCAMERA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_scheimCameraClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout_3;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_9;
    QWidget *page_2;
    QGridLayout *gridLayout_5;
    QWidget *page_3;
    QGridLayout *gridLayout_6;
    QWidget *page_4;
    QGridLayout *gridLayout_7;
    QWidget *page_5;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_10;
    QPushButton *pushButtonRefresh;
    QPushButton *pushButton;
    QPushButton *pushButtonXZ;
    QPushButton *pushButtonXresolutionZ;
    QPushButton *pushButtonXZ_2;
    QPushButton *pushButtonXZ_3;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QComboBox *comboBox_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLineEdit *LineEditPixelSize;
    QLabel *label;
    QLineEdit *height;
    QLabel *LabelPixelSize;
    QLabel *LabelInput;
    QLabel *LabelBaseDistance;
    QLabel *labelCamHorizontalOffset;
    QLineEdit *LineEditCameraAngle;
    QLabel *labelCamVerticalLength;
    QLineEdit *lineEditCamVerticalLength;
    QLabel *LabelFocalLength;
    QLabel *resolution;
    QLineEdit *width;
    QLineEdit *LineEditFocalLength;
    QLabel *LabelCameraAngle;
    QLineEdit *lineEditCamHorizontalOffset;
    QLineEdit *LineEditBaseDistance;
    QLabel *labelLaserFan;
    QLineEdit *lineEditLaserFan;
    QLabel *label_3;
    QLabel *label_2;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonLoad;
    QLabel *labelImg;
    QTableWidget *tableWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *scheimCameraClass)
    {
        if (scheimCameraClass->objectName().isEmpty())
            scheimCameraClass->setObjectName(QString::fromUtf8("scheimCameraClass"));
        scheimCameraClass->resize(1375, 997);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scheimCameraClass->sizePolicy().hasHeightForWidth());
        scheimCameraClass->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(scheimCameraClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setAutoFillBackground(false);
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetMinimumSize);
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        stackedWidget->setMinimumSize(QSize(800, 450));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        sizePolicy.setHeightForWidth(page->sizePolicy().hasHeightForWidth());
        page->setSizePolicy(sizePolicy);
        page->setMinimumSize(QSize(200, 0));
        gridLayout_9 = new QGridLayout(page);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_9->setSizeConstraint(QLayout::SetMinimumSize);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        sizePolicy.setHeightForWidth(page_2->sizePolicy().hasHeightForWidth());
        page_2->setSizePolicy(sizePolicy);
        gridLayout_5 = new QGridLayout(page_2);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setSizeConstraint(QLayout::SetMinimumSize);
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        sizePolicy.setHeightForWidth(page_3->sizePolicy().hasHeightForWidth());
        page_3->setSizePolicy(sizePolicy);
        gridLayout_6 = new QGridLayout(page_3);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setSizeConstraint(QLayout::SetMinimumSize);
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        sizePolicy.setHeightForWidth(page_4->sizePolicy().hasHeightForWidth());
        page_4->setSizePolicy(sizePolicy);
        gridLayout_7 = new QGridLayout(page_4);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setSizeConstraint(QLayout::SetMinimumSize);
        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        sizePolicy.setHeightForWidth(page_5->sizePolicy().hasHeightForWidth());
        page_5->setSizePolicy(sizePolicy);
        gridLayout_8 = new QGridLayout(page_5);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setSizeConstraint(QLayout::SetMinimumSize);
        stackedWidget->addWidget(page_5);

        gridLayout_3->addWidget(stackedWidget, 1, 0, 1, 1);

        gridLayout_10 = new QGridLayout();
        gridLayout_10->setSpacing(6);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_10->setSizeConstraint(QLayout::SetNoConstraint);
        pushButtonRefresh = new QPushButton(centralWidget);
        pushButtonRefresh->setObjectName(QString::fromUtf8("pushButtonRefresh"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonRefresh->sizePolicy().hasHeightForWidth());
        pushButtonRefresh->setSizePolicy(sizePolicy1);
        pushButtonRefresh->setStyleSheet(QString::fromUtf8("QPushButton{background-color: rgb(225, 225, 225);border:1px groove gray;border-radius:4px;padding:1px 4px;border-style: outset;}\n"
"                                       QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}\n"
"                                       QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}"));

        gridLayout_10->addWidget(pushButtonRefresh, 0, 6, 1, 1);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy2);
        pushButton->setMaximumSize(QSize(300, 16777215));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton{background-color: rgb(225, 225, 225);border:1px groove gray;border-radius:4px;padding:1px 4px;border-style: outset;}\n"
"                                       QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}\n"
"                                       QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}"));

        gridLayout_10->addWidget(pushButton, 0, 1, 1, 1);

        pushButtonXZ = new QPushButton(centralWidget);
        pushButtonXZ->setObjectName(QString::fromUtf8("pushButtonXZ"));
        sizePolicy1.setHeightForWidth(pushButtonXZ->sizePolicy().hasHeightForWidth());
        pushButtonXZ->setSizePolicy(sizePolicy1);
        pushButtonXZ->setMaximumSize(QSize(300, 16777215));
        pushButtonXZ->setLayoutDirection(Qt::LeftToRight);
        pushButtonXZ->setStyleSheet(QString::fromUtf8("QPushButton{background-color: rgb(225, 225, 225);border:1px groove gray;border-radius:4px;padding:1px 4px;border-style: outset;}\n"
"                                       QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}\n"
"                                       QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}"));

        gridLayout_10->addWidget(pushButtonXZ, 0, 2, 1, 1);

        pushButtonXresolutionZ = new QPushButton(centralWidget);
        pushButtonXresolutionZ->setObjectName(QString::fromUtf8("pushButtonXresolutionZ"));
        sizePolicy1.setHeightForWidth(pushButtonXresolutionZ->sizePolicy().hasHeightForWidth());
        pushButtonXresolutionZ->setSizePolicy(sizePolicy1);
        pushButtonXresolutionZ->setMaximumSize(QSize(300, 16777215));
        pushButtonXresolutionZ->setStyleSheet(QString::fromUtf8("QPushButton{background-color: rgb(225, 225, 225);border:1px groove gray;border-radius:4px;padding:1px 4px;border-style: outset;}\n"
"                                       QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}\n"
"                                       QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}"));

        gridLayout_10->addWidget(pushButtonXresolutionZ, 0, 3, 1, 1);

        pushButtonXZ_2 = new QPushButton(centralWidget);
        pushButtonXZ_2->setObjectName(QString::fromUtf8("pushButtonXZ_2"));
        sizePolicy1.setHeightForWidth(pushButtonXZ_2->sizePolicy().hasHeightForWidth());
        pushButtonXZ_2->setSizePolicy(sizePolicy1);
        pushButtonXZ_2->setMaximumSize(QSize(300, 16777215));
        pushButtonXZ_2->setStyleSheet(QString::fromUtf8("QPushButton{background-color: rgb(225, 225, 225);border:1px groove gray;border-radius:4px;padding:1px 4px;border-style: outset;}\n"
"                                       QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}\n"
"                                       QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}"));

        gridLayout_10->addWidget(pushButtonXZ_2, 0, 4, 1, 1);

        pushButtonXZ_3 = new QPushButton(centralWidget);
        pushButtonXZ_3->setObjectName(QString::fromUtf8("pushButtonXZ_3"));
        sizePolicy1.setHeightForWidth(pushButtonXZ_3->sizePolicy().hasHeightForWidth());
        pushButtonXZ_3->setSizePolicy(sizePolicy1);
        pushButtonXZ_3->setMaximumSize(QSize(300, 16777215));
        pushButtonXZ_3->setStyleSheet(QString::fromUtf8("QPushButton{background-color: rgb(225, 225, 225);border:1px groove gray;border-radius:4px;padding:1px 4px;border-style: outset;}\n"
"                                       QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}\n"
"                                       QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}"));

        gridLayout_10->addWidget(pushButtonXZ_3, 0, 5, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        sizePolicy2.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(lineEdit);

        comboBox_2 = new QComboBox(centralWidget);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        sizePolicy2.setHeightForWidth(comboBox_2->sizePolicy().hasHeightForWidth());
        comboBox_2->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(comboBox_2);


        gridLayout_10->addLayout(horizontalLayout, 1, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_10, 2, 0, 1, 1);


        horizontalLayout_2->addLayout(gridLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
        LineEditPixelSize = new QLineEdit(centralWidget);
        LineEditPixelSize->setObjectName(QString::fromUtf8("LineEditPixelSize"));
        sizePolicy2.setHeightForWidth(LineEditPixelSize->sizePolicy().hasHeightForWidth());
        LineEditPixelSize->setSizePolicy(sizePolicy2);
        LineEditPixelSize->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(LineEditPixelSize, 2, 1, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(label, 1, 2, 1, 1);

        height = new QLineEdit(centralWidget);
        height->setObjectName(QString::fromUtf8("height"));
        sizePolicy2.setHeightForWidth(height->sizePolicy().hasHeightForWidth());
        height->setSizePolicy(sizePolicy2);
        height->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(height, 1, 3, 1, 1);

        LabelPixelSize = new QLabel(centralWidget);
        LabelPixelSize->setObjectName(QString::fromUtf8("LabelPixelSize"));
        sizePolicy2.setHeightForWidth(LabelPixelSize->sizePolicy().hasHeightForWidth());
        LabelPixelSize->setSizePolicy(sizePolicy2);
        LabelPixelSize->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(LabelPixelSize, 2, 0, 1, 1);

        LabelInput = new QLabel(centralWidget);
        LabelInput->setObjectName(QString::fromUtf8("LabelInput"));
        sizePolicy2.setHeightForWidth(LabelInput->sizePolicy().hasHeightForWidth());
        LabelInput->setSizePolicy(sizePolicy2);
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(13);
        font.setBold(true);
        LabelInput->setFont(font);

        gridLayout->addWidget(LabelInput, 0, 0, 1, 1);

        LabelBaseDistance = new QLabel(centralWidget);
        LabelBaseDistance->setObjectName(QString::fromUtf8("LabelBaseDistance"));
        sizePolicy2.setHeightForWidth(LabelBaseDistance->sizePolicy().hasHeightForWidth());
        LabelBaseDistance->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(LabelBaseDistance, 4, 0, 1, 1);

        labelCamHorizontalOffset = new QLabel(centralWidget);
        labelCamHorizontalOffset->setObjectName(QString::fromUtf8("labelCamHorizontalOffset"));
        sizePolicy2.setHeightForWidth(labelCamHorizontalOffset->sizePolicy().hasHeightForWidth());
        labelCamHorizontalOffset->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(labelCamHorizontalOffset, 7, 0, 1, 1);

        LineEditCameraAngle = new QLineEdit(centralWidget);
        LineEditCameraAngle->setObjectName(QString::fromUtf8("LineEditCameraAngle"));
        sizePolicy2.setHeightForWidth(LineEditCameraAngle->sizePolicy().hasHeightForWidth());
        LineEditCameraAngle->setSizePolicy(sizePolicy2);
        LineEditCameraAngle->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(LineEditCameraAngle, 5, 1, 1, 1);

        labelCamVerticalLength = new QLabel(centralWidget);
        labelCamVerticalLength->setObjectName(QString::fromUtf8("labelCamVerticalLength"));
        sizePolicy2.setHeightForWidth(labelCamVerticalLength->sizePolicy().hasHeightForWidth());
        labelCamVerticalLength->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(labelCamVerticalLength, 6, 0, 1, 1);

        lineEditCamVerticalLength = new QLineEdit(centralWidget);
        lineEditCamVerticalLength->setObjectName(QString::fromUtf8("lineEditCamVerticalLength"));
        sizePolicy2.setHeightForWidth(lineEditCamVerticalLength->sizePolicy().hasHeightForWidth());
        lineEditCamVerticalLength->setSizePolicy(sizePolicy2);
        lineEditCamVerticalLength->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(lineEditCamVerticalLength, 6, 1, 1, 1);

        LabelFocalLength = new QLabel(centralWidget);
        LabelFocalLength->setObjectName(QString::fromUtf8("LabelFocalLength"));
        sizePolicy2.setHeightForWidth(LabelFocalLength->sizePolicy().hasHeightForWidth());
        LabelFocalLength->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(LabelFocalLength, 3, 0, 1, 1);

        resolution = new QLabel(centralWidget);
        resolution->setObjectName(QString::fromUtf8("resolution"));
        sizePolicy2.setHeightForWidth(resolution->sizePolicy().hasHeightForWidth());
        resolution->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(resolution, 1, 0, 1, 1);

        width = new QLineEdit(centralWidget);
        width->setObjectName(QString::fromUtf8("width"));
        sizePolicy2.setHeightForWidth(width->sizePolicy().hasHeightForWidth());
        width->setSizePolicy(sizePolicy2);
        width->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(width, 1, 1, 1, 1);

        LineEditFocalLength = new QLineEdit(centralWidget);
        LineEditFocalLength->setObjectName(QString::fromUtf8("LineEditFocalLength"));
        sizePolicy2.setHeightForWidth(LineEditFocalLength->sizePolicy().hasHeightForWidth());
        LineEditFocalLength->setSizePolicy(sizePolicy2);
        LineEditFocalLength->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(LineEditFocalLength, 3, 1, 1, 1);

        LabelCameraAngle = new QLabel(centralWidget);
        LabelCameraAngle->setObjectName(QString::fromUtf8("LabelCameraAngle"));
        sizePolicy2.setHeightForWidth(LabelCameraAngle->sizePolicy().hasHeightForWidth());
        LabelCameraAngle->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(LabelCameraAngle, 5, 0, 1, 1);

        lineEditCamHorizontalOffset = new QLineEdit(centralWidget);
        lineEditCamHorizontalOffset->setObjectName(QString::fromUtf8("lineEditCamHorizontalOffset"));
        sizePolicy2.setHeightForWidth(lineEditCamHorizontalOffset->sizePolicy().hasHeightForWidth());
        lineEditCamHorizontalOffset->setSizePolicy(sizePolicy2);
        lineEditCamHorizontalOffset->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(lineEditCamHorizontalOffset, 7, 1, 1, 1);

        LineEditBaseDistance = new QLineEdit(centralWidget);
        LineEditBaseDistance->setObjectName(QString::fromUtf8("LineEditBaseDistance"));
        sizePolicy2.setHeightForWidth(LineEditBaseDistance->sizePolicy().hasHeightForWidth());
        LineEditBaseDistance->setSizePolicy(sizePolicy2);
        LineEditBaseDistance->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(LineEditBaseDistance, 4, 1, 1, 1);

        labelLaserFan = new QLabel(centralWidget);
        labelLaserFan->setObjectName(QString::fromUtf8("labelLaserFan"));
        sizePolicy2.setHeightForWidth(labelLaserFan->sizePolicy().hasHeightForWidth());
        labelLaserFan->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(labelLaserFan, 8, 0, 1, 1);

        lineEditLaserFan = new QLineEdit(centralWidget);
        lineEditLaserFan->setObjectName(QString::fromUtf8("lineEditLaserFan"));
        sizePolicy2.setHeightForWidth(lineEditLaserFan->sizePolicy().hasHeightForWidth());
        lineEditLaserFan->setSizePolicy(sizePolicy2);
        lineEditLaserFan->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(lineEditLaserFan, 8, 1, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 7, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy3);
        label_2->setMinimumSize(QSize(0, 0));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(false);
        label_2->setFont(font1);

        verticalLayout->addWidget(label_2);

        pushButtonAdd = new QPushButton(centralWidget);
        pushButtonAdd->setObjectName(QString::fromUtf8("pushButtonAdd"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pushButtonAdd->sizePolicy().hasHeightForWidth());
        pushButtonAdd->setSizePolicy(sizePolicy4);
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(true);
        font2.setUnderline(false);
        font2.setStrikeOut(false);
        font2.setKerning(true);
        pushButtonAdd->setFont(font2);
        pushButtonAdd->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(pushButtonAdd);

        pushButtonSave = new QPushButton(centralWidget);
        pushButtonSave->setObjectName(QString::fromUtf8("pushButtonSave"));
        sizePolicy4.setHeightForWidth(pushButtonSave->sizePolicy().hasHeightForWidth());
        pushButtonSave->setSizePolicy(sizePolicy4);
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(true);
        pushButtonSave->setFont(font3);
        pushButtonSave->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(pushButtonSave);

        pushButtonLoad = new QPushButton(centralWidget);
        pushButtonLoad->setObjectName(QString::fromUtf8("pushButtonLoad"));
        pushButtonLoad->setFont(font3);
        pushButtonLoad->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(pushButtonLoad);

        labelImg = new QLabel(centralWidget);
        labelImg->setObjectName(QString::fromUtf8("labelImg"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(labelImg->sizePolicy().hasHeightForWidth());
        labelImg->setSizePolicy(sizePolicy5);
        labelImg->setStyleSheet(QString::fromUtf8("\\1.jpg"));

        verticalLayout->addWidget(labelImg);


        horizontalLayout_2->addLayout(verticalLayout);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 23)
            tableWidget->setColumnCount(23);
        QFont font4;
        font4.setItalic(false);
        font4.setKerning(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font4);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QBrush brush(QColor(0, 0, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        QFont font5;
        font5.setBold(true);
        font5.setItalic(false);
        font5.setUnderline(false);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFont(font5);
        __qtablewidgetitem9->setBackground(QColor(138, 138, 138, 120));
        __qtablewidgetitem9->setForeground(brush);
        tableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QFont font6;
        font6.setBold(true);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setFont(font6);
        __qtablewidgetitem10->setForeground(brush);
        tableWidget->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setFont(font6);
        __qtablewidgetitem11->setForeground(brush);
        tableWidget->setHorizontalHeaderItem(11, __qtablewidgetitem11);
        QFont font7;
        font7.setBold(true);
        font7.setItalic(false);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        __qtablewidgetitem12->setFont(font7);
        __qtablewidgetitem12->setForeground(brush);
        tableWidget->setHorizontalHeaderItem(12, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        __qtablewidgetitem13->setFont(font6);
        __qtablewidgetitem13->setForeground(brush);
        tableWidget->setHorizontalHeaderItem(13, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        __qtablewidgetitem14->setFont(font6);
        __qtablewidgetitem14->setForeground(brush);
        tableWidget->setHorizontalHeaderItem(14, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        __qtablewidgetitem15->setFont(font7);
        __qtablewidgetitem15->setForeground(brush);
        tableWidget->setHorizontalHeaderItem(15, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        __qtablewidgetitem16->setFont(font6);
        __qtablewidgetitem16->setForeground(brush);
        tableWidget->setHorizontalHeaderItem(16, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        __qtablewidgetitem17->setFont(font6);
        __qtablewidgetitem17->setForeground(brush);
        tableWidget->setHorizontalHeaderItem(17, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(18, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(19, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(20, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(21, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(22, __qtablewidgetitem22);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout_2->addWidget(tableWidget, 1, 0, 1, 1);

        scheimCameraClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(scheimCameraClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1375, 22));
        scheimCameraClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(scheimCameraClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        scheimCameraClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(scheimCameraClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        scheimCameraClass->setStatusBar(statusBar);
        QWidget::setTabOrder(width, height);
        QWidget::setTabOrder(height, LineEditPixelSize);
        QWidget::setTabOrder(LineEditPixelSize, LineEditFocalLength);
        QWidget::setTabOrder(LineEditFocalLength, LineEditBaseDistance);
        QWidget::setTabOrder(LineEditBaseDistance, LineEditCameraAngle);
        QWidget::setTabOrder(LineEditCameraAngle, lineEditCamVerticalLength);
        QWidget::setTabOrder(lineEditCamVerticalLength, lineEditCamHorizontalOffset);
        QWidget::setTabOrder(lineEditCamHorizontalOffset, lineEditLaserFan);

        retranslateUi(scheimCameraClass);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(scheimCameraClass);
    } // setupUi

    void retranslateUi(QMainWindow *scheimCameraClass)
    {
        scheimCameraClass->setWindowTitle(QCoreApplication::translate("scheimCameraClass", "scheimCamera", nullptr));
        pushButtonRefresh->setText(QCoreApplication::translate("scheimCameraClass", "\345\210\267\346\226\260", nullptr));
        pushButton->setText(QCoreApplication::translate("scheimCameraClass", "\346\242\257\345\275\242\345\233\276", nullptr));
        pushButtonXZ->setText(QCoreApplication::translate("scheimCameraClass", "X-Z", nullptr));
        pushButtonXresolutionZ->setText(QCoreApplication::translate("scheimCameraClass", "Xresolution-Z", nullptr));
        pushButtonXZ_2->setText(QCoreApplication::translate("scheimCameraClass", "Zresolution-Z", nullptr));
        pushButtonXZ_3->setText(QCoreApplication::translate("scheimCameraClass", "Xresolution-Zresolution", nullptr));
        lineEdit->setText(QCoreApplication::translate("scheimCameraClass", "\351\200\211\346\213\251\346\265\213\351\207\217\347\272\277\357\274\232", nullptr));
        label->setText(QCoreApplication::translate("scheimCameraClass", "\303\227", nullptr));
        LabelPixelSize->setText(QCoreApplication::translate("scheimCameraClass", "\345\203\217\345\205\203\345\260\272\345\257\270(\316\274m)\357\274\232", nullptr));
        LabelInput->setText(QCoreApplication::translate("scheimCameraClass", "Input\357\274\232", nullptr));
        LabelBaseDistance->setText(QCoreApplication::translate("scheimCameraClass", "\345\237\272\350\267\235(mm)\357\274\232", nullptr));
        labelCamHorizontalOffset->setText(QCoreApplication::translate("scheimCameraClass", "\347\233\270\346\234\272\346\260\264\345\271\263\345\201\217\347\247\273(mm)\357\274\232", nullptr));
        labelCamVerticalLength->setText(QCoreApplication::translate("scheimCameraClass", "\347\233\270\346\234\272\345\256\211\350\243\205\351\253\230\345\272\246(mm)\357\274\232", nullptr));
        LabelFocalLength->setText(QCoreApplication::translate("scheimCameraClass", "\347\204\246\350\267\235f(mm)\357\274\232", nullptr));
        resolution->setText(QCoreApplication::translate("scheimCameraClass", "\345\210\206\350\276\250\347\216\207(Width\303\227Height))\357\274\232", nullptr));
        LabelCameraAngle->setText(QCoreApplication::translate("scheimCameraClass", "\347\233\270\346\234\272\345\200\276\350\247\222(\302\260)\357\274\232", nullptr));
        labelLaserFan->setText(QCoreApplication::translate("scheimCameraClass", "\346\277\200\345\205\211\346\211\207\350\247\222(\302\260)\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("scheimCameraClass", "(\345\267\246\350\264\237\345\217\263\346\255\243)", nullptr));
        label_2->setText(QString());
        pushButtonAdd->setText(QCoreApplication::translate("scheimCameraClass", "\346\267\273\345\212\240\346\226\271\346\241\210", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("scheimCameraClass", "\344\277\235\345\255\230\346\211\200\346\234\211\346\226\271\346\241\210", nullptr));
        pushButtonLoad->setText(QCoreApplication::translate("scheimCameraClass", "\345\257\274\345\205\245\346\226\271\346\241\210", nullptr));
        labelImg->setText(QCoreApplication::translate("scheimCameraClass", "TextLabel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("scheimCameraClass", "Width", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("scheimCameraClass", "Height", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("scheimCameraClass", "\345\203\217\345\205\203\345\260\272\345\257\270(\316\274m)", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("scheimCameraClass", "\347\204\246\350\267\235(mm)", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("scheimCameraClass", "\345\237\272\350\267\235(mm)", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("scheimCameraClass", "\347\233\270\346\234\272\345\200\276\350\247\222(\302\260)", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("scheimCameraClass", "\345\256\211\350\243\205\351\253\230\345\272\246(mm)", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("scheimCameraClass", "\346\260\264\345\271\263\345\201\217\347\247\273(mm)", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("scheimCameraClass", "\346\277\200\345\205\211\346\211\207\350\247\222(\302\260)", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("scheimCameraClass", "\346\262\231\345\247\206\350\247\222(\302\260)", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("scheimCameraClass", "\350\277\221\347\253\257\346\260\264\345\271\263\350\214\203\345\233\264(mm)", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->horizontalHeaderItem(11);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("scheimCameraClass", "\350\277\234\347\253\257\346\260\264\345\271\263\350\214\203\345\233\264(mm)", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->horizontalHeaderItem(12);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("scheimCameraClass", "\350\277\221\347\253\257\345\236\202\347\233\264\351\253\230\345\272\246(mm)", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->horizontalHeaderItem(13);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("scheimCameraClass", "\350\277\234\347\253\257\345\236\202\347\233\264\351\253\230\345\272\246(mm)", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->horizontalHeaderItem(14);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("scheimCameraClass", "\350\277\221\347\253\257\346\260\264\345\271\263\345\210\206\350\276\250\347\216\207(mm/px)", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->horizontalHeaderItem(15);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("scheimCameraClass", "\350\277\234\347\253\257\346\260\264\345\271\263\345\210\206\350\276\250\347\216\207(mm/px)", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->horizontalHeaderItem(16);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("scheimCameraClass", "\350\277\221\347\253\257\345\236\202\347\233\264\345\210\206\350\276\250\347\216\207(mm/px)", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->horizontalHeaderItem(17);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("scheimCameraClass", "\350\277\234\347\253\257\345\236\202\347\233\264\345\210\206\350\276\250\347\216\207(mm/px)", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->horizontalHeaderItem(18);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("scheimCameraClass", "\347\233\270\346\234\272\350\214\203\345\233\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->horizontalHeaderItem(19);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("scheimCameraClass", "\346\277\200\345\205\211\350\214\203\345\233\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->horizontalHeaderItem(20);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("scheimCameraClass", "\351\242\234\350\211\262", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->horizontalHeaderItem(21);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("scheimCameraClass", "\346\226\271\346\241\210", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->horizontalHeaderItem(22);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("scheimCameraClass", "id", nullptr));
    } // retranslateUi

};

namespace Ui {
    class scheimCameraClass: public Ui_scheimCameraClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHEIMPFLUGCAMERA_H
