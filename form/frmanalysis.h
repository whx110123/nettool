#ifndef FRMANALYSIS_H
#define FRMANALYSIS_H

#include <QWidget>
#include "protocol101apdu.h"
#include "protocol104apdu.h"
#include "protocol103wiscomnet.h"
#include "protocol103com.h"
#include "globaldefine.h"

namespace Ui {
class frmAnalysis;
}
class myhighlighter;
class frmAnalysis : public QWidget
{
    Q_OBJECT

public:
    explicit frmAnalysis(QWidget *parent = nullptr);
    ~frmAnalysis();

private slots:
    void initForm();
    void initConfig();
//    void saveConfig();

private slots:
    void on_AnalysisBtn_clicked();

    void on_clearBtn_clicked();

    void on_protocolcbox_currentIndexChanged(const QString &arg1);

    void on_highlightEdit_textChanged(const QString &arg1);

    void on_fontcolor_clicked();

    void on_backgroundcolor_clicked();

    void on_fontchange_clicked();

private:

    Ui::frmAnalysis *ui;
    myhighlighter *highlighter1;
    myhighlighter *highlighter2;
private:
    protocol101::protocol101apdu *m_101;
    protocol101::protocol104apdu *m_104;
    protocol103::protocol103wiscomnet *m_103wiscomnet;
    protocol103::protocol103com *m_103com;

};

#endif // FRMANALYSIS_H
