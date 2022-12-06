#include "dialog.h"
#include "ui_dialog.h"
#include "employer.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QTextDocument>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QTextStream>
#include <QtPrintSupport/QPrintDialog>
#include<QPdfWriter>
#include<QDesktopServices>
#include <QHeaderView>
#include "QImage"
#include <QPainter>
#include "iostream"
#include <QSqlQuery>
#include <QFileDialog>
#include <QPixmap>
#include <QPainter>
#include "connection.h"
#include <QtWidgets/QApplication>
#include <QtCore/QTime>
#include <QTextEdit>
#include <QIntValidator>
#include<QWidget>
#include <QTextDocument>
#include <QTextEdit>
#include <fstream>
#include <QTextStream>
#include <QRadioButton>
#include <QPixmap>
#include <QPainter>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QSvgGenerator>
#include<QDir>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QAbstractPrintDialog>
#include<QDirModel>
#include <QtPrintSupport/QPrintDialog>
#include<QPdfWriter>
#include<QDesktopServices>
#include <QHeaderView>
#include "QImage"
#include <QPainter>
#include "iostream"
#include "qrcode.h"
#include "qrcodegenerateworker.h"
#include <QFileDialog>
#include <QDialog>
#include "stat.h"
#include <QDebug>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->tab_invitee->setModel(I.afficher());

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int ret=A.connect_arduino();
    switch (ret) {
    case(0):qDebug()<<"arduino is availible and connected to :"<<A.getarduino_port_name();
        break;
    case(1):qDebug()<<"arduino is availible but not connected to :"<<A.getarduino_port_name();
        break;
    case(-1):qDebug()<<"arduino is not availible ";
    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));



        ////////////////////////////////////////////////////////////////
        ui->tab_partenaire->setModel(P.afficher());

        connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
        connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));


        QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                           QCoreApplication::organizationName(), QCoreApplication::applicationName());

        ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");

        ///////////////////////////


        QPieSeries *series = new QPieSeries();

        QSqlQueryModel * model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM Partenaire where ANNEE > 5");
        int a= model->rowCount();


        model->setQuery("SELECT * FROM Partenaire where ANNEE < 5");
        int b = model->rowCount();




        series->setHoleSize(0.35);

        QPieSlice *slice1 =series->append("partenaire expert",a);
        QPieSlice *slice = series->append("partenaire non expert",b);

        slice->setExploded();
        slice->setLabelVisible();


        slice1->setLabelVisible();


        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->setTitle("Analyse et segmentation d'expertise");
        chart->setTheme(QChart::ChartThemeBlueCerulean);


        QChartView *chartview = new QChartView(chart);
        chartview->setRenderHint(QPainter::Antialiasing);

        chartview->setParent(ui->horizontalFrame);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pb_ajouter_clicked()
{
    int cin=ui->le_cin->text().toInt();
       QString nom=ui->le_nom->text();
       QString prenom=ui->le_prenom->text();
       QString metier=ui->le_metier->text();
       int age=ui->le_age->text().toInt();
       int password=ui->le_password->text().toInt();

     employer I(cin,nom,prenom,metier,age,password);
     bool test=I.ajouter();
     QMessageBox msgBox;
     if(test){
                 QMessageBox::information(nullptr, QObject::tr("ok"),
                             QObject::tr("ajout effectué.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);

             }
             else
                 QMessageBox::critical(nullptr, QObject::tr("not ok"),
                             QObject::tr("ajout non effectué.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
}

void Dialog::on_pb_supprimer_clicked()
{
    employer I1; I1.setcin(ui->le_cin_supp->text().toInt());
        bool test=I1.supprimer(I1.getcin());
        QMessageBox msgBox;
        if (test)
          {  msgBox.setText("Suppression avec succes.");
        ui->tab_invitee->setModel(I.afficher());

        }
        else
            msgBox.setText("Echec de suppression.");
        msgBox.exec();
}

void Dialog::on_pb_recherche_clicked()
{
    employer I3;
    QString rech =ui->le_r->text();
     ui->tableView->setModel(I3.chercher_invite(rech));
}

void Dialog::on_pb_update_clicked()
{
    int cin=ui->le_cin_modf->text().toInt();
       QString nom=ui->le_nom_modf->text();
       QString prenom=ui->le_prenom_modf->text();
       QString metier=ui->le_metier_modf->text();
       int age=ui->le_age_modf->text().toInt();
       int password=ui->le_password_modf->text().toInt();
       employer I2(cin,nom,prenom,metier,age,password);
   //    I2.setcin(ui->le_cin_modf->text().toInt());
       bool test=I2.modifier();
        // I2.getcin();

       QMessageBox msgBox;
       if(test){
            ui->tab_invitee->setModel(I.afficher());


                   QMessageBox::information(nullptr, QObject::tr("ok"),
                               QObject::tr("update effectué.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);

                   ui->le_cin->clear();
                                         ui->le_nom_modf->clear();
                                         ui->le_prenom_modf->clear();
                                         ui->le_metier_modf->clear();
                                         ui->le_age_modf->clear();
                                         ui->le_password_modf->clear();


               }
               else
                   QMessageBox::critical(nullptr, QObject::tr("not ok"),
                               QObject::tr("update non effectué.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
}

void Dialog::on_pushButton_pdf_clicked()
{
    QPdfWriter fichier_pdf("C:\\slayem\\invitee.pdf");


                           QPainter painter(&fichier_pdf);
                           int i = 4000;
                                  painter.setPen(Qt::red);
                                  painter.setFont(QFont("Time New Roman", 25));
                                  painter.drawText(3000,1400,"Liste Des Invités");
                                  painter.setPen(Qt::black);
                                  painter.setFont(QFont("Time New Roman", 15));
                                  painter.drawRect(100,100,9400,2500);
                                  painter.drawRect(100,3000,9400,500);
                                  painter.setFont(QFont("Time New Roman", 9));
                                  painter.drawText(400,3300,"CIN");
                                  painter.drawText(1350,3300,"NOM");
                                  painter.drawText(2200,3300,"PRENOM");
                                  painter.drawText(3400,3300,"METIER");
                                  painter.drawText(4500,3300,"AGE");
                                  painter.drawText(5500,3300,"PASSWORD");


                                  QSqlQuery query;
                                  query.prepare("select * from inviter");
                                  query.exec();
                                  while (query.next())
                                                            {
                                                                painter.drawText(400,i,query.value(0).toString());
                                                                painter.drawText(1350,i,query.value(1).toString());
                                                                painter.drawText(2300,i,query.value(2).toString());
                                                                painter.drawText(3400,i,query.value(3).toString());
                                                                painter.drawText(4500,i,query.value(4).toString());
                                                                painter.drawText(5500,i,query.value(5).toString());



                                                               i = i + 350;
                                                            }
                                  QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
                                                            QObject::tr("PDF Enregistré.\n" "Click Cancel to exit."), QMessageBox::Cancel);



}

void Dialog::on_pushButton_2_clicked()
{

    ui->tableView_2->setModel(I.afficher_tri());
}

void Dialog::on_pushButton_3_clicked()
{
    if(ui->tab_invitee->currentIndex().row()==-1)

                                          QMessageBox::information(nullptr, QObject::tr("Suppression"),

                                                                   QObject::tr("Veuillez Choisir une CIN du Tableau.\n"

                                                                               "Click Ok to exit."), QMessageBox::Ok);

                                      else

                                      {

                                           int CIN=ui->tab_invitee->model()->data(ui->tab_invitee->model()->index(ui->tab_invitee->currentIndex().row(),0)).toInt();

                                           const qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(std::to_string(CIN).c_str(), qrcodegen::QrCode::Ecc::LOW);


                                           std::ofstream myfile;

                                           myfile.open ("qrcode.svg") ;

                                              myfile << qr.toSvgString(2);

                                              myfile.close();

                                              QSvgRenderer svgRenderer(QString("qrcode.svg"));

                                              QPixmap pix( QSize(90, 90));

                                              QPainter pixPainter( &pix );

                                              svgRenderer.render(&pixPainter);

                                           ui->label_11->setPixmap(pix);

                                      }
}

void Dialog::on_pushButton_4_clicked()
{
    int res;
                      statistiques w(this);
                      w.setWindowTitle("Statistiques Des Invités");

                      res = w.exec();
                      qDebug() << res;
                      if (res == QDialog::Rejected)
                        return;
}

void Dialog::on_pushButton_refresh_clicked()
{
    int cin=ui->le_cin_modf->text().toInt();
       QString nom=ui->le_nom_modf->text();
       QString prenom=ui->le_prenom_modf->text();
       QString metier=ui->le_metier_modf->text();
       int age=ui->le_age_modf->text().toInt();
       int password=ui->le_password_modf->text().toInt();
       employer I2(cin,nom,prenom,metier,age,password);
   //    I2.setcin(ui->le_cin_modf->text().toInt());
       bool test=I2.modifier();
        // I2.getcin();

       QMessageBox msgBox;
       if(test){
            ui->tab_invitee->setModel(I.afficher());


                   QMessageBox::information(nullptr, QObject::tr("ok"),
                               QObject::tr("Refresh effectué.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);

                   ui->le_cin->clear();
                                         ui->le_nom_modf->clear();
                                         ui->le_prenom_modf->clear();
                                         ui->le_metier_modf->clear();
                                         ui->le_age_modf->clear();
                                         ui->le_password_modf->clear();


               }
               else
                   QMessageBox::critical(nullptr, QObject::tr("not ok"),
                               QObject::tr("Refresh non effectué.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
}
/////////////////////////////////////////////////////////////////////////////////////////////////

//#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include "Partenaire.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "smtp.h"
#include <QDebug>
#include "arduino.h"
#include <QDate>
#include <QDateTime>

//MainWindow::MainWindow(QWidget *parent) :
    //QMainWindow(parent),
    //ui(new Ui::MainWindow)
/*Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

    ui->setupUi(this);

int ret=A.connect_arduino();
switch (ret) {
case(0):qDebug()<<"arduino is availible and connected to :"<<A.getarduino_port_name();
    break;
case(1):qDebug()<<"arduino is availible but not connected to :"<<A.getarduino_port_name();
    break;
case(-1):qDebug()<<"arduino is not availible ";
}
QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));



    ////////////////////////////////////////////////////////////////
    ui->tab_partenaire->setModel(P.afficher());

    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));


    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::organizationName(), QCoreApplication::applicationName());

    ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");

    ///////////////////////////


    QPieSeries *series = new QPieSeries();

    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Partenaire where ANNEE > 5");
    int a= model->rowCount();


    model->setQuery("SELECT * FROM Partenaire where ANNEE < 5");
    int b = model->rowCount();




    series->setHoleSize(0.35);

    QPieSlice *slice1 =series->append("partenaire expert",a);
    QPieSlice *slice = series->append("partenaire non expert",b);

    slice->setExploded();
    slice->setLabelVisible();


    slice1->setLabelVisible();


    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle("Analyse et segmentation d'expertise");
    chart->setTheme(QChart::ChartThemeBlueCerulean);


    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);

    chartview->setParent(ui->horizontalFrame);


}

MainWindow::~MainWindow()
{
    delete ui;
}*/

void Dialog::on_pb_ajouter_clicked_2()
{
    int id=ui->le_id->text().toInt();
    int cin=ui->le_cin_2->text().toInt();
    QString nom=ui->le_nom_2->text();
    QString prenom=ui->le_prenom_2->text();
    QDate datenais=ui->le_datnais->date();
    int num=ui->le_num->text().toInt();
    QString adresse=ui->le_adresse->text();
    QString domaine=ui->le_domaine->text();
    int duree=ui->le_duree->text().toInt();

    Partenaire P(id,cin,nom,prenom,datenais,num,adresse,domaine,duree);

    bool test = P.ajouter();

    if(test){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Ajout effectué \n"),QMessageBox::Cancel);
        ui->tab_partenaire->setModel(P.afficher());
    }else {
        QMessageBox::information(nullptr,QObject::tr("not OK"),
                                 QObject::tr("Ajout non effectué \n"),QMessageBox::Cancel);

}
}

void Dialog::on_pb_supprimer_clicked_2()
{

    Partenaire P1; P1.setid(ui->le_id_supp->text().toInt());
    bool test = P1.supprimer(P1.getid());

    if(test){

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Supprission effectué \n"),QMessageBox::Cancel);
        ui->tab_partenaire->setModel(P.afficher());

    }else {
        QMessageBox::information(nullptr,QObject::tr("not OK"),
                                 QObject::tr("Supprission non effectué \n"),QMessageBox::Cancel);

}
}



void Dialog::on_pb_modifier_clicked_2()
{
    int id=ui->le_id_modif->text().toInt();
    int cin=ui->le_cin_modif->text().toInt();
    QString nommod=ui->le_nom_modif->text();
    QString prenommod=ui->le_prenom_modif->text();
    QDate datenais=ui->le_datnaismodif->date();
    int num=ui->le_nummodif->text().toInt();
    QString adressemod=ui->le_adressemodif->text();
     QString domainemodif=ui->le_domainemodif->text();
     int duree=ui->le_dureemodif->text().toInt();
    Partenaire P(id,cin,nommod,prenommod,datenais,num,adressemod,domainemodif,duree);

    bool test = P.modifier();

    if(test){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("modification effectué \n"),QMessageBox::Cancel);
        ui->tab_partenaire->setModel(P.afficher());
    }else {
        QMessageBox::information(nullptr,QObject::tr("not OK"),
                                 QObject::tr("modification non effectué \n"),QMessageBox::Cancel);

}

}

void Dialog::on_pb_chercher_clicked()
{
    QString cin=ui->le_cin_chercher->text();
    ui->tab_partenaire->setModel(P.chercherpartenaire_par_cin(cin));
}

void Dialog::on_pb_tri_nom_clicked()
{
    ui->tab_partenaire->setModel(P.trier_par_nom());
}

void Dialog::on_pb_tri_id_clicked()
{
    ui->tab_partenaire->setModel(P.trier_par_id());
}

void Dialog::on_le_pdf_clicked()
{
    QPdfWriter pdf("C:/Users/melek/Desktop/projet c++/file.PDF");
        QPainter painter(&pdf);
        int i = 4000;
        painter.setPen(Qt::red);
        QFontDatabase::addApplicationFont("😕../../Sangrita.ttf");
        painter.setFont(QFont("Sangrita", 30));
        painter.drawText(2500,1600,"Liste Des Partenaire");
        painter.setPen(Qt::black);
        painter.setFont(QFont("Times", 50));
        // painter.drawText(1100,2000,afficheDC);
        painter.drawRect(2000,900,5500,1000);
       //painter.drawPixmap(QRect(70,70,1500,1500),QPixmap("C:/Users/user/OneDrive/Bureau/projet 2/logo app/1 (2).png"));
        painter.drawRect(10,3000,9000,550);
        painter.setFont(QFont("Arial", 12));
        painter.drawText(900,3300,"id");
        painter.drawText(2233,3300,"nom");
        painter.drawText(3566,3300,"prenom");
        painter.drawText(4899,3300,"cin");


        QSqlQuery query;
        query.prepare("select * from Partenaire");
        query.exec();
        while (query.next())
        {
            painter.drawText(900,i,query.value(0).toString());
            painter.drawText(2233,i,query.value(1).toString());
            painter.drawText(3566,i,query.value(2).toString());
            painter.drawText(5299,i,query.value(3).toString());



            i = i +500;
        }
        int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/melek/Desktop/projet c++/file.PDF"));

            painter.end();
        }
        if (reponse == QMessageBox::No)
        {
            painter.end();
        }

}
void Dialog::on_pb_Chat_clicked()
{

    c= new Chat();
    c->show();

}

void  Dialog::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}
void   Dialog::sendMail()
{
    Smtp* smtp = new Smtp("melek.hamadi@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("melek.hamadi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("melek.hamadi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   Dialog::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}

void Dialog::update_label()
{

    data=A.read_from_arduino();


    QString a="";
    foreach(char c ,data){
        a = a + c;
    }

    QString data_String = QString(data) ;
    ui->le_texti->append(data);
    qDebug()<<data_String;

    //QString dataString = QTextCodec::codecForMib(1015)->toUnicode(data);
   // qDebug()<<data_String;

    QSqlQuery query;
    QString d =QDateTime::currentDateTime().toString();
         query.prepare("INSERT INTO ARDUINO (id_carte,DATE_INSERT) VALUES (:data_String, :d)");
         query.bindValue(0, data_String);
         query.bindValue(1, d);
         query.exec();

         if(query.exec())
         {
             A.write_to_arduino("1");
         }
         else
         {
             A.write_to_arduino("0");
         }

}



void Dialog::on_pb_ajouter_2_clicked()
{

    int id=ui->le_id->text().toInt();
    int cin=ui->le_cin_2->text().toInt();
    QString nom=ui->le_nom_2->text();
    QString prenom=ui->le_prenom_2->text();
    QDate datenais=ui->le_datnais->date();
    int num=ui->le_num->text().toInt();
    QString adresse=ui->le_adresse->text();
    QString domaine=ui->le_domaine->text();
    int duree=ui->le_duree->text().toInt();

    Partenaire P(id,cin,nom,prenom,datenais,num,adresse,domaine,duree);

    bool test = P.ajouter();

    if(test){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Ajout effectué \n"),QMessageBox::Cancel);
        ui->tab_partenaire->setModel(P.afficher());
    }else {
        QMessageBox::information(nullptr,QObject::tr("not OK"),
                                 QObject::tr("Ajout non effectué \n"),QMessageBox::Cancel);

}
}

void Dialog::on_pb_supprimer_2_clicked()
{

    Partenaire P1; P1.setid(ui->le_id_supp->text().toInt());
    bool test = P1.supprimer(P1.getid());

    if(test){

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Supprission effectué \n"),QMessageBox::Cancel);
        ui->tab_partenaire->setModel(P.afficher());

    }else {
        QMessageBox::information(nullptr,QObject::tr("not OK"),
                                 QObject::tr("Supprission non effectué \n"),QMessageBox::Cancel);

}


}

void Dialog::on_pb_modifier_clicked()
{
    int id=ui->le_id_modif->text().toInt();
    int cin=ui->le_cin_modif->text().toInt();
    QString nommod=ui->le_nom_modif->text();
    QString prenommod=ui->le_prenom_modif->text();
    QDate datenais=ui->le_datnaismodif->date();
    int num=ui->le_nummodif->text().toInt();
    QString adressemod=ui->le_adressemodif->text();
     QString domainemodif=ui->le_domainemodif->text();
     int duree=ui->le_dureemodif->text().toInt();
    Partenaire P(id,cin,nommod,prenommod,datenais,num,adressemod,domainemodif,duree);

    bool test = P.modifier();

    if(test){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("modification effectué \n"),QMessageBox::Cancel);
        ui->tab_partenaire->setModel(P.afficher());
    }else {
        QMessageBox::information(nullptr,QObject::tr("not OK"),
                                 QObject::tr("modification non effectué \n"),QMessageBox::Cancel);

}

}





