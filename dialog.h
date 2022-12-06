#ifndef DIALOG_H
#define DIALOG_H
#include "employer.h"
#include <QDialog>
#include "ui_dialog.h"


#include <Partenaire.h>
#include <QPrinter>
#include "chat.h"
#include "smtp.h"
#include "arduino.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    ////////////////////////////////////////////
    void on_pb_ajouter_clicked_2();

    void on_pb_supprimer_clicked_2();

    void on_pb_modifier_clicked_2();

    void on_pb_chercher_clicked();

    void on_pb_tri_nom_clicked();

    void on_pb_tri_id_clicked();

    void on_le_pdf_clicked();

    void on_pb_Chat_clicked();

    void on_pb_ajouter_2_clicked();

    void on_pb_supprimer_2_clicked();

    void on_pb_modifier_clicked();

    void sendMail();
    void mailSent(QString);
    void browse();

    void update_label();
    ///////////////////////////////////////
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_recherche_clicked();

    void on_pb_update_clicked();

    void on_pushButton_pdf_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_refresh_clicked();



private:
    Ui::Dialog *ui;
    Chat *c;
    employer I;
    Partenaire P;
    QStringList files;
    QByteArray data;
    Arduino A;

};

#endif // DIALOG_H
