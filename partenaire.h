#ifndef PARTENAIRE_H
#define PARTENAIRE_H
#include <QString>
#include <QSqlQueryModel>
#include <QDateTime>

class Partenaire
{
public:
    Partenaire();

    Partenaire(int,int,QString,QString,QDate,int,QString,QString);


    int getid();
    int getcin();
    int getnum();
    QString getnom();
    QString getprenom();
    QDate getdatenais();
    QString getadresse();
    QString getdomaine();

    void setid(int);
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
private:
    int id ,cin,num;
    QDate datenais;
    QString nom , prenom, adresse,domaine;
};

#endif // PARTENAIRE_H
