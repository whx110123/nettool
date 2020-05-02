#include "dialogdealdata.h"
#include "ui_dialogdealdata.h"
#include "quiwidget.h"
#include "globaldefine.h"

DialogDealData::DialogDealData(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogDealData)
{
	ui->setupUi(this);
	initfrom();
}

DialogDealData::~DialogDealData()
{
	delete ui;
}

void DialogDealData::initfrom()
{
	ui->cbcrc->addItems(App::CRClst);
	ui->cbtransform->addItems(App::Transfermode);
}

ushort DialogDealData::crc16(uchar *buf, ushort length)
{
	ushort i;
	ushort j;
	ushort c;
	ushort crc = 0xFFFF;   //设置crc寄存器为0xffff
	for (i=0; i<length; i++)
	{
		c = *(buf+i) & 0x00FF;
		crc^=c;
		for (j=0; j<8; j++)
		{
			if (crc & 0x0001)
			{
				crc >>= 1;
				crc ^= 0xA001;
			}
			else
			{
				crc >>= 1;
			}
		}
	}
	return(crc);
}

void DialogDealData::on_pbcrc_clicked()
{

	QString data = ui->textsource->toPlainText().trimmed();
	QByteArray ba = QUIHelper::hexStrToByteArray(data);
	uchar crcarray[2] = {0};
	int crclen = 0;
	if(ui->cbcrc->currentText().contains("CRC 16 低位在前"))
	{
		crclen = 2;
		ushort crc = crc16((uchar *)ba.data(),ba.length());
		crcarray[0] = crc & 0xff;
		crcarray[1] = (crc>>8) & 0xff;
	}
	else if(ui->cbcrc->currentText().contains("CRC 16 高位在前"))
	{
		crclen = 2;
		ushort crc = crc16((uchar *)ba.data(),ba.length());
		crcarray[1] = crc & 0xff;
		crcarray[0] = (crc>>8) & 0xff;
	}
	else if(ui->cbcrc->currentText().contains("总加和"))
	{
		crclen = 1;
		for (int i = 0;i <ba.length();i++)
		{
			crcarray[0] += *(uchar *)(ba.data() +i);
		}
	}
	else if(ui->cbcrc->currentText().contains("加总异或"))
	{
		crclen = 1;
		for (int i = 0;i <ba.length();i++)
		{
			crcarray[0] ^= *(uchar *)(ba.data() +i);
		}
	}


	for (int i = 0;i <crclen;i++)
	{
		data.append(" " + CharToHexStr(crcarray[i]));
	}
	ui->textdestination->setText(data.toUpper());

}

void DialogDealData::on_pbtransform_clicked()
{
	QString data = ui->linesource->text().trimmed();
	QString dataout;
	float datafloat = 0;
	uint datauint = 0;
	uchar uchararray[4] = {0};
	if(ui->cbtransform->currentText().contains("浮点数转四字节"))
	{
		datafloat = data.toFloat();
		datauint = *(uint *)(&datafloat);
		if(ui->checkreverse->isChecked())
		{
			for (int i = 0;i<4;i++)
			{
				uchararray[i] = (datauint >> 8*i) & 0xff;
			}
		}
		else
		{
			for (int i = 0;i<4;i++)
			{
				uchararray[i] = (datauint >> 8*(3-i)) & 0xff;
			}
		}
		for (int i = 0;i <4;i++)
		{
			dataout.append(" " + CharToHexStr(uchararray[i]));
		}
	}
	else if(ui->cbtransform->currentText().contains("四字节转浮点数"))
	{
		QByteArray ba = QUIHelper::hexStrToByteArray(data);
		if(ba.length() == 4)
		{
			int model = 1;
			if(ui->checkreverse->isChecked())
			{
				model = 0;
			}
			datafloat = charTofloat((uchar *)ba.data(),model);
			dataout = QString::number(datafloat);
		}
	}
	else if(ui->cbtransform->currentText().contains("整数转四字节"))
	{

	}
	else if(ui->cbtransform->currentText().contains("带符号四字节转整数"))
	{

	}
	else if(ui->cbtransform->currentText().contains("无符号四字节转整数"))
	{

	}
	ui->linedestination->setText(dataout.trimmed());

}
