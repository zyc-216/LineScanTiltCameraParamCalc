#include "ScheimpflugCamera.h"
#include <QtWidgets/QApplication>
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(".//128.ico"));
    scheimCamera w;
    w.setWindowTitle(QString::fromLocal8Bit("�߽ṹ��ɳķ�������Ԥ��  ���� by zyc"));
    w.show();
    return a.exec();
}
