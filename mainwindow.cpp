#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLayout>
#include <QMessageBox>
#include "TextCompare/textcompare.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->compareButton, &QPushButton::pressed, this, &MainWindow::Compare);    
}

void MainWindow::Compare()
{    
    ui->firstView->ResetCharFormat();

    QStringList firstVeiwLines = ui->firstView->toPlainText().split("\n", QString::SplitBehavior::KeepEmptyParts);
    QStringList secondViewLines = ui->secondView->toPlainText().split("\n", QString::SplitBehavior::KeepEmptyParts);
    QPair<QList<int>, QList<int>> diffs = TextCompare::FindDifferentLines(firstVeiwLines, secondViewLines);

    QColor lineColor = QColor(Qt::gray).lighter(110);
    QTextCharFormat format;
    format.setProperty(QTextFormat::FullWidthSelection, true);
    format.setBackground(lineColor);

    for (int line : diffs.first)
        ui->firstView->HighlightLine(line, format);

    for (int line : diffs.second)
        ui->secondView->HighlightLine(line, format);
}

MainWindow::~MainWindow()
{        
    delete ui; // Все дочерние виджеты будут удалены автоматически
}
