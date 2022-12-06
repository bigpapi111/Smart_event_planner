#include "chat.h"
#include "ui_chat.h"
#include <QTcpSocket>
#include <QTextStream>
#include "DuMessengerConnectionDialog.h"


Chat::Chat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
    mSocket= new QTcpSocket(this);
    connect(mSocket, &QTcpSocket::readyRead, [&](){
            QTextStream T(mSocket);
            auto text = T.readAll();
            ui->textEdit->append(text);
        });
}

Chat::~Chat()
{
    delete ui;
}

void Chat::on_send_clicked()
{
    QTextStream T(mSocket);
       T << ui->name ->text() << ":" << ui->message->text();
       mSocket->flush();
       ui->message->clear();

}
void Chat::on_bind_clicked()
{
    DuMessengerConnectionDialog D(this);
        if(D.exec()== QDialog::Rejected){
            return;
        }
        mSocket->connectToHost(D.Hostname(), D.Port());

}
