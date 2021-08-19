#include "dialog_create_the_connection.h"
#include "ui_dialog_create_the_connection.h"

Dialog_create_the_connection::Dialog_create_the_connection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_create_the_connection)
{
    ui->setupUi(this);
}

Dialog_create_the_connection::~Dialog_create_the_connection()
{
    delete ui;
}
