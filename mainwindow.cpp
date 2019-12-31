#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "CodeViewer/CodeViewer.h"
#include <QLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CodeViewer* myViewer = new CodeViewer(this);
    layout()->addWidget(myViewer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

