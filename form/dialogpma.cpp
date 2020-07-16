#include "dialogpma.h"
#include "ui_dialogpma.h"

DialogPMA::DialogPMA(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogPMA)
{
	ui->setupUi(this);
}

DialogPMA::~DialogPMA()
{
	delete ui;
}
