#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLayout>
#include <QMessageBox>
#include "TextCompare/textcompare.h"
#include "DatabaseSettings/DatabaseConnection.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // QSqlDatabase: an instance of QCoreApplication is required for loading driver plugins
    DbConnection.Database = QSqlDatabase::addDatabase("QPSQL");

    ui->setupUi(this);
    dialog = new DatabaseSettingsDialog();
    statsWindow = new Stats();
    connect(ui->compareButton, &QPushButton::pressed, this, &MainWindow::Compare);
    connect(ui->openDatabaseSettings, &QAction::triggered, this, &MainWindow::OpenDBSettingsWindow);
    connect(ui->openStats, &QAction::triggered, this, &MainWindow::OpenStatsWindow);
}

void MainWindow::Compare()
{    
    ui->firstView->ResetCharFormat();

    QStringList firstVeiwLines = ui->firstView->toPlainText().split("\n", QString::SplitBehavior::KeepEmptyParts);
    QStringList secondViewLines = ui->secondView->toPlainText().split("\n", QString::SplitBehavior::KeepEmptyParts);

    for (int i = 0; i < firstVeiwLines.count(); i++)
        firstVeiwLines[i] = TextCompare::RightTrimm(firstVeiwLines[i]);

    for (int i = 0; i < secondViewLines.count(); i++)
        secondViewLines[i] = TextCompare::RightTrimm(secondViewLines[i]);

    QPair<QList<int>, QList<int>> diffs = TextCompare::FindDifferentLines(firstVeiwLines, secondViewLines);

    QColor lineColor = QColor(Qt::blue).lighter(175);
    QTextCharFormat format;
    format.setProperty(QTextFormat::FullWidthSelection, true);
    format.setBackground(lineColor);

    for (int line : diffs.first)
        ui->firstView->HighlightLine(line, format);

    for (int line : diffs.second)
        ui->secondView->HighlightLine(line, format);
}

void MainWindow::OpenDBSettingsWindow()
{    
    dialog->show();
}

void MainWindow::OpenStatsWindow()
{
    statsWindow->show();
}

MainWindow::~MainWindow()
{            
    delete statsWindow;
    delete dialog;
    delete ui; // Все дочерние виджеты будут удалены автоматически
}
