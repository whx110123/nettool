#include "frmmain.h"
#include "ui_frmmain.h"
#include "quiwidget.h"

frmMain::frmMain(QWidget *parent) : QWidget(parent), ui(new Ui::frmMain)
{
	ui->setupUi(this);
	ui->tabWidget->setCurrentIndex(App::CurrentIndex);
	initform();

}

frmMain::~frmMain()
{
	delete ui;
}

void frmMain::on_tabWidget_currentChanged(int index)
{
	App::CurrentIndex = index;
	App::writeConfig();
	changeImage();

}


void frmMain::initform()
{
	connect(ui->tabFunctions->m_dialogsenddata, SIGNAL(dlgTotcpclient(const QString&)), ui->tabTcpClient, SLOT(dealData(const QString&)));
	connect(ui->tabFunctions->m_dialogsenddata, SIGNAL(dlgTotcpserver(const QString&)), ui->tabTcpServer, SLOT(dealData(const QString&)));
	connect(ui->tabFunctions->m_dialogsenddata, SIGNAL(dlgToudpclient(const QString&)), ui->tabUdpClient, SLOT(dealData(const QString&)));
	connect(ui->tabFunctions->m_dialogsenddata, SIGNAL(dlgToudpserver(const QString&)), ui->tabUdpServer, SLOT(dealData(const QString&)));
	connect(ui->tabFunctions->m_dialogsenddata, SIGNAL(dlgTocom(const QString&)), ui->tabCom, SLOT(dealData(const QString&)));
	connect(ui->tabTcpClient, SIGNAL(dlgTodialogsenddata(const QString&, const QString&)),
			ui->tabFunctions->m_dialogsenddata, SLOT(dealData(const QString&, const QString&)));
	connect(ui->tabTcpServer, SIGNAL(dlgTodialogsenddata(const QString&, const QString&)),
			ui->tabFunctions->m_dialogsenddata, SLOT(dealData(const QString&, const QString&)));
	connect(ui->tabUdpClient, SIGNAL(dlgTodialogsenddata(const QString&, const QString&)),
			ui->tabFunctions->m_dialogsenddata, SLOT(dealData(const QString&, const QString&)));
	connect(ui->tabUdpServer, SIGNAL(dlgTodialogsenddata(const QString&, const QString&)),
			ui->tabFunctions->m_dialogsenddata, SLOT(dealData(const QString&, const QString&)));
	connect(ui->tabCom, SIGNAL(dlgTodialogsenddata(const QString&, const QString&)),
			ui->tabFunctions->m_dialogsenddata, SLOT(dealData(const QString&, const QString&)));

	connect(ui->tabFunctions->m_dialogpma, SIGNAL(dlgTotcpclient(const QString&)), ui->tabTcpClient, SLOT(dealData(const QString&)));
	connect(ui->tabFunctions->m_dialogpma, SIGNAL(dlgTotcpserver(const QString&)), ui->tabTcpServer, SLOT(dealData(const QString&)));
	connect(ui->tabFunctions->m_dialogpma, SIGNAL(dlgToudpclient(const QString&)), ui->tabUdpClient, SLOT(dealData(const QString&)));
	connect(ui->tabFunctions->m_dialogpma, SIGNAL(dlgToudpserver(const QString&)), ui->tabUdpServer, SLOT(dealData(const QString&)));
	connect(ui->tabFunctions->m_dialogpma, SIGNAL(dlgTocom(const QString&)), ui->tabCom, SLOT(dealData(const QString&)));
	connect(ui->tabTcpClient, SIGNAL(dlgTodialogsenddata(const QString&, const QString&)),
			ui->tabFunctions->m_dialogpma, SLOT(dealData(const QString&, const QString&)));
	connect(ui->tabTcpServer, SIGNAL(dlgTodialogsenddata(const QString&, const QString&)),
			ui->tabFunctions->m_dialogpma, SLOT(dealData(const QString&, const QString&)));
	connect(ui->tabUdpClient, SIGNAL(dlgTodialogsenddata(const QString&, const QString&)),
			ui->tabFunctions->m_dialogpma, SLOT(dealData(const QString&, const QString&)));
	connect(ui->tabUdpServer, SIGNAL(dlgTodialogsenddata(const QString&, const QString&)),
			ui->tabFunctions->m_dialogpma, SLOT(dealData(const QString&, const QString&)));
	connect(ui->tabCom, SIGNAL(dlgTodialogsenddata(const QString&, const QString&)),
			ui->tabFunctions->m_dialogpma, SLOT(dealData(const QString&, const QString&)));
}

void frmMain::changeImage()
{
	this->setAutoFillBackground(true);
	QPalette palette = this->palette();
	QImage image(":/res/kejibj2.JPG");
	QImage backGround = image.scaled(this->width(), this->height(), Qt::IgnoreAspectRatio);
	palette.setBrush(QPalette::Background, QBrush(backGround));
	this->setPalette(palette);
}
