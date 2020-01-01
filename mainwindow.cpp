#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLayout>
#include <QGridLayout>
#include <QMessageBox>
#include "TextCompare/textcompare.h"

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
    diffView = new CodeViewer(this);
    pushButton = new QPushButton(this);
    pushButton->setText("Compare");
    connect(pushButton, &QPushButton::pressed, this, &MainWindow::Compare);

    gridLayout->addWidget(firstView, 0, 0);
    gridLayout->addWidget(diffView, 0, 1);
    gridLayout->addWidget(secondView, 0, 2);
    gridLayout->addWidget(pushButton, 1, 1);
    central->setLayout(gridLayout);

    setLayout(gridLayout);
    setWindowTitle("Сравнение модулей");
}

void MainWindow::Compare()
{
    QMessageBox msgBox;
    /*
    auto diff = TextCompare::longestCommonSubsequence(firstView->toPlainText(), secondView->toPlainText());
    msgBox.setText(diff);
    msgBox.exec();
    */
    auto diff = TextCompare::longestCommonSubsequence(firstView->toPlainText().split("\n"), secondView->toPlainText().split("\n"));
    for (auto commonString : diff)
        diffView->appendPlainText(commonString);
    /*{
        msgBox.setText(commonString);
        msgBox.exec();
    }*/

}

MainWindow::~MainWindow()
{
    delete firstView;
    delete secondView;
    delete ui;
}

