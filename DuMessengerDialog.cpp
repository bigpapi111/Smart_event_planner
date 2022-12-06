#include "DuMessengerDialog.h"
#include "ui_DuMessengerDialog.h"

DuMessengerDialog::DuMessengerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DuMessengerDialog)
{
    ui->setupUi(this);
}

DuMessengerDialog::~DuMessengerDialog()
{
    delete ui;
}
