#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(250,250,435,360);
    thread = new QThread;
    ObjGenerate = new generatedataThread;
    ui->push_start_send->setDisabled(true);
    ui->push_stop_send->setDisabled(true);
    num_port = QSerialPortInfo::availablePorts().length();

    ui->comboBox_portSpeed->addItem("115200");
    ui->comboBox_speed_1->addItem("1,2");
    ui->comboBox_speed_1->addItem("2,4");
    ui->comboBox_speed_1->addItem("4,8");
    ui->comboBox_speed_2->addItem("1,2");
    ui->comboBox_speed_2->addItem("2,4");
    ui->comboBox_speed_2->addItem("4,8");
    ui->label_statusPort_1->setText("Down");
    ui->label_statusPort_1->setStyleSheet("QLabel {font-weight: bold; color : red; }");
    ui->label_statusPort_3->setText("Down");
    ui->label_statusPort_3->setStyleSheet("QLabel {font-weight: bold; color : red; }");

    for(int i = 0; i < num_port; i++)
    {
        ui->comboBox_port->addItem(QSerialPortInfo::availablePorts().at(i).portName());
    }
    connect(this, SIGNAL(signalOpenPort(QString)), ObjGenerate, SLOT(openPort(QString)));
    connect(ObjGenerate, SIGNAL(signalToUIConnectPort(bool)), this, SLOT(slot_push_connect(bool)));
    connect(this, SIGNAL(signalClosePort()), ObjGenerate, SLOT(closePort()));
    connect(ObjGenerate, SIGNAL(signalToUiDisConnectPort(bool)), this, SLOT(slot_push_disconnect(bool)));
    connect(this, SIGNAL(signalOpenFile(QString)), ObjGenerate, SLOT(openPatternFile(QString)));
    connect(ui->checkBox_1, SIGNAL(toggled(bool)), ObjGenerate, SLOT(setCheckBox_1(bool)));
    connect(ui->checkBox_2, SIGNAL(toggled(bool)), ObjGenerate, SLOT(setCheckBox_2(bool)));
    connect(ui->comboBox_speed_1, SIGNAL(currentTextChanged(QString)), ObjGenerate, SLOT(setComboBox_speed_1(QString)));
    connect(ui->comboBox_speed_2, SIGNAL(currentTextChanged(QString)), ObjGenerate, SLOT(setComboBox_speed_2(QString)));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), ObjGenerate, SLOT(setShiftFreq(int)));

    ObjGenerate->moveToThread(thread);
    thread->start();
}
//******************************************************************************
MainWindow::~MainWindow()
{
    delete ui;
}
//******************************************************************************
void MainWindow::debugTextEdit(bool status, QString debMSG)
{
    if(status) ui->textEdit->append(QTime::currentTime().toString("HH:mm:ss") + " -> " + debMSG);
    else ui->textEdit->append("<font color = red><\\font>" + QTime::currentTime().toString("HH:mm:ss") + " -> " + debMSG);
}

void MainWindow::openPatternFile()
{
    Pattern.clear();
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName.isEmpty())
    {
        debugTextEdit(false, "File isEmpty");
        return;
    }
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        debugTextEdit(false, "File not open");
        return;
    }else debugTextEdit(true, "Control file load");
    QTextStream in(&file);
    while(!in.atEnd())
    {
        Pattern.append(in.readLine());
    }
    emit signalOpenFile(Pattern);
    return;
}
//******************************************************************************
void MainWindow::on_comboBox_portSpeed_currentIndexChanged(int index)
{
    ObjGenerate->setRate_slot(index);
}

void MainWindow::on_push_connect_clicked()
{
    emit signalOpenPort(ui->comboBox_port->currentText());
}
void MainWindow::on_push_disconnect_clicked()
{
    emit signalClosePort();
}
void MainWindow::on_push_download_clicked()
{
    openPatternFile();
}
//******************************************************************************
//***************************** SLOTS ******************************************
//******************************************************************************
void MainWindow::slot_push_connect(bool status)
{
    if(status)
    {
        debugTextEdit(true, "Connected");
        ui->label_status->setText("Connected");
        ui->label_status->setStyleSheet("QLabel {font-weight: bold; color : green; }");
        ui->push_connect->setEnabled(false);
        ui->push_disconnect->setEnabled(true);
        ui->label_info->setText(ui->comboBox_port->currentText() +" @ "+ ui->comboBox_portSpeed->currentText());
        ui->push_start_send->setEnabled(true);
        ui->push_stop_send->setEnabled(true);
    }
    else
    {
        debugTextEdit(false, "Port not open!");
    }
}

void MainWindow::slot_push_disconnect(bool status)
{
    if(status)
    {
        debugTextEdit(true, "Disconnected");
        ui->label_status->setText("Disconnected");
        ui->label_status->setStyleSheet("QLabel {font-weight: bold; color : red; }");
        ui->push_connect->setEnabled(true);
        ui->push_disconnect->setEnabled(false);
        ui->checkBox_1->setEnabled(true);
        ui->checkBox_2->setEnabled(true);
        ui->push_start_send->setEnabled(true);
        ui->comboBox_speed_1->setEnabled(true);
        ui->comboBox_speed_2->setEnabled(true);
        ui->label_statusPort_1->setText("Down");
        ui->label_statusPort_1->setStyleSheet("QLabel {font-weight: bold; color : red; }");
        ui->label_statusPort_3->setText("Down");
        ui->label_statusPort_3->setStyleSheet("QLabel {font-weight: bold; color : red; }");
    }
    else
    {
        debugTextEdit(false, "Port close error!");
    }
}

void MainWindow::slot_push_downloadFile(bool status)
{
    if(status) debugTextEdit(true, "Control file load");
    else debugTextEdit(false, "File not open");
}
