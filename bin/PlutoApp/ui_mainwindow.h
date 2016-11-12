/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *sub1Label;
    QLabel *label_2;
    QLabel *sub2Label;
    QLabel *label_3;
    QLabel *sub3Label;
    QPushButton *searchSubButton;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(708, 425);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(454, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        sub1Label = new QLabel(centralWidget);
        sub1Label->setObjectName(QString::fromUtf8("sub1Label"));
        sub1Label->setMinimumSize(QSize(180, 0));
        sub1Label->setMaximumSize(QSize(180, 16777215));

        formLayout->setWidget(0, QFormLayout::FieldRole, sub1Label);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        sub2Label = new QLabel(centralWidget);
        sub2Label->setObjectName(QString::fromUtf8("sub2Label"));
        sub2Label->setMinimumSize(QSize(180, 0));
        sub2Label->setMaximumSize(QSize(180, 16777215));

        formLayout->setWidget(1, QFormLayout::FieldRole, sub2Label);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        sub3Label = new QLabel(centralWidget);
        sub3Label->setObjectName(QString::fromUtf8("sub3Label"));
        sub3Label->setMinimumSize(QSize(180, 0));
        sub3Label->setMaximumSize(QSize(180, 16777215));

        formLayout->setWidget(2, QFormLayout::FieldRole, sub3Label);


        verticalLayout->addLayout(formLayout);

        searchSubButton = new QPushButton(centralWidget);
        searchSubButton->setObjectName(QString::fromUtf8("searchSubButton"));

        verticalLayout->addWidget(searchSubButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 708, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Pluto User Interface", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "USB0:", 0, QApplication::UnicodeUTF8));
        sub1Label->setText(QApplication::translate("MainWindow", "Subsystem1", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "USB1:", 0, QApplication::UnicodeUTF8));
        sub2Label->setText(QApplication::translate("MainWindow", "Subsystem2", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "USB2:", 0, QApplication::UnicodeUTF8));
        sub3Label->setText(QApplication::translate("MainWindow", "Subsystem3", 0, QApplication::UnicodeUTF8));
        searchSubButton->setText(QApplication::translate("MainWindow", "Search Subsystems", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
