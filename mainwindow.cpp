#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "partenaire.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    ui->tab_partenaire->setModel(P.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->le_id->text().toInt();
    int cin=ui->le_cin->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QDate datenais=ui->le_datnais->date();
    int num=ui->le_num->text().toInt();
    QString adresse=ui->le_adresse->text();
    QString domaine=ui->le_domaine->text();

    Partenaire P(id,cin,nom,prenom,datenais,num,adresse,domaine);

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

void MainWindow::on_pb_supprimer_clicked()
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



void MainWindow::on_pb_modifier_clicked()
{
    int id=ui->le_id_modif->text().toInt();
    int cin=ui->le_cin_modif->text().toInt();
    QString nommod=ui->le_nom_modif->text();
    QString prenommod=ui->le_prenom_modif->text();
    QDate datenais=ui->le_datnaismodif->date();
    int num=ui->le_nummodif->text().toInt();
    QString adressemod=ui->le_adressemodif->text();
     QString domainemodif=ui->le_domainemodif->text();
    Partenaire P(id,cin,nommod,prenommod,datenais,num,adressemod,domainemodif);

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
