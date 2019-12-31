#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "CodeViewer/CodeViewer.h"
#include <QLayout>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    QGridLayout* gridLayout = new QGridLayout(this);
    // Что-бы накинуть свлой QLayout на MainWindows обязательно надо использовать прослойку из центрального виджета
    // https://forum.qt.io/topic/53814/qlayout-attempting-to-add-qlayout-to-mainwindow-which-already-has-a-layout-solved/4
    auto central = new QWidget(this);
    setCentralWidget(central);

    firstView = new CodeViewer(this);
    secondView = new CodeViewer(this);

    gridLayout->addWidget(firstView, 0, 0);
    gridLayout->addWidget(secondView, 0, 2);

    central->setLayout(gridLayout);

    setLayout(gridLayout);
    setWindowTitle("Simple diff app");
}

MainWindow::~MainWindow()
{
    delete firstView;
    delete secondView;
    delete ui;
}

