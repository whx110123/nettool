#include "dialogsenddata.h"
#include "ui_dialogsenddata.h"
#include "quiwidget.h"

DialogSendData::DialogSendData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSendData)
{
    ui->setupUi(this);
    initfrom();
}

DialogSendData::~DialogSendData()
{
    delete ui;
}

void DialogSendData::initfrom()
{
    timercycle = new QTimer(this);
    recflag = 0;
    connect(timercycle, SIGNAL(timeout()), this, SLOT(sendDatacycle()));
    ui->comboBox->addItems(App::Transferlst);
}

void DialogSendData::initdataList()
{
    lstindex = 0;
    dataList.clear();

    QString data;
    data = ui->linedata1->text();
    if(ui->checkBox1->isChecked()&&!data.trimmed().isEmpty())
    {
        dataList.append(data);
    }
    data = ui->linedata2->text();
    if(ui->checkBox2->isChecked()&&!data.trimmed().isEmpty())
    {
        dataList.append(data);
    }
    data = ui->linedata3->text();
    if(ui->checkBox3->isChecked()&&!data.trimmed().isEmpty())
    {
        dataList.append(data);
    }
    data = ui->linedata4->text();
    if(ui->checkBox4->isChecked()&&!data.trimmed().isEmpty())
    {
        dataList.append(data);
    }
    data = ui->linedata5->text();
    if(ui->checkBox5->isChecked()&&!data.trimmed().isEmpty())
    {
        dataList.append(data);
    }
    data = ui->linedata6->text();
    if(ui->checkBox6->isChecked()&&!data.trimmed().isEmpty())
    {
        dataList.append(data);
    }
    data = ui->linedata7->text();
    if(ui->checkBox7->isChecked()&&!data.trimmed().isEmpty())
    {
        dataList.append(data);
    }
    data = ui->linedata8->text();
    if(ui->checkBox8->isChecked()&&!data.trimmed().isEmpty())
    {
        dataList.append(data);
    }
    data = ui->linedata9->text();
    if(ui->checkBox9->isChecked()&&!data.trimmed().isEmpty())
    {
        dataList.append(data);
    }
    data = ui->linedata10->text();
    if(ui->checkBox10->isChecked()&&!data.trimmed().isEmpty())
    {
        dataList.append(data);
    }
    data = ui->linedata11->text();
    if(ui->checkBox11->isChecked()&&!data.trimmed().isEmpty())
    {
        dataList.append(data);
    }
    data = ui->linedata12->text();
    if(ui->checkBox12->isChecked()&&!data.trimmed().isEmpty())
    {
        dataList.append(data);
    }
    data = ui->linedata13->text();
    if(ui->checkBox13->isChecked()&&!data.trimmed().isEmpty())
    {
        dataList.append(data);
    }
    data = ui->linedata14->text();
    if(ui->checkBox14->isChecked()&&!data.trimmed().isEmpty())
    {
        dataList.append(data);
    }
}

void DialogSendData::closeEvent(QCloseEvent *event)
{
    stopTimer();
    event->accept();
}

void DialogSendData::dealData(const QString &data, const QString &title)
{
    if(ui->comboBox->currentText().contains(title))
    {
//        ui->comboBox->setCurrentIndex(ui->comboBox->findText(title));
        recflag = 1;
    }

}

void DialogSendData::sendDatacycle()
{
    switch (cycleflag)
    {
    case CYCLEONCEREC:                          //有接受才发，全部发完后停止
        if(recflag == 0)
        {
            break;
        }
    case CYCLEONCE:                             //全部发完后停止
        if(lstindex < dataList.size())
        {
            emitsignals(dataList.at(lstindex));
            lstindex++;
        }
        else
        {
            lstindex = 0;
            if (timercycle->isActive())
            {
                timercycle->stop();
            }
        }
        break;
    case CYCLEREC:                          //有接受才发，循环不停止
        if(recflag == 0)
        {
            break;
        }
    case CYCLE:                         //循环不停止
        if(lstindex >= dataList.size())
        {
            lstindex = 0;
        }
        emitsignals(dataList.at(lstindex));
        lstindex++;
        break;
    default:
        break;

    }
    recflag = 0;

}

void DialogSendData::emitsignals(const QString &data)
{
    if(ui->comboBox->currentText().contains("TCP客户端"))
    {
        emit dlgTotcpclient(data);
    }
    else if(ui->comboBox->currentText().contains("TCP服务器"))
    {
        emit dlgTotcpserver(data);
    }
    else if(ui->comboBox->currentText().contains("UDP客户端"))
    {
        emit dlgToudpclient(data);
    }
    else if(ui->comboBox->currentText().contains("UDP服务器"))
    {
        emit dlgToudpserver(data);
    }
    else if(ui->comboBox->currentText().contains("COM串口"))
    {
        emit dlgTocom(data);
    }
}

void DialogSendData::stopTimer()
{
    if (timercycle->isActive())
    {
        timercycle->stop();
    }
    if(ui->btnSendcycle->text().indexOf("停止轮询")>-1)
    {
        ui->btnSendcycle->setText("开始轮询");
    }
}

void DialogSendData::on_btnSendAll_clicked()
{

    stopTimer();

    initdataList();
    if(dataList.size()>0)
    {
        if(ui->Cb_recv->isChecked())
        {
            cycleflag = CYCLEONCEREC;
        }
        else
        {
            cycleflag = CYCLEONCE;
        }
//        recflag = 1;       //第一次发送不判是否收到报文，强制发送
        if (!timercycle->isActive())
        {
            timercycle->start(ui->timeinterval->text().toUInt());
        }
    }
}

void DialogSendData::on_btnSendcycle_clicked()
{

    if (timercycle->isActive())
    {
        timercycle->stop();
    }
    if(ui->btnSendcycle->text().indexOf("开始轮询")>-1)
    {
        initdataList();
        if(dataList.size()>0)
        {
            if(ui->Cb_recv->isChecked())
            {
                cycleflag = CYCLEREC;
            }
            else
            {
                cycleflag = CYCLE;
            }
//        recflag = 1;       //第一次发送不判是否收到报文，强制发送
            ui->btnSendcycle->setText("停止轮询");
            if (!timercycle->isActive())
            {
                timercycle->start(ui->timeinterval->text().toUInt());
            }
        }
    }
    else
    {
        ui->btnSendcycle->setText("开始轮询");
    }
}

void DialogSendData::on_comboBox_currentIndexChanged(int index)
{
    stopTimer();
}

void DialogSendData::on_Cb_recv_stateChanged(int arg1)
{
    stopTimer();
}

void DialogSendData::on_timeinterval_textChanged(const QString &arg1)
{
    stopTimer();
}
