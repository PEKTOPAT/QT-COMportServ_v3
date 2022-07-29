#include "mainwindow.h"
#include "ui_mainwindow.h"

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


    connect(thread, &QThread::started, ObjGenerate, generatedataThread::run);

    connect(ui->comboBox_portSpeed, SIGNAL(currentIndexChanged(int)), ObjGenerate, generatedataThread::setRate_slot(int));

    ObjGenerate->moveToThread(thread);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    thread->start();
}
