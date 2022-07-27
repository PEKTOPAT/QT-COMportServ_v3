#include "generatedatathread.h"
#include <QDebug>

generatedataThread::generatedataThread(QObject *parent) : QObject(parent)
{


}

void generatedataThread::run()
{

    for(int i = 0; i <= 50; i++)
    {
       qDebug() << i << "ss";
    }
}

