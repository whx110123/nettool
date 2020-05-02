#ifndef DIALOGDEALDATA_H
#define DIALOGDEALDATA_H

#include <QDialog>

namespace Ui {
class DialogDealData;
}

class DialogDealData : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDealData(QWidget *parent = nullptr);
    ~DialogDealData();
private slots:
	void on_pbcrc_clicked();

	void on_pbtransform_clicked();

private:
    void initfrom();
    ushort crc16(uchar *puchMsg, ushort usDataLen);

private:
    Ui::DialogDealData *ui;
};

#endif // DIALOGDEALDATA_H
