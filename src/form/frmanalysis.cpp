#include "frmanalysis.h"
#include "ui_frmanalysis.h"
#include "quiwidget.h"
#include <QString>
#include <iec101.h>
#include <iec103com.h>
#include <iec103netwiscom.h>
#include "myhighlighter.h"
#include "iec104.h"


frmAnalysis::frmAnalysis(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmAnalysis)
{
	ui->setupUi(this);
	highlighter1 = new myhighlighter(ui->resulttext->document());
	highlighter2 = new myhighlighter(ui->originaltext->document());
	initForm();
	initConfig();
}

frmAnalysis::~frmAnalysis()
{
	delete highlighter1;
	delete highlighter2;
	delete ui;
}

void frmAnalysis::initForm()
{
	ui->protocolcbox->addItems(App::Protocollst);
	QStringList list = QStringList();
	list << "1" <<"2";
	ui->comboBox_cotlen->addItems(list);
	ui->comboBox_comaddrlen->addItems(list);
	list <<"3";
	ui->comboBox_infaddrlen->addItems(list);
}

void frmAnalysis::initConfig()
{
	ui->protocolcbox->setCurrentIndex(ui->protocolcbox->findText(App::DefaultProtocol));
	ui->comboBox_cotlen->setCurrentText("2");
	ui->comboBox_comaddrlen->setCurrentText("2");
	ui->comboBox_infaddrlen->setCurrentText("3");
	highlighter1->hlformat.setForeground(Qt::magenta);
	highlighter1->hlformat.setFontWeight(QFont::Bold);
	highlighter2->hlformat.setForeground(Qt::magenta);
	highlighter2->hlformat.setFontWeight(QFont::Bold);
	//    connect(ui->protocolcbox, SIGNAL(currentIndexChanged(int)), this, SLOT(saveConfig()));
}

void frmAnalysis::on_clearBtn_clicked()
{
	ui->originaltext->clear();
	ui->resulttext->clear();
}

void frmAnalysis::on_protocolcbox_currentIndexChanged(const QString &arg1)
{
	if(arg1 == IEC_104)
	{
		ui->comboBox_cotlen->setCurrentText("2");
		ui->comboBox_comaddrlen->setCurrentText("2");
		ui->comboBox_infaddrlen->setCurrentText("3");
	}
	else if(arg1 == IEC_101)
	{
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("2");
	}
	else if(arg1 == IEC_103WISCOMNET)
	{
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("2");
	}
	else if(arg1 == IEC_103COM)
	{
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("2");
	}
}

void frmAnalysis::on_highlightEdit_textChanged(const QString &arg1)
{
	highlighter1->hlstr = arg1;
	highlighter2->hlstr = arg1;
	ui->resulttext->setText(ui->resulttext->toPlainText());
	ui->originaltext->setText(ui->originaltext->toPlainText());
}


void frmAnalysis::on_fontcolor_clicked()
{
	QColor color = QColorDialog::getColor(Qt::magenta,this,tr("颜色对话框"));
	if(color.isValid())
	{
		highlighter1->hlformat.setForeground(color);
		//      highlighter1->hlformat.setFontWeight(QFont::Bold);
		highlighter2->hlformat.setForeground(color);
		//      highlighter2->hlformat.setFontWeight(QFont::Bold);
		ui->resulttext->setText(ui->resulttext->toPlainText());
		ui->originaltext->setText(ui->originaltext->toPlainText());
	}
}

void frmAnalysis::on_backgroundcolor_clicked()
{
	QColor color = QColorDialog::getColor(Qt::white,this,tr("颜色对话框"));
	if(color.isValid())
	{
		highlighter1->hlformat.setBackground(color);
		highlighter2->hlformat.setBackground(color);
		ui->resulttext->setText(ui->resulttext->toPlainText());
		ui->originaltext->setText(ui->originaltext->toPlainText());
	}
}


void frmAnalysis::on_fontchange_clicked()
{
	bool ok;
	QFont font = QFontDialog::getFont(&ok,this);
	if(ok)
	{
		highlighter1->hlformat.setFont(font);
		highlighter2->hlformat.setFont(font);
		ui->resulttext->setText(ui->resulttext->toPlainText());
		ui->originaltext->setText(ui->originaltext->toPlainText());
	}
}

void frmAnalysis::on_AnalysisBtn_clicked()
{
	ui->resulttext->clear();
	App::readConfig();
	QString data = ui->originaltext->toPlainText();
	if (data.length() <= 0) {
		return;
	}
	QByteArray buffer;
	buffer = QUIHelper::hexStrToByteArray(data);
	int err;
	QString text;
	/************************************************************/
	int i = 1;
	while (!buffer.isEmpty())
	{
		text.append(QString("####第%1帧####\r\n").arg(i++));
		if(ui->protocolcbox->currentText() == IEC_104)           //分析104报文
		{
			m_104 = new protocol101::protocol104apdu;
			m_104->cotlen =ui->comboBox_cotlen->currentText().toInt();
			m_104->comaddrlen = ui->comboBox_comaddrlen->currentText().toInt();
			m_104->dataaddrlen = ui->comboBox_infaddrlen->currentText().toInt();
			err =m_104->CharT0APDU(buffer.data(),buffer.length());
			buffer.remove(0,m_104->m_apdu->length);
			if(err)
			{
				text.append(m_104->dealERR(err));
				break;
			}
			else
			{
				text.append(m_104->dealAPDU());
			}
			delete m_104;

		}
		else if(ui->protocolcbox->currentText() == IEC_101)      //分析101报文
		{
			m_101 = new protocol101::protocol101apdu;
			m_101->cotlen =ui->comboBox_cotlen->currentText().toInt();
			m_101->comaddrlen = ui->comboBox_comaddrlen->currentText().toInt();
			m_101->dataaddrlen = ui->comboBox_infaddrlen->currentText().toInt();
			err =m_101->CharT0APDU(buffer.data(),buffer.length());
			buffer.remove(0,m_101->m_apdu->length);
			if(err)
			{
				text.append(m_101->dealERR(err));
				break;
			}
			else
			{
				text.append(m_101->dealAPDU());
			}
			delete m_101;
		}
		else if(ui->protocolcbox->currentText() == IEC_103WISCOMNET)//分析金智网络103报文
		{
			m_103wiscomnet = new protocol103::protocol103wiscomnet;
			err =m_103wiscomnet->CharT0APDU(buffer.data(),buffer.length());
			buffer.remove(0,m_103wiscomnet->m_apdu->length);
			if(err)
			{
				text.append(m_103wiscomnet->dealERR(err));
				break;
			}
			else
			{
				text.append(m_103wiscomnet->dealAPDU());
			}
			delete m_103wiscomnet;
		}
		else if(ui->protocolcbox->currentText() == IEC_103COM)
		{
			m_103com = new protocol103::protocol103com;
			err =m_103com->CharT0APDU(buffer.data(),buffer.length());
			buffer.remove(0,m_103com->m_apdu->length);
			if(err)
			{
				text.append(m_103com->dealERR(err));
				break;
			}
			else
			{
				text.append(m_103com->dealAPDU());
			}
			delete m_103com;
		}
	}
	ui->resulttext->setText(text);
	return;
}

void frmAnalysis::on_PBtest_clicked()
{
	ui->resulttext->clear();
	App::readConfig();
	QString data = ui->originaltext->toPlainText();
	if (data.length() <= 0) {
		return;
	}
	QByteArray buffer;
	buffer = QUIHelper::hexStrToByteArray(data);


	int i = 1;
	MyBase *myprotocol = NULL;
	if(ui->protocolcbox->currentText() == IEC_104)           //分析104报文
	{
		IEC104 *tmp = new IEC104;
		tmp->asdu.cotlen =ui->comboBox_cotlen->currentText().toInt();
		tmp->asdu.comaddrlen = ui->comboBox_comaddrlen->currentText().toInt();
		tmp->asdu.infaddrlen = ui->comboBox_infaddrlen->currentText().toInt();
		myprotocol = tmp;
	}
	else if(ui->protocolcbox->currentText() == IEC_101)      //分析101报文
	{
		IEC101 *tmp = new IEC101;
		tmp->asdu.cotlen =ui->comboBox_cotlen->currentText().toInt();
		tmp->asdu.comaddrlen = ui->comboBox_comaddrlen->currentText().toInt();
		tmp->asdu.infaddrlen = ui->comboBox_infaddrlen->currentText().toInt();
		myprotocol = tmp;
	}
	else if(ui->protocolcbox->currentText() == IEC_103WISCOMNET)//分析金智网络103报文
	{
		myprotocol = new IEC103NetWiscom;

	}
	else if(ui->protocolcbox->currentText() == IEC_103COM)
	{
		myprotocol = new IEC103COM;
	}

	if (myprotocol)
	{
		while (!buffer.isEmpty())
		{
			ui->resulttext->append(QString("####第%1帧####").arg(i++));
			if(myprotocol->init(buffer))
			{
				ui->resulttext->append(myprotocol->showToText());
				buffer.remove(0, myprotocol->len);
			}
			else
			{
				ui->resulttext->append(myprotocol->error);
				break;
			}
		}
		delete myprotocol;
		myprotocol = NULL;
	}
}
