#ifndef GENERATEDATATHREAD_H
#define GENERATEDATATHREAD_H

#include <QObject>
#include <QSerialPort>

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

signals:
    void signalToUIConnectPort(bool);
    void signalToUiDisConnectPort(bool);

public slots:
    void run();
    void setRate_slot(int rate);
    void openPort(QString namePort);
    void closePort();
};

#endif // GENERATEDATATHREAD_H
