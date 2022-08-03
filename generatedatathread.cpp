#include "generatedatathread.h"
#include <QDebug>

generatedataThread::generatedataThread(QObject *parent) :
    QObject(parent)
{
    flagRecieve_ch1 = true;
    flagRecieve_ch2 = true;
    sizeInfo_ch1 = 50;
    sizeInfo_ch2 = 50;
    sizePackage = 53;

    port = new QSerialPort(this);
    port->setDataBits(QSerialPort::Data8);
    port->setFlowControl(QSerialPort::NoFlowControl);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setBaudRate(QSerialPort::Baud115200);
}

void generatedataThread::run()
{
    qDebug() << "andrei RUN";
}

void generatedataThread::setRate_slot(int rate)
{
    if(rate == 0) port->setBaudRate(QSerialPort::Baud9600);
    else if (rate == 1) port->setBaudRate(QSerialPort::Baud19200);
    else if (rate == 2) port->setBaudRate(QSerialPort::Baud38400);
    else if (rate == 3) port->setBaudRate(QSerialPort::Baud57600);
    else if (rate == 4) port->setBaudRate(QSerialPort::Baud115200);
}

void generatedataThread::openPort(QString namePort)
{
    port->setPortName(namePort);
    if(!port) emit signalToUIConnectPort(false);
    if(port->isOpen()) port->close();
    port->open(QIODevice::ReadWrite);
    if(port->isOpen())
    {
        emit signalToUIConnectPort(true);
    }else emit signalToUIConnectPort(false);
}

void generatedataThread::closePort()
{
    if (!port) signalToUiDisConnectPort(false);
    if(port->isOpen())
    {
        port->close();
        flagRecieve_ch1 = true;
        flagRecieve_ch2 = true;
        Package_ch1.clear();
        Package_ch2.clear();
        sizeInfo_ch1 = 50;
        sizeInfo_ch2 = 50;
        sizePackage = 53;

        emit signalToUiDisConnectPort(true);

    }
    else signalToUiDisConnectPort(false);
}

