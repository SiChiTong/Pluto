#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

#define LEFT  1
#define RIGHT 2

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mCurrSpeed(0)
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
    connect(ui->slider_speed, &QSlider::valueChanged,
            this, &MainWindow::setSpeed);
    connect(ui->slider_acc_1, &QSlider::valueChanged,
            this, &MainWindow::setAcc1);
    connect(ui->slider_acc_2, &QSlider::valueChanged,
            this, &MainWindow::setAcc2);
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
    device.SetCommand(_GO, RIGHT, (-1)*mCurrSpeed);
    device.SetCommand(_GO, LEFT, mCurrSpeed);
}

void MainWindow::reverse()
{
    cout<<"reverse"<<endl;
    device.SetCommand(_GO, RIGHT, mCurrSpeed);
    device.SetCommand(_GO, LEFT, (-1)*mCurrSpeed);
}

void MainWindow::left()
{
    cout<<"left"<<endl;
    device.SetCommand(_GO, RIGHT, (-1)*mCurrSpeed);
    device.SetCommand(_GO, LEFT, (-1)*mCurrSpeed);
}

void MainWindow::right()
{
    cout<<"right"<<endl;
    device.SetCommand(_GO, RIGHT, mCurrSpeed);
    device.SetCommand(_GO, LEFT, mCurrSpeed);
}

void MainWindow::stop()
{
    cout<<"stop"<<endl;
    device.SetCommand(_MSTOP, 1);
    device.SetCommand(_MSTOP, 2);
}

void MainWindow::setSpeed(int spd)
{
    cout<<"Setting speed: "<<spd<<endl;
    mCurrSpeed = spd;
    ui->label_speed->setText(QString::number(spd));
}

void MainWindow::setAcc1(int acc)
{
    cout<<"Setting acc 1: "<<acc<<endl;
//    device.SetCommand(_ACCEL, 1, acc);
//    device.SetCommand(_DECEL, 1, acc);
    ui->label_acc_1->setText(QString::number(acc));
}

void MainWindow::setAcc2(int acc)
{
    cout<<"Setting acc 2: "<<acc<<endl;
//    device.SetCommand(_ACCEL, 2, acc);
//    device.SetCommand(_DECEL, 2, acc);
    ui->label_acc_2->setText(QString::number(acc));
}
