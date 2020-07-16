#ifndef DIALOGPMA_H
#define DIALOGPMA_H

#include <QDialog>

namespace Ui {
	class DialogPMA;
}

class DialogPMA : public QDialog
{
	Q_OBJECT

public:
	explicit DialogPMA(QWidget *parent = nullptr);
	~DialogPMA();

private:
	Ui::DialogPMA *ui;
};

#endif // DIALOGPMA_H
