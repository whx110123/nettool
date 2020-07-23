#include "dialogpma.h"
#include "ui_dialogpma.h"

#include <quiwidget.h>

DialogPMA::DialogPMA(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogPMA)
{
	ui->setupUi(this);
	piec104 = NULL;
	piec104Show = NULL;
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
	if(piec104Show)
	{
		delete piec104Show;
		piec104Show = NULL;
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
			showToText(config.data);
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
			showToText(recvData.left(piec104->apci.length+2));
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
			showToText(config.data);
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
	if(!piec104Show)
	{
		piec104Show = new IEC104;
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

void DialogPMA::showToText(QByteArray ba)
{
	while(!ba.isEmpty())
	{
		if(!piec104Show->init(ba))
		{
			stopdebug();
			QMessageBox::warning(this,"告警窗","收到未识别的报文,停止模拟\r\n"+piec104Show->mRecvData.toHex(' '));
			return;
		}
		else
		{
			if(ui->pushButton_reflash->text().contains("暂停刷新"))
			{
				ui->textEdit_data->append("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
				ui->textEdit_data->append(piec104Show->showToText());
			}
			ba.remove(0,piec104Show->apci.length+2);
		}
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

QByteArray DialogPMA::getYKYTData(uchar type)
{
	uchar asdutype = ui->comboBox_104remotetype->currentText().split(" ").at(0).toUShort();
	QByteArray tmp;
	ushort tmp_us = 0;
	short tmp_s = 0;
	float tmp_f = 0;
	QDateTime datetime = QDateTime::currentDateTime();
	switch (asdutype)
	{
	case 45:
	case 58:
		if(ui->comboBox_104YKvalue->currentText().contains("合"))
		{
			tmp += 0x01|type;
		}
		else
		{
			tmp += type;
		}
		if(asdutype==58)
		{
			tmp += dateTimeToBa(datetime,7,BINARYTIME2A);
		}
		break;
	case 46:
	case 47:
	case 59:
		if(ui->comboBox_104YKvalue->currentText().contains("合"))
		{
			tmp += 0x02|type;
		}
		else
		{
			tmp += 0x01|type;
		}
		if(asdutype==59)
		{
			tmp += dateTimeToBa(datetime,7,BINARYTIME2A);
		}
		break;
	case 48:
	case 49:
		tmp_s = ui->lineEdit_104YTvalue->text().toShort();
		tmp_us = (ushort)tmp_s;
		tmp += tmp_us & 0xff;
		tmp += (tmp_us>>8)&0xff;
		tmp += type;
		break;
	case 50:
		tmp_f = ui->lineEdit_104YTvalue->text().toFloat();
		tmp += floatToBa(tmp_f);
		tmp += type;
		break;
	default:
		break;

	}
	return tmp;
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

void DialogPMA::on_pushButton_104callTitle_clicked()
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

void DialogPMA::on_pushButton_104callDescription_clicked()
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

void DialogPMA::on_pushButton_104callDimension_clicked()
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

void DialogPMA::on_pushButton_104callSetting_clicked()
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


void DialogPMA::on_pushButton_104setFloatDowm_clicked()
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
	config.iec103config->asdutype = 0x0a;
	config.iec103config->vsq = 0x81;
	config.iec103config->cot = 0x28;
	config.iec103config->fun = 0xfe;
	config.iec103config->inf = 0xf9;
	config.iec103config->rii = 0;
	config.iec103config->ngd = 1;
	config.iec103config->gin[0][0] = ui->lineEdit_104setGroup->text().toUShort();
	config.iec103config->gin[0][1] = ui->lineEdit_104setInf->text().toUShort();
	config.iec103config->kod[0] = 1;
	config.iec103config->gdd[0][0] = 7;
	config.iec103config->gdd[0][1] = 4;
	config.iec103config->gdd[0][2] = 1;
	float tmp = ui->lineEdit_104setValueFloat->text().toFloat();
	memcpy(config.iec103config->gid,&tmp,4);
	createAndSendData(config);
}

void DialogPMA::on_pushButton_104settingCuring_clicked()
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
	config.iec103config->asdutype = 0x0a;
	config.iec103config->vsq = 0x81;
	config.iec103config->cot = 0x28;
	config.iec103config->fun = 0xfe;
	config.iec103config->inf = 0xfa;
	config.iec103config->rii = 0;
	config.iec103config->ngd = 0;
	createAndSendData(config);
}

void DialogPMA::on_pushButton_104setUintDowm_clicked()
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
	config.iec103config->asdutype = 0x0a;
	config.iec103config->vsq = 0x81;
	config.iec103config->cot = 0x28;
	config.iec103config->fun = 0xfe;
	config.iec103config->inf = 0xf9;
	config.iec103config->rii = 0;
	config.iec103config->ngd = 1;
	config.iec103config->gin[0][0] = ui->lineEdit_104setGroup->text().toUShort();
	config.iec103config->gin[0][1] = ui->lineEdit_104setInf->text().toUShort();
	config.iec103config->kod[0] = 1;
	config.iec103config->gdd[0][0] = 3;
	config.iec103config->gdd[0][1] = 4;
	config.iec103config->gdd[0][2] = 1;
	uint tmp = ui->lineEdit_104setValueUint->text().toUInt();
	memcpy(config.iec103config->gid,&tmp,4);
	createAndSendData(config);
}



void DialogPMA::on_pushButton_clear_clicked()
{
	ui->textEdit_data->clear();
}

void DialogPMA::on_pushButton_104select_clicked()
{
	config.state = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = ui->comboBox_104remotetype->currentText().split(" ").at(0).toUShort();
	config.controltype = ITYPE;
	config.vsq = 1;
	config.cot = 6;
	if(ui->checkBox_104isHex->isChecked())
	{
		config.infaddr = ui->lineEdit_104infaddr->text().toUInt(0,16);
	}
	else
	{
		config.infaddr = ui->lineEdit_104infaddr->text().toUInt();
	}
	config.infdata = getYKYTData(0x80);
	createAndSendData(config);
}

void DialogPMA::on_pushButton_104execute_clicked()
{
	config.state = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = ui->comboBox_104remotetype->currentText().split(" ").at(0).toUShort();
	config.controltype = ITYPE;
	config.vsq = 1;
	config.cot = 6;
	if(ui->checkBox_104isHex->isChecked())
	{
		config.infaddr = ui->lineEdit_104infaddr->text().toUInt(0,16);
	}
	else
	{
		config.infaddr = ui->lineEdit_104infaddr->text().toUInt();
	}
	config.infdata = getYKYTData('\0');
	createAndSendData(config);
}

void DialogPMA::on_pushButton_104cancel_clicked()
{
	config.state = STATE_HOTKEY;
	config.isMaster = true;
	config.asdutype = ui->comboBox_104remotetype->currentText().split(" ").at(0).toUShort();
	config.controltype = ITYPE;
	config.vsq = 1;
	config.cot = 8;
	if(ui->checkBox_104isHex->isChecked())
	{
		config.infaddr = ui->lineEdit_104infaddr->text().toUInt(0,16);
	}
	else
	{
		config.infaddr = ui->lineEdit_104infaddr->text().toUInt();
	}
	config.infdata = getYKYTData('\0');
	createAndSendData(config);
}

void DialogPMA::on_checkBox_104isHex_stateChanged(int arg1)
{
	uint ss = ui->lineEdit_104infaddr->text().toUInt(0,arg1?10:16);
	ui->lineEdit_104infaddr->setText(QString::number(ss,arg1?16:10));
}

void DialogPMA::on_pushButton_reflash_clicked()
{
	if(ui->pushButton_reflash->text().contains("暂停刷新"))
	{
		ui->pushButton_reflash->setText("正常刷新");
	}
	else
	{
		ui->pushButton_reflash->setText("暂停刷新");
	}
}
