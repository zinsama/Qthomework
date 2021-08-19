#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chessboard.h"
#include "dialog_create_the_connection.h"
#include "dialog_connect_to_server.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionStart,&QAction::triggered,ui->frame,&chessboard::gene_new_chessboard);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionCreate_the_connection_triggered()
{
    dialog = new Dialog_create_the_connection(this);
    dialog -> setWindowTitle(QString("Create the connection"));
    dialog -> show();
}


void MainWindow::on_actionConnect_to_Server_triggered()
{
    dialog2 = new Dialog_Connect_to_Server(this);
    dialog2 -> setWindowTitle(QString("Connect to Server triggered"));
    dialog2 -> show();
}

void MainWindow::generateChess(QMainWindow *NowWindow){
    
}

