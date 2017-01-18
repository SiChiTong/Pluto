#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->button_connect, &QPushButton::clicked,
            this, &MainWindow::connectRoboteq);
    connect(ui->button_disconnect, &QPushButton::clicked,
            this, &MainWindow::disconnectRoboteq);
    connect(ui->button_forward, &QPushButton::pressed,
            this, &MainWindow::forward);
    connect(ui->button_reverse, &QPushButton::pressed,
            this, &MainWindow::reverse);
    connect(ui->button_left, &QPushButton::pressed,
            this, &MainWindow::left);
    connect(ui->button_right, &QPushButton::pressed,
            this, &MainWindow::right);
    connect(ui->button_forward, &QPushButton::released,
            this, &MainWindow::stop);
    connect(ui->button_reverse, &QPushButton::released,
            this, &MainWindow::stop);
    connect(ui->button_left, &QPushButton::released,
            this, &MainWindow::stop);
    connect(ui->button_right, &QPushButton::released,
            this, &MainWindow::stop);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectRoboteq()
{
    int status = device.Connect("/dev/ttyACM0");

    if(status != RQ_SUCCESS)
    {
        cout<<"Error connecting to device: "<<status<<"."<<endl;
        return;
    }
    cout<<"connected"<<endl;
}

void MainWindow::disconnectRoboteq()
{
    device.Disconnect();
    cout<<"disconnected"<<endl;
}

void MainWindow::forward()
{
    cout<<"forward"<<endl;
    device.SetCommand(_GO, 1, 30);
}

void MainWindow::reverse()
{
    cout<<"reverse"<<endl;
}

void MainWindow::left()
{
    cout<<"left"<<endl;
}

void MainWindow::right()
{
    cout<<"right"<<endl;
}

void MainWindow::stop()
{
    cout<<"stop"<<endl;
    device.SetCommand(_GO, 1, 0);
}
