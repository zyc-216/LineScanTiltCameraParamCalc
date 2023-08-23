#include "ScheimpflugCamera.h"
#include <QtWidgets/QApplication>
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(".//128.ico"));
    scheimCamera w;
    w.setWindowTitle(QString::fromLocal8Bit("线结构光沙姆相机参数预估  —— by zyc"));
    w.show();
    return a.exec();
}
