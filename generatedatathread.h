#ifndef GENERATEDATATHREAD_H
#define GENERATEDATATHREAD_H

#include <QObject>
#include <QSerialPort>
#include <QFileDialog>

class generatedataThread : public QObject
{
    Q_OBJECT

public:
    explicit generatedataThread(QObject *parent = 0);
    QString message;
    QSerialPort *port;

private:

    bool flagRecieve_ch1;
    bool flagRecieve_ch2;
    QByteArray Package_ch1;
    QByteArray Package_ch2;
    int sizeInfo_ch1;
    int sizeInfo_ch2;
    int sizePackage;
    QString Pattern;
    bool checkBox_1;
    bool checkBox_2;
    QString comboBox_speed_1;
    QString comboBox_speed_2;
    short shiftFreq;
    int countByte_CH1;
    int countByte_CH2;
    bool flagStopReceive;
    bool flagMain;
    double correction_Freq;

signals:
    void signalToUIConnectPort(bool);
    void signalToUiDisConnectPort(bool);
    void signalToUiSendMsg(int);
    void signalToUiStopMsg();
    void signalDebugTextEdit(bool, QString);
    void signalToUiResetArduino(bool);
    void signalToUiSetCorrection(QString);

public slots:
    void setRate_slot(int rate);

private slots:
    void openPort(QString namePort);
    void closePort();
    void openPatternFile(QString uiPattern);
    void generatePackage();
    void sendPackage();
    void stopSendPackage();
    void writePort(QByteArray data);
    void readPort();
    void correctionFreq();
    void reset_Arduino();
    void setCheckBox_1(bool current);
    void setCheckBox_2(bool current);
    void setComboBox_speed_1(QString current);
    void setComboBox_speed_2(QString current);
    void setShiftFreq(int current);
};

#endif // GENERATEDATATHREAD_H
