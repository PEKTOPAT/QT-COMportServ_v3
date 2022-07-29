#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QSerialPortInfo>
#include "generatedatathread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QThread *thread;
    generatedataThread *ObjGenerate;

    int num_port;
};

#endif // MAINWINDOW_H
