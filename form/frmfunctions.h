#ifndef FRMFUNCTIONS_H
#define FRMFUNCTIONS_H

#include <QWidget>
#include "dialogsenddata.h"
#include "dialogdealdata.h"

namespace Ui {
class frmFunctions;
}

class frmFunctions : public QWidget
{
    Q_OBJECT

public:
    explicit frmFunctions(QWidget *parent = nullptr);
    ~frmFunctions();

private slots:
    void on_pushButton_clicked();
    void initfrom();

    void on_pbfunc2_clicked();

private:
    Ui::frmFunctions *ui;
public:
    DialogSendData *m_dialogsenddata;
    DialogDealData *m_dialogdealdata;

};

#endif // FRMFUNCTIONS_H
