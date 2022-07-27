#ifndef GENERATEDATATHREAD_H
#define GENERATEDATATHREAD_H

#include <QObject>

class generatedataThread : public QObject
{
    Q_OBJECT

public:
    explicit generatedataThread(QObject *parent = 0);
    QString message;

private:


signals:

public slots:
    void run();
};

#endif // GENERATEDATATHREAD_H
