#include "qplutotheme.h"

#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QPlutoTheme::applyDarkTheme();
    w.show();
    return a.exec();
}
