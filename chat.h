#ifndef CHAT_H
#define CHAT_H

#include <QWidget>

namespace Ui {
class Chat;
}
class QTcpSocket;
class Chat : public QWidget
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = nullptr);
    ~Chat();

private slots:
    void on_send_clicked();

    void on_bind_clicked();


private:
    Ui::Chat *ui;
    QTcpSocket *mSocket;
};

#endif // CHAT_H
