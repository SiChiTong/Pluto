#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "subsystems.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void searchSub();


private:
    Ui::MainWindow *ui;
    Pluto::Subsystems *s;
};

#endif // MAINWINDOW_H
