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

private:
QSerialPort *port;

signals:

public slots:
    void run();
    void setRate_slot(int rate);

};

#endif // GENERATEDATATHREAD_H
