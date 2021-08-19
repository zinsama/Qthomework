#ifndef DIALOG_CONNECT_TO_SERVER_H
#define DIALOG_CONNECT_TO_SERVER_H

#include <QDialog>

namespace Ui {
class Dialog_Connect_to_Server;
}

class Dialog_Connect_to_Server : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Connect_to_Server(QWidget *parent = nullptr);
    ~Dialog_Connect_to_Server();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog_Connect_to_Server *ui;
};

#endif // DIALOG_CONNECT_TO_SERVER_H
