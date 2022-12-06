#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "invite.h"
#include <QMessageBox>
#include <QPainter>
#include <QDesktopServices>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QUrl>
#include <QDebug>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString cin,password;
          cin =ui->lineEdit_CINLOG->text();
          password=ui->lineEdit->text();

          employer I;
          QSqlQuery qry,query;

      if(qry.exec("select CIN,PASSWORD from EMPLOYEE where CIN='"+cin +"' and PASSWORD='"+password+"'"))
      {
              int count=0;
      while(qry.next())
      {
            count++;



       if(count==1)
       {
           query.prepare("INSERT INTO EMPLOYEE(CIN,PASSWORD) "
                                  "VALUES (:CIN,  :PW)");

                    query.bindValue(":CIN",qry.value(0).toString());

                    query.bindValue(":PW",qry.value(2).toString());

                    query.exec();



            this->hide();
              ui->lineEdit_CINLOG->clear();
              ui->lineEdit->clear();

              Dialog dialog;
                          dialog.setModal(true);
                          dialog.exec();








              }
      }

              if(count<1)
              {


              }
}}
void MainWindow::update_label()
{
    data=A.read_from_arduino();




}
