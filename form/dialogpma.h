#ifndef DIALOGPMA_H
#define DIALOGPMA_H

#include <QDialog>
#include <iec104.h>

namespace Ui {
	class DialogPMA;
}

class DialogPMA : public QDialog
{
	Q_OBJECT

public:
	explicit DialogPMA(QWidget *parent = nullptr);
	~DialogPMA();
public slots:
	void dealData(const QString &data,const QString &title);
signals:

	void dlgTotcpclient(const QString &data);
	void dlgTotcpserver(const QString &data);
	void dlgToudpclient(const QString &data);
	void dlgToudpserver(const QString &data);
	void dlgTocom(const QString &data);
private slots:
	void init();
	void handleData();
	void startdebug();
	void stopdebug();
	void emitsignals(const QString &data);

	void on_pushButton_start_clicked();

	void on_pushButton_sendasdu_clicked();

private:
	Ui::DialogPMA *ui;
	IEC104 *piec104;
	IECDataConfig config;
	QTimer *handleDataTimer;
	QByteArray recvData;
	bool haveData;
};

#endif // DIALOGPMA_H
