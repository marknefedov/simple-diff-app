#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLayout>
#include <QMessageBox>
#include "TextCompare/textcompare.h"
#include "DBWindow/DBWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
    gridLayout = new QGridLayout();
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

    gridLayout->addWidget(firstView, 1, 0);
    gridLayout->addWidget(diffView, 1, 1);
    gridLayout->addWidget(secondView, 1, 2);
    gridLayout->addWidget(pushButton, 2, 1);
    central->setLayout(gridLayout);
    */
    connect(ui->compareButton, &QPushButton::pressed, this, &MainWindow::Compare);
    setWindowTitle("Сравнение модулей");
}

void MainWindow::Compare()
{
    ui->diffView->clear();
    QStringList firstVeiwLines = ui->firstView->toPlainText().split("\n");
    QStringList secondViewLines = ui->secondView->toPlainText().split("\n");
    QStringList lcs = TextCompare::longestCommonSubsequence<QStringList>(firstVeiwLines, secondViewLines);

    int startPos = ui->diffView->toPlainText().count();
    QTextCursor cursor = ui->diffView->textCursor();
    cursor.clearSelection();

    ui->diffView->appendPlainText("Common text:");
    for (const auto& commonString : lcs)
        ui->diffView->appendPlainText(commonString);

    int selectonEnd = ui->diffView->toPlainText().count();

    ui->diffView->appendPlainText("First diff:");
    QMap<int, QString> diffMap = TextCompare::QStringListDifference(lcs, firstVeiwLines);
    for (const auto& lineKey : diffMap.keys())
        ui->diffView->appendPlainText(QString::number(lineKey + 1) + " " + diffMap[lineKey]);

    ui->diffView->appendPlainText("Second diff:");
    diffMap = TextCompare::QStringListDifference(lcs, secondViewLines);
    for (const auto& lineKey : diffMap.keys())
        ui->diffView->appendPlainText(QString::number(lineKey + 1) + " " + diffMap[lineKey]);

    cursor.setPosition(startPos);
    cursor.setPosition(selectonEnd, QTextCursor::KeepAnchor);
    QColor lineColor = QColor(Qt::gray).lighter(110);
    QTextCharFormat format;
    format.setProperty(QTextFormat::FullWidthSelection, true);
    format.setBackground(lineColor);
    cursor.setCharFormat(format);
/*
    QTextEdit::ExtraSelection selection;
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.format.setBackground(lineColor);
    selection.cursor = cursor;
    diffView->setExtraSelections({selection});
*/
}

MainWindow::~MainWindow()
{        
    delete ui; // Все дочерние виджеты будут удалены автоматически
}
