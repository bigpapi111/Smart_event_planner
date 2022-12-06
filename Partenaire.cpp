#include "Partenaire.h"


#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>

#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlQueryModel>
#include <QDate>

Partenaire::Partenaire()
{
id=0 ,cin=0,num=0, duree=0;
nom="",prenom="",adresse="",domaine="";
datenais.setDate(2000,01,01);

}

Partenaire::Partenaire(int id,int cin,QString nom,QString prenom,QDate datenais,int num,QString adresse,QString domaine,int duree)
{this->id=id;this->cin=cin; this->nom=nom; this->prenom=prenom;this->datenais=datenais;this->num=num; this->adresse=adresse; this->domaine=domaine; this->duree=duree;}

int Partenaire::getid(){return id;}
void Partenaire::setid(int id){this->id=id;}


int Partenaire::getcin(){return cin;}
void Partenaire::setcin(int cin){this->cin=cin;}

int Partenaire::getnum(){return num;}
void Partenaire::setnum(int num){this->num=num;}


QString Partenaire::getadresse(){return adresse;}
void Partenaire::setadresse(QString adresse){this->adresse=adresse;}

QString Partenaire::getnom(){return nom;}
void Partenaire::setnom(QString nom){this->nom=nom;}

QString Partenaire::getprenom(){return prenom;}
void Partenaire::setprenom(QString prenom){this->prenom=prenom;}

void Partenaire::setdatenais(QDate datenais){this->datenais=datenais;}
QDate Partenaire::getdatenais(){return datenais;}

QString Partenaire::getdomaine(){return domaine;}
void Partenaire::setdomaine(QString domaine){this->domaine=domaine;}

int Partenaire::getduree(){return duree;}
void Partenaire::setduree(int duree){this->duree=duree;}


bool Partenaire::ajouter()
{


  QString id_string= QString::number(id);
  QString cin_string= QString::number(cin);
  QString duree_string= QString::number(duree);
QString num_string= QString::number(num);
  QSqlQuery query;
       query.prepare("INSERT INTO PARTENAIRE (id, nom, prenom,cin,datenaissance,telephone,adresse,domaine,annee) "
                     "VALUES (:id, :forename, :surname,:cin,:date,:num,:adresse,:domaine,:duree)");
       query.bindValue(0, id_string);
       query.bindValue(1, nom);
       query.bindValue(2, prenom);
       query.bindValue(3, cin_string);
       query.bindValue(4, datenais.toString());
       query.bindValue(5, num_string);
       query.bindValue(6, adresse);
       query.bindValue(7, domaine);
       query.bindValue(8, duree_string);
       return query.exec();
}

bool Partenaire::supprimer(int id)
{
    QSqlQuery query;
         query.prepare(" Delete from Partenaire where id=:id");
         query.bindValue(0, id);

         return query.exec();

}


QSqlQueryModel * Partenaire::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();

          model->setQuery("SELECT * FROM Partenaire");

          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("DateNaissance"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephone"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("Domaine"));
          model->setHeaderData(8, Qt::Horizontal, QObject::tr("Année d'expertise"));

return model;
}

bool Partenaire::modifier()
{


  QString id_string= QString::number(id);
  QString cin_string= QString::number(cin);
  QString num_string= QString::number(num);
  QString duree_string= QString::number(duree);
  //QDate date = datenais;
  //QDate datenais_string= QString::number(datenais);

  QSqlQuery query;
       query.prepare("update PARTENAIRE set id='"+id_string+"',cin='"+cin_string+"',nom='"+nom+"',prenom='"+prenom+"',datenaissance='"+datenais.toString()+"',adresse='"+adresse+"',domaine='"+domaine+"',annee='"+duree_string+"' where id='"+id_string+"'" );

       return query.exec();
}

QSqlQueryModel* Partenaire::chercherpartenaire_par_cin(QString cin)
{

    QSqlQueryModel * model = new QSqlQueryModel();

          model->setQuery("SELECT * FROM Partenaire WHERE cin like '"+cin+"%' ");

          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("DateNaissance"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephone"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("Domaine"));
          model->setHeaderData(8, Qt::Horizontal, QObject::tr("Année d'expertise"));

return model;
}

QSqlQueryModel * Partenaire::trier_par_nom()
{
    QSqlQueryModel * model = new QSqlQueryModel();

          model->setQuery("SELECT * FROM Partenaire order by nom");

          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("DateNaissance"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephone"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("Domaine"));
          model->setHeaderData(8, Qt::Horizontal, QObject::tr("Année d'expertise"));

return model;
}

QSqlQueryModel * Partenaire::trier_par_id()
{
    QSqlQueryModel * model = new QSqlQueryModel();

          model->setQuery("SELECT * FROM Partenaire order by id");

          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("DateNaissance"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephone"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("Domaine"));
          model->setHeaderData(8, Qt::Horizontal, QObject::tr("Année d'expertise"));

return model;
}














