#include "employer.h"
#include<QSqlQuery>
employer::employer()
{
    cin=0; nom=""; prenom="" ; metier="";age=0;password=0;

}
employer::employer(int cin,QString nom,QString prenom,QString metier,int age,int password)
{this->cin=cin; this->nom=nom; this->prenom=prenom;this->metier=metier;this->age=age;this->password=password;}
int employer::getcin(){return cin;}
QString employer::getnom(){return nom;}
QString employer::getprenom(){return prenom;}
QString employer::getmetier(){return metier;}
int employer::getage(){return age;}
int employer::getpassword(){return password;}
void employer::setcin(int cin){this->cin=cin;}
void employer::setnom(QString nom){this->nom=nom;}
void employer::setprenom(QString prenom){this->prenom=prenom;}
void employer::setmetier(QString metier){this->metier=metier;}
void employer::setage(int age){this->age=age;}
void employer::setpassword(int password){this->password=password;}
bool employer::ajouter()
{

        QString cin_string= QString::number(cin);
         QString age_string= QString::number(age);
          QString password_string= QString::number(password);
        QSqlQuery query;
              query.prepare("INSERT INTO EMPLOYEE (CIN, NOM,PRENOM,METIER,AGE,PASSWORD) "
                            "VALUES (:cin, :nom, :prenom, :metier, :age, :password)");
              query.bindValue(":cin",cin_string);
              query.bindValue(":nom", nom);
              query.bindValue(":prenom", prenom);
               query.bindValue(":metier", metier);
               query.bindValue(":age",age_string);
               query.bindValue(":password",password_string);
              return query.exec();




        }
bool employer::supprimer(int cin)
{
    QSqlQuery query;
          query.prepare("delete from EMPLOYEE where cin=:cin");
          query.bindValue(0,cin);

          return query.exec();




}







QSqlQueryModel* employer::afficher()
{
        QSqlQueryModel* model=new QSqlQueryModel();

        model->setQuery("SELECT * FROM EMPLOYEE ");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("METIER"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("AGE"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("PASSWORD"));






  return model;
}
QSqlQueryModel* employer::chercher_invite(QString rech){
    QString sQuery="SELECT cin,nom,prenom,metier, age, password FROM EMPLOYEE WHERE nom LIKE'%"+rech+"%' or prenom LIKE'%"+rech+"%'or metier LIKE'%"+rech+"%'or age LIKE'%"+rech+"%'or password LIKE'%"+rech+"%' ";

    QSqlQueryModel*model4=new QSqlQueryModel();

    QSqlQuery qry;

    qry.prepare(sQuery);

    qry.exec();
    model4->setQuery(qry);
    return model4;
}

bool employer::modifier()
{
     QSqlQuery query;
     QString cin_string= QString::number(cin);
 QString age_string= QString::number(age);
 QString password_string= QString::number(password);
     query.prepare("UPDATE EMPLOYEE SET nom=:nom , prenom=:prenom , metier=:metier, age=:age, password=:password "
                   " where cin= :cin");
     query.bindValue(":cin",cin_string);
     query.bindValue(":nom",nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":metier",metier);
     query.bindValue(":age",age_string);
     query.bindValue(":password",password_string);


     return query.exec();

}

QSqlQueryModel * employer::afficher_tri()
{
    QSqlQuery query;
  QString squery="SELECT cin ,nom,prenom,metier,age from EMPLOYEE ORDER BY cin";
  QSqlQueryModel*model=new QSqlQueryModel();
  query.prepare(squery);
  query.exec();
  model->setQuery(query);
  return model;
}
int employer::calculer1(int choix,int choix2)
{
    QSqlQuery query;
          query.prepare("SELECT * FROM EMPLOYEE WHERE age BETWEEN (:choix) AND (:choix2)");
          query.bindValue(":choix",choix);
          query.bindValue(":choix2",choix2);

          query.exec();
          int total = 0;
          while (query.next()) {
            total++;
 }

          return total; }
