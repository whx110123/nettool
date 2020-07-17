#include "frmfunctions.h"
#include "ui_frmfunctions.h"


frmFunctions::frmFunctions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmFunctions)
{
    ui->setupUi(this);
    m_dialogsenddata = new DialogSendData(this);
    m_dialogdealdata = new DialogDealData(this);
	m_dialogintroduction = new DialogIntroduction(this);
	m_dialogdebug = new DialogDebug(this);
	m_dialogpma = new DialogPMA(this);
    initfrom();
}

frmFunctions::~frmFunctions()
{
    delete ui;
}

void frmFunctions::on_pbfunc1_clicked()
{

    m_dialogsenddata->show();
}

void frmFunctions::initfrom()
{
//    QString str;
//    str.append("1.提供多组报文输入并发送\r\n");
//    str.append("2.发报文可设置不同延时，可以收到一帧报文后再发送下一帧报文\r\n");
//    str.append("3.对TCP、UDP、串口等通道均可使用\r\n");
//    ui->lab_intro1->setText(str);
}

void frmFunctions::on_pbfunc2_clicked()
{
    m_dialogdealdata->show();
}

void frmFunctions::on_pbintro_clicked()
{
	m_dialogintroduction->exec();
}


void frmFunctions::on_pbfunc3_clicked()
{
	m_dialogdebug->show();
}

void frmFunctions::on_pbfunc4_clicked()
{
	m_dialogpma->show();
}
