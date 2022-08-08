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
    flagStopReceive = false;
    sizeInfo_ch1 = 50;
    sizeInfo_ch2 = 50;
    sizePackage = 53;
    shiftFreq = 0;
    countByte_CH1 = 0;
    countByte_CH2 = 0;
    flagMain = false;
    correction_Freq = 0;

    port = new QSerialPort(this);
    port->setDataBits(QSerialPort::Data8);
    port->setFlowControl(QSerialPort::NoFlowControl);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setBaudRate(QSerialPort::Baud115200);

    connect(port, SIGNAL(readyRead()), this, SLOT(readPort()));
}

//******************************************************************************
void generatedataThread::setRate_slot(int rate)
{
    if(rate == 0) port->setBaudRate(QSerialPort::Baud9600);
    else if (rate == 1) port->setBaudRate(QSerialPort::Baud19200);
    else if (rate == 2) port->setBaudRate(QSerialPort::Baud38400);
    else if (rate == 3) port->setBaudRate(QSerialPort::Baud57600);
    else if (rate == 4) port->setBaudRate(QSerialPort::Baud115200);
}
//******************************************************************************
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
//******************************************************************************
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
//******************************************************************************
void generatedataThread::openPatternFile(QString uiPattern)
{
    Pattern = uiPattern;
}
//******************************************************************************
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
void generatedataThread::sendPackage()
{
    flagStopReceive = false;
    if(Pattern.size() == 0)
    {
        emit signalToUiSendMsg(0);
        return;
    }
    generatePackage();
    if(Package_ch1.size() != 0 && flagRecieve_ch1)
    {
        writePort(Package_ch1);
        correctionFreq();
        emit signalToUiSendMsg(1);

    }
    if(Package_ch2.size() != 0 && flagRecieve_ch2)
    {
        writePort(Package_ch2);
        correctionFreq();
        emit signalToUiSendMsg(2);
    }

    flagRecieve_ch1 = false;
    flagRecieve_ch2 = false;
    sizeInfo_ch1 = 15;
    sizeInfo_ch2 = 15;
    sizePackage = 18;
}
//******************************************************************************
void generatedataThread::stopSendPackage()
{
        emit signalToUiStopMsg();
        sizeInfo_ch1 = 50;
        sizeInfo_ch2 = 50;
        sizePackage = 53;
        flagStopReceive = true;
        flagRecieve_ch1 = true;
        flagRecieve_ch2 = true;
        Package_ch1.clear();
        Package_ch2.clear();
}
//******************************************************************************
void generatedataThread::writePort(QByteArray data)
{
    port->write(data);
}
//******************************************************************************
void generatedataThread::readPort()
{
    qDebug() << "ReadSlot";
    if(flagStopReceive)
    {
        port->clear(QSerialPort::AllDirections);
        return;
    }
    QByteArray data;
    QByteArray transit;
    if (port->bytesAvailable() == 0) return;
    data = port->readAll();
    qDebug() << data;
    for(int i = 0; i < data.size(); i++)
    {
        transit.clear();
        transit.append(data[i]);
        const QString tab = " ";
        QString strData;
        int intData = static_cast<quint8>(transit.at(0));
        for (int i = 0;i < transit.size();i++)
        {
            strData = strData+QString("%1").arg(intData)+tab;
        }
        strData.resize(strData.length() - 1);
        if(!flagMain && strData == "170") flagMain = true;
        else if (flagMain)
        {
            if(strData == "64")
            {
                flagRecieve_ch1 = true;
                sendPackage();
                flagMain = false;
            }
            else if(strData == "65")
            {
                flagRecieve_ch1 = true;
                sendPackage();
                flagMain = false;
            }
            else if(strData == "67")
            {
                flagMain = false;
            }
            else if(strData == "71")
            {
                flagMain = false;
            }
            else if(strData == "128")
            {
                flagRecieve_ch2 = true;
                sendPackage();
                flagMain = false;
            }
            else if(strData == "136")
            {
                flagRecieve_ch2 = true;
                sendPackage();
                flagMain = false;
            }
            else if(strData == "152")
            {
                flagMain = false;
            }
            else if(strData == "184")
            {
                flagMain = false;
            }
            else if(strData == "201")
            {

                flagRecieve_ch1 = true;
                flagRecieve_ch2 = true;
                sendPackage();
                flagMain = false;
            }
            else if(strData == "217")
            {
                flagRecieve_ch1 = true;
                sendPackage();
                flagMain = false;
            }
            else if(strData == "249")
            {
                flagRecieve_ch1 = true;
                sendPackage();
                flagMain = false;
            }
            else if(strData == "203")
            {

                flagRecieve_ch2 = true;
                sendPackage();
                flagMain = false;
            }
            else if(strData == "207")
            {
                flagRecieve_ch2 = true;
                sendPackage();
                flagMain = false;
            }
            else if((strData == "219")||(strData == "223")||(strData == "251")||(strData == "255"))
            {
                flagMain = false;
            }
            else if(strData == "0")
            {
                flagMain = false;
                signalDebugTextEdit(false, "BufferEmpty");
                stopSendPackage();
            }
            else
            {
                signalDebugTextEdit(false, "Err read data!");
                flagMain = false;
            }
        }
        else
        {
            signalDebugTextEdit(true, "Waiting to start");
            return;
        }
    }
    return;
}

void generatedataThread::correctionFreq()
{
    if(checkBox_1)
    {
        if(comboBox_speed_1 == "1,2")
        {
            double speed = 13333;
            correction_Freq = 16000000 / speed;
            double helper = 16000000 / (speed + shiftFreq);
            correction_Freq = helper - correction_Freq;
        }
        else if(comboBox_speed_1 == "2,4")
        {
            double speed = 6667;
            correction_Freq = 16000000 / speed;
            double helper = 16000000 / (speed + shiftFreq);
            correction_Freq = helper - correction_Freq;
        }
        else if(comboBox_speed_1 == "4,8")
        {
            double speed = 3333;
            correction_Freq = 16000000 / speed;
            double helper = 16000000 / (speed + shiftFreq);
            correction_Freq = helper - correction_Freq;
        }
        emit signalToUiSetCorrection(QString::number(correction_Freq, 'f', 3));
        //ui->lbl_correction->setText(QString::number(correction_Freq, 'f', 3));
    }
    else if(checkBox_2)
    {
        if(comboBox_speed_2 == "1,2")
        {
            double speed = 13333;
            correction_Freq = 16000000 / speed;
            double helper = 16000000 / (speed + shiftFreq);
            correction_Freq = helper - correction_Freq;
        }
        else if(comboBox_speed_2 == "2,4")
        {
            double speed = 6667;
            correction_Freq = 16000000 / speed;
            double helper = 16000000 / (speed + shiftFreq);
            correction_Freq = helper - correction_Freq;
        }
        else if(comboBox_speed_2 == "4,8")
        {
            double speed = 3333;
            correction_Freq = 16000000 / speed;
            double helper = 16000000 / (speed + shiftFreq);
            correction_Freq = helper - correction_Freq;
        }
        emit signalToUiSetCorrection(QString::number(correction_Freq, 'f', 3));
    }
}
//******************************************************************************
void generatedataThread::reset_Arduino()
{
    QByteArray msg;
    msg.append(170);
    if(port->isOpen())
    {
        writePort(msg);
        flagRecieve_ch1 = true;
        flagRecieve_ch2 = true;
        Package_ch1.clear();
        Package_ch2.clear();
        sizeInfo_ch1 = 50;
        sizeInfo_ch2 = 50;
        sizePackage = 53;
        emit signalToUiResetArduino(true);
    }
    else
    {
        emit signalToUiResetArduino(false);
        return;
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
