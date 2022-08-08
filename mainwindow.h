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

    void slot_push_connect(bool status);
    void slot_push_disconnect(bool status);
    void slot_send_Package(int status);
    void slot_stop_Package();
    void slot_reset_Arduino(bool status);
    void slot_set_Correction_lbl(QString number);
    void on_comboBox_portSpeed_currentIndexChanged(int index);
    void on_push_connect_clicked();
    void on_push_clear_log_clicked();
    void openPatternFile();
    void debugTextEdit(bool status, QString debMSG);
    void refrashPort();

private:
    Ui::MainWindow *ui;
    QThread *thread;
    generatedataThread *ObjGenerate;
    int num_port;
    QString namePort;
    QString Pattern;
    QTimer *timer_RefrashPort;

signals:
    void signalConnectPort(QString);
    void signalOpenFile(QString);

};

#endif // MAINWINDOW_H
