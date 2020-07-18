#include "dialogpma.h"
#include "ui_dialogpma.h"

#include <quiwidget.h>

DialogPMA::DialogPMA(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogPMA)
{
	ui->setupUi(this);
	piec104 = NULL;
	init();
}

DialogPMA::~DialogPMA()
{
	delete ui;
	if(piec104)
	{
		delete piec104;
		piec104 = NULL;
	}
}

void DialogPMA::dealData(const QString &data, const QString &title)
{
	if(ui->comboBox_connect->currentText().contains(title))
	{
		if(ui->pushButton_start->text() == QString("停止"))
		{
			recvData.append(QUIHelper::hexStrToByteArray(data));
		}
	}
}

bool DialogPMA::createAndSendData(IECDataConfig &config)
{
	if(ui->pushButton_start->text() == QString("停止") && piec104)
	{
		if(piec104->createData(config))
		{
			emitsignals(config.data.toHex(' '));
			return true;
		}
	}
	return false;
}

void DialogPMA::init()
{
	handleDataTimer = new QTimer(this);
	haveData = false;
	connect(handleDataTimer, SIGNAL(timeout()), this, SLOT(handleData()));
}

void DialogPMA::handleData()
{
	if(!piec104)
	{
		return;
	}
	while(!recvData.isEmpty())
	{
		if(!piec104->init(recvData))
		{
			stopdebug();
			QMessageBox::warning(this,"告警窗","收到未识别的报文,停止模拟\r\n"+piec104->mRecvData.toHex(' '));
			return;
		}
		else
		{
			haveData = true;
			recvData.remove(0,piec104->apci.length+2);
		}
	}
	if(haveData || piec104->mstate == STATE_INIT)
	{
		haveData = false;
		config.state = piec104->mstate;
//		qDebug() << "state = " << piec104->mstate;
		config.isMaster = true;
		if(piec104->createData(config))
		{
			QString str = config.data.toHex(' ');
			emitsignals(str);
		}
	}
}

void DialogPMA::startdebug()
{
	recvData.clear();
	ui->pushButton_start->setText("停止");
	if(!piec104)
	{
		piec104 = new IEC104;
	}
	piec104->mstate = STATE_INIT;
	App::IEC_COMADDR = ui->lineEdit_104asduaddr->text().toUInt();
	handleDataTimer->start(1000);
}

void DialogPMA::stopdebug()
{
	recvData.clear();
	ui->pushButton_start->setText("开始");
	if(handleDataTimer->isActive())
	{
		handleDataTimer->stop();
	}
	if(piec104)
	{
		piec104->mstate = STATE_INIT;
		piec104->apci.control.localRecvNo = 0;
		piec104->apci.control.localSendNo = 0;
	}
}

void DialogPMA::emitsignals(const QString &data)
{
	if(ui->comboBox_connect->currentText().contains("TCP客户端"))
	{
		emit dlgTotcpclient(data);
	}
	else if(ui->comboBox_connect->currentText().contains("TCP服务器"))
	{
		emit dlgTotcpserver(data);
	}
	else if(ui->comboBox_connect->currentText().contains("UDP客户端"))
	{
		emit dlgToudpclient(data);
	}
	else if(ui->comboBox_connect->currentText().contains("UDP服务器"))
	{
		emit dlgToudpserver(data);
	}
	else if(ui->comboBox_connect->currentText().contains("COM串口"))
	{
		emit dlgTocom(data);
	}
}

void DialogPMA::on_pushButton_start_clicked()
{
	if(ui->pushButton_start->text() == QString("开始"))
	{
		startdebug();
	}
	else
	{
		stopdebug();
	}
}

void DialogPMA::on_pushButton_sendasdu_clicked()
{
	config.userdata = QUIHelper::hexStrToByteArray(ui->textEdit_104asdu->toPlainText());
	config.state = STATE_USER;
	config.isMaster = true;
	config.asdutype = 0;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_104calltitle_clicked()
{
	config.state = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = 167;
	config.controltype = ITYPE;
	config.vsq = 0;
	config.cot = 5;
	if(!config.iec103config)
	{
		config.iec103config = new IECDataConfig;
	}
	config.iec103config->isMaster = config.isMaster;
	config.iec103config->devaddr = ui->lineEdit_104devaddr->text().toUShort();
	config.iec103config->asdutype = 0x15;
	config.iec103config->vsq = 0x81;
	config.iec103config->cot = 0x2a;
	config.iec103config->fun = 0xfe;
	config.iec103config->inf = 0xf0;
	config.iec103config->rii = 0;
	config.iec103config->nog = 0;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_104callRange_clicked()
{
	config.state = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = 167;
	config.controltype = ITYPE;
	config.vsq = 0;
	config.cot = 5;
	if(!config.iec103config)
	{
		config.iec103config = new IECDataConfig;
	}
	config.iec103config->isMaster = config.isMaster;
	config.iec103config->devaddr = ui->lineEdit_104devaddr->text().toUShort();
	config.iec103config->asdutype = 0x15;
	config.iec103config->vsq = 0x81;
	config.iec103config->cot = 0x2a;
	config.iec103config->fun = 0xfe;
	config.iec103config->inf = 0xf1;
	config.iec103config->rii = 0;
	config.iec103config->nog = 1;
	config.iec103config->gin[0][0] = ui->lineEdit_104setGroup->text().toUShort();
	config.iec103config->gin[0][1] = 0;
	config.iec103config->kod[0] = 3;
	createAndSendData(config);

}

void DialogPMA::on_pushButton_104calldescription_clicked()
{
	config.state = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = 167;
	config.controltype = ITYPE;
	config.vsq = 0;
	config.cot = 5;
	if(!config.iec103config)
	{
		config.iec103config = new IECDataConfig;
	}
	config.iec103config->isMaster = config.isMaster;
	config.iec103config->devaddr = ui->lineEdit_104devaddr->text().toUShort();
	config.iec103config->asdutype = 0x15;
	config.iec103config->vsq = 0x81;
	config.iec103config->cot = 0x2a;
	config.iec103config->fun = 0xfe;
	config.iec103config->inf = 0xf1;
	config.iec103config->rii = 0;
	config.iec103config->nog = 1;
	config.iec103config->gin[0][0] = ui->lineEdit_104setGroup->text().toUShort();
	config.iec103config->gin[0][1] = 0;
	config.iec103config->kod[0] = 0x0a;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_104callAccuracy_clicked()
{
	config.state = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = 167;
	config.controltype = ITYPE;
	config.vsq = 0;
	config.cot = 5;
	if(!config.iec103config)
	{
		config.iec103config = new IECDataConfig;
	}
	config.iec103config->isMaster = config.isMaster;
	config.iec103config->devaddr = ui->lineEdit_104devaddr->text().toUShort();
	config.iec103config->asdutype = 0x15;
	config.iec103config->vsq = 0x81;
	config.iec103config->cot = 0x2a;
	config.iec103config->fun = 0xfe;
	config.iec103config->inf = 0xf1;
	config.iec103config->rii = 0;
	config.iec103config->nog = 1;
	config.iec103config->gin[0][0] = ui->lineEdit_104setGroup->text().toUShort();
	config.iec103config->gin[0][1] = 0;
	config.iec103config->kod[0] = 5;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_104calldimension_clicked()
{
	config.state = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = 167;
	config.controltype = ITYPE;
	config.vsq = 0;
	config.cot = 5;
	if(!config.iec103config)
	{
		config.iec103config = new IECDataConfig;
	}
	config.iec103config->isMaster = config.isMaster;
	config.iec103config->devaddr = ui->lineEdit_104devaddr->text().toUShort();
	config.iec103config->asdutype = 0x15;
	config.iec103config->vsq = 0x81;
	config.iec103config->cot = 0x2a;
	config.iec103config->fun = 0xfe;
	config.iec103config->inf = 0xf1;
	config.iec103config->rii = 0;
	config.iec103config->nog = 1;
	config.iec103config->gin[0][0] = ui->lineEdit_104setGroup->text().toUShort();
	config.iec103config->gin[0][1] = 0;
	config.iec103config->kod[0] = 9;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_104callsetting_clicked()
{
	config.state = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = 167;
	config.controltype = ITYPE;
	config.vsq = 0;
	config.cot = 5;
	if(!config.iec103config)
	{
		config.iec103config = new IECDataConfig;
	}
	config.iec103config->isMaster = config.isMaster;
	config.iec103config->devaddr = ui->lineEdit_104devaddr->text().toUShort();
	config.iec103config->asdutype = 0x15;
	config.iec103config->vsq = 0x81;
	config.iec103config->cot = 0x2a;
	config.iec103config->fun = 0xfe;
	config.iec103config->inf = 0xf1;
	config.iec103config->rii = 0;
	config.iec103config->nog = 1;
	config.iec103config->gin[0][0] = ui->lineEdit_104setGroup->text().toUShort();
	config.iec103config->gin[0][1] = 0;
	config.iec103config->kod[0] = 1;
	createAndSendData(config);
}
