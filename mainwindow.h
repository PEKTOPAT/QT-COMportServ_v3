#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>
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

    void on_comboBox_portSpeed_currentIndexChanged(int index);
    void on_push_connect_clicked();
    void slot_push_connect(bool status);
    void slot_push_disconnect(bool status);

    void on_push_disconnect_clicked();

private:
    Ui::MainWindow *ui;
    QThread *thread;
    generatedataThread *ObjGenerate;
    int num_port;
    QString namePort;

    void debugTextEdit(bool status, QString debMSG);
signals:
    void signalOpenPort(QString);
    void signalClosePort();
};

#endif // MAINWINDOW_H
