#include "mainwindow.h"
#include <QApplication>

#include "subsystems.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Pluto::Subsystems *s = new Pluto::Subsystems("subsystems");
    Q_UNUSED(s)

    w.show();

    return a.exec();
}
