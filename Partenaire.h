#ifndef PARTENAIRE_H
#define PARTENAIRE_H


#include <QString>
#include <QSqlQueryModel>
#include <QDateTime>

#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>

class Partenaire
{
public:
    Partenaire();

    Partenaire(int,int,QString,QString,QDate,int,QString,QString,int);


    int getid();
    int getduree();
    int getcin();
    int getnum();
    QString getnom();
    QString getprenom();
    QDate getdatenais();
    QString getadresse();
    QString getdomaine();

    void setid(int);
    void setduree(int);
    void setcin(int);
    void setnum(int);
    void setnom(QString);
    void setprenom(QString);
    void setdatenais(QDate);
    void setadresse(QString);
    void setdomaine(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();
    Partenaire chercher_cin(int cin_c);
    QSqlQueryModel* chercherpartenaire_par_cin(QString);
    QSqlQueryModel* trier_par_nom();
    QSqlQueryModel* trier_par_id();
   // QSqlQueryModel* afficher_id();

   // QPieSeries *statistique();


private:
    int id , cin , num , duree;
    QDate datenais;
    QString nom , prenom, adresse , domaine;
};


#endif // PARTENAIRE_H
