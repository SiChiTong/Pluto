#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s = new Pluto::Subsystems("subsystems");

    QObject::connect(ui->searchSubButton, SIGNAL(clicked()), this, SLOT(searchSub()) );
}

void MainWindow::searchSub()
{
    ui->sub1Label->setText("");
    ui->sub1Label->setText("");
    ui->sub1Label->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}
