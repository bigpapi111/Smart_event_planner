#ifndef DUMESSENGERDIALOG_H
#define DUMESSENGERDIALOG_H

#include <QDialog>

namespace Ui {
class DuMessengerDialog;
}

class DuMessengerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DuMessengerDialog(QWidget *parent = nullptr);
    ~DuMessengerDialog();

private:
    Ui::DuMessengerDialog *ui;
};

#endif // DUMESSENGERDIALOG_H
