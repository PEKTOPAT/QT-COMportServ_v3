#include "generatedatathread.h"
#include <QDebug>
#include <mainwindow.h>

generatedataThread::generatedataThread(QObject *parent) :
    QObject(parent)
{
    checkBox_1 = false;
    checkBox_2 = false;
    comboBox_speed_1 = "1,2";
    comboBox_speed_2 = "1,2";

    flagRecieve_ch1 = true;
    flagRecieve_ch2 = true;
    sizeInfo_ch1 = 50;
    sizeInfo_ch2 = 50;
    sizePackage = 53;
    shiftFreq = 0;
    countByte_CH1 = 0;
    countByte_CH2 = 0;

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

void generatedataThread::openPatternFile(QString uiPattern)
{
    Pattern = uiPattern;
}

void generatedataThread::generatePackage()
{
    if(Pattern.size() == 0) return;
    Package_ch1.clear();
    Package_ch2.clear();
    QByteArray convert;
    convert = Pattern.toLocal8Bit();
    if(checkBox_1)
    {
        if(comboBox_speed_1 == "1,2")
        {
            Package_ch1.append(171);
            Package_ch1.append(33);
            Package_ch1.append(shiftFreq);
            Package_ch1.append(sizeInfo_ch1);
            for(int j = 0; j < sizeInfo_ch1; j++)
            {
                Package_ch1.append(convert.at(countByte_CH1));
                countByte_CH1++;
                if(countByte_CH1 > Pattern.length()) countByte_CH1 = 0;
            }
        }
        else if (comboBox_speed_1 == "2,4")
        {
            Package_ch1.append(171);
            Package_ch1.append(34);
            Package_ch1.append(shiftFreq);
            Package_ch1.append(sizeInfo_ch1);
            for(int j = 0; j < sizeInfo_ch1; j++)
            {
                Package_ch1.append(convert.at(countByte_CH1));
                countByte_CH1++;
                if(countByte_CH1 > Pattern.length()) countByte_CH1 = 0;
            }
        }
        else if (comboBox_speed_1 == "4,8")
        {
            Package_ch1.append(171);
            Package_ch1.append(35);
            Package_ch1.append(shiftFreq);
            Package_ch1.append(sizeInfo_ch1);
            for(int j = 0; j < sizeInfo_ch1; j++)
            {
                Package_ch1.append(convert.at(countByte_CH1));
                countByte_CH1++;
                if(countByte_CH1 > Pattern.length()) countByte_CH1 = 0;
            }
        }
    }
    if(checkBox_2)
    {
        if(comboBox_speed_2 == "1,2")
        {
            Package_ch2.append(171);
            Package_ch2.append(68);
            Package_ch2.append(shiftFreq);
            Package_ch2.append(sizeInfo_ch2);
            for(int j = 0; j < sizeInfo_ch2; j++)
            {
                Package_ch2.append(convert.at(countByte_CH2));
                countByte_CH2++;
                if(countByte_CH2 == Pattern.length()) countByte_CH2 = 0;
            }
        }
        else if (comboBox_speed_2 == "2,4")
        {
            Package_ch2.append(171);
            Package_ch2.append(72);
            Package_ch2.append(shiftFreq);
            Package_ch2.append(sizeInfo_ch2);
            for(int j = 0; j < sizeInfo_ch2; j++)
            {
                Package_ch2.append(convert.at(countByte_CH2));
                countByte_CH2++;
                if(countByte_CH2 == Pattern.length()) countByte_CH2 = 0;
            }
        }
        else if (comboBox_speed_2 == "4,8")
        {
            Package_ch2.append(171);
            Package_ch2.append(76);
            Package_ch2.append(shiftFreq);
            Package_ch2.append(sizeInfo_ch2);
            for(int j = 0; j < sizeInfo_ch2; j++)
            {
                Package_ch2.append(convert.at(countByte_CH2));
                countByte_CH2++;
                if(countByte_CH2 == Pattern.length()) countByte_CH2 = 0;
            }
        }
    }
}




//******************************************************************************
//**************   SLOT FOR SIGNAL UI   ****************************************
//******************************************************************************
void generatedataThread::setCheckBox_1(bool current)
{
    checkBox_1 = current;
}

void generatedataThread::setCheckBox_2(bool current)
{
    checkBox_2 = current;
}

void generatedataThread::setComboBox_speed_1(QString current)
{
    comboBox_speed_1 = current;
}

void generatedataThread::setComboBox_speed_2(QString current)
{
    comboBox_speed_2 = current;
}

void generatedataThread::setShiftFreq(int current)
{
    shiftFreq = current;
}


