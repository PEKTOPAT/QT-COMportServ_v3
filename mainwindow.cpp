#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&thread_1, &QThread::started, &Object_1, generatedataThread::run);
    connect(&thread_2, &QThread::started, &Object_2, generatedataThread::run);

    Object_1.moveToThread(&thread_1);
    Object_2.moveToThread(&thread_2);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_write_1_clicked()
{

}

void MainWindow::on_pushButton_write_2_clicked()
{

}

void MainWindow::on_pushButton_start_clicked()
{
    thread_1.start();
    thread_2.start();
}

void MainWindow::on_pushButton_stop_clicked()
{

}
