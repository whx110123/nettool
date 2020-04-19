﻿#include "frmmain.h"
#include "quiwidget.h"
#include "globaldefine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/main.ico"));

    QFont font;
    font.setFamily(QUIConfig::FontName);
    font.setPixelSize(QUIConfig::FontSize);
    a.setFont(font);

    //设置编码以及加载中文翻译文件
    QUIHelper::setCode();
    QUIHelper::setTranslator(":/qt_zh_CN.qm");
    QUIHelper::setTranslator(":/widgets.qm");
    QUIHelper::initRand();

    App::Intervals << "1" << "10" << "20" << "50" << "100" << "200" << "300" << "500" << "1000" << "1500" << "2000" << "3000" << "5000" << "10000";
    App::Protocollst << IEC104 << IEC101 << IEC103WISCOMNET << IEC103COM;
    App::Transferlst << "TCP客户端" << "TCP服务器" << "UDP客户端" << "UDP服务器" << "COM串口";
    App::ConfigFile = QString("%1/%2.ini").arg(QUIHelper::appPath()).arg(QUIHelper::appName());
    App::readConfig();
    App::readSendData();
    App::readDeviceData();

    frmMain w;
    w.setWindowTitle(QString("网络串口调试助手V1.02   ") + QString("本机IP: %1 ").arg(QUIHelper::getLocalIP()) + QString("          作者：hxwang"));
    w.show();

    return a.exec();
}
