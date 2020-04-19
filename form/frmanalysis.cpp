#include "frmanalysis.h"
#include "ui_frmanalysis.h"
#include "quiwidget.h"
#include <QString>
#include "myhighlighter.h"


frmAnalysis::frmAnalysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmAnalysis)
{
    ui->setupUi(this);
    highlighter = new myhighlighter(ui->resulttext->document());
    initForm();
    initConfig();
}

frmAnalysis::~frmAnalysis()
{
    delete highlighter;
    delete ui;
}

void frmAnalysis::initForm()
{
    ui->protocolcbox->addItems(App::Protocollst);
    QStringList list = QStringList();
    list << "1" <<"2";
    ui->comboBox_1->addItems(list);
    ui->comboBox_2->addItems(list);
    ui->comboBox_4->addItems(list);
    ui->comboBox_5->addItems(list);
    list <<"3";
    ui->comboBox_3->addItems(list);
    ui->comboBox_6->addItems(list);
}

void frmAnalysis::initConfig()
{
    ui->protocolcbox->setCurrentIndex(ui->protocolcbox->findText(App::DefaultProtocol));
    ui->comboBox_1->setCurrentText("2");
    ui->comboBox_2->setCurrentText("2");
    ui->comboBox_3->setCurrentText("3");
    ui->comboBox_4->setCurrentText("1");
    ui->comboBox_5->setCurrentText("1");
    ui->comboBox_6->setCurrentText("2");
    //    connect(ui->protocolcbox, SIGNAL(currentIndexChanged(int)), this, SLOT(saveConfig()));
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
    int length;
    int err;
    QString text;
    /************************************************************/
    int i = 1;
    while (!buffer.isEmpty())
    {
        text.append(QString("####第%1帧####\r\n").arg(i++));
        if(ui->protocolcbox->currentText() == IEC104)           //分析104报文
        {
            m_104 = new protocol101::protocol104apdu;
            m_104->cotlen =ui->comboBox_1->currentText().toInt();
            m_104->comaddrlen = ui->comboBox_2->currentText().toInt();
            m_104->dataaddrlen = ui->comboBox_3->currentText().toInt();
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
        else if(ui->protocolcbox->currentText() == IEC101)      //分析101报文
        {
            m_101 = new protocol101::protocol101apdu;
            m_101->cotlen =ui->comboBox_4->currentText().toInt();
            m_101->comaddrlen = ui->comboBox_5->currentText().toInt();
            m_101->dataaddrlen = ui->comboBox_6->currentText().toInt();
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
        else if(ui->protocolcbox->currentText() == IEC103WISCOMNET)//分析金智网络103报文
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
        else if(ui->protocolcbox->currentText() == IEC103COM)
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

void frmAnalysis::on_clearBtn_clicked()
{
    ui->originaltext->clear();
    ui->resulttext->clear();
}

void frmAnalysis::on_protocolcbox_currentIndexChanged(const QString &arg1)
{
    if(arg1 == IEC104)
    {
        ui->configWidgets->setCurrentWidget(ui->page_1);
    }
    else if(arg1 == IEC101)
    {
        ui->configWidgets->setCurrentWidget(ui->page_2);
    }
    else if(arg1 == IEC103WISCOMNET)
    {
        ui->configWidgets->setCurrentWidget(ui->page_3);
    }
    else if(arg1 == IEC103COM)
    {
        ui->configWidgets->setCurrentWidget(ui->page_4);
    }
}
