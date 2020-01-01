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
    // forum.qt.io/topic/53814/qlayout-attempting-to-add-qlayout-to-mainwindow-which-already-has-a-layout-solved/4
    auto central = new QWidget(this);
    setCentralWidget(central);

    firstView = new CodeViewer(this);
    secondView = new CodeViewer(this);
    diffView = new CodeViewer(this);
    pushButton = new QPushButton(this);
    pushButton->setText("Сравнить");
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
    diffView->clear();
    QStringList firstVeiwLines = firstView->toPlainText().split("\n");
    QStringList secondViewLines = secondView->toPlainText().split("\n");
    QStringList lcs = TextCompare::longestCommonSubsequence(firstVeiwLines, secondViewLines);
    diffView->appendPlainText("Common text:");
    for (const auto& commonString : lcs)
        diffView->appendPlainText(commonString);

    diffView->appendPlainText("First diff:");
    QMap<int, QString> diffMap = TextCompare::QStringListDifference(lcs, firstVeiwLines);
    for (const auto& lineKey : diffMap.keys())
        diffView->appendPlainText(QString::number(lineKey + 1) + " " + diffMap[lineKey]);



    diffView->appendPlainText("Second diff:");
    diffMap = TextCompare::QStringListDifference(lcs, secondViewLines);
    for (const auto& lineKey : diffMap.keys())
        diffView->appendPlainText(QString::number(lineKey + 1) + " " + diffMap[lineKey]);       
}

MainWindow::~MainWindow()
{    
    delete ui; // Все дочерние виджеты будут удалены автоматически
}
