#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "dialog_create_the_connection.h"
#include "dialog_connect_to_server.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void generateChess(QMainWindow*);
    ~MainWindow();
    
private slots:
    void on_actionCreate_the_connection_triggered();

    void on_actionConnect_to_Server_triggered();

signals:
    void start_play();
private:
    Dialog_create_the_connection* dialog;
    Dialog_Connect_to_Server* dialog2;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
