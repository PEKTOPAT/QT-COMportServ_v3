#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void slot_send_Package(int status);
    void slot_stop_Package();
    void on_push_reset_arduin_clicked();
    void on_push_clear_log_clicked();
    void on_push_stop_send_clicked();
    void openPatternFile();

private:
    Ui::MainWindow *ui;
    QThread *thread;
    generatedataThread *ObjGenerate;
    int num_port;
    QString namePort;
    QString Pattern;

    void debugTextEdit(bool status, QString debMSG);
signals:
    void signalConnectPort(QString);
    void signalOpenFile(QString);
};

#endif // MAINWINDOW_H
