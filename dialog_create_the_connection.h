#ifndef DIALOG_CREATE_THE_CONNECTION_H
#define DIALOG_CREATE_THE_CONNECTION_H

#include <QDialog>

namespace Ui {
class Dialog_create_the_connection;
}

class Dialog_create_the_connection : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_create_the_connection(QWidget *parent = nullptr);
    ~Dialog_create_the_connection();

private:
    Ui::Dialog_create_the_connection *ui;
};

#endif // DIALOG_CREATE_THE_CONNECTION_H
