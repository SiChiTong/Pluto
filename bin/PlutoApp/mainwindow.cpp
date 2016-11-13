#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s = new Pluto::Subsystems("subsystems");
    s->searchSubsystems();

    QObject::connect(ui->searchSubButton, SIGNAL(clicked()), this, SLOT(searchSub()) );
}

void MainWindow::searchSub()
{
    ui->sub1Label->setText("");
    ui->sub1Label->setText("");
    ui->sub1Label->setText("");

    QList<Pluto::System*> l = s->getSubsystemList();
    ui->sub1Label->setText(l.at(0)->name+" "+l.at(0)->version);
    ui->sub2Label->setText(l.at(1)->name+" "+l.at(1)->version);
    ui->sub3Label->setText(l.at(2)->name+" "+l.at(2)->version);
}

MainWindow::~MainWindow()
{
    delete ui;
}
