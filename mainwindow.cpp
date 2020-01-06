#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QMessageBox>
#include <QSqlQuery>
#include "TextCompare/textcompare.h"
#include "DatabaseSettings/DatabaseConnection.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>


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
    connect(ui->saveButton, &QPushButton::pressed, this, &MainWindow::SaveComparison);
    connect(ui->firstOpenFile, &QPushButton::pressed, this, &MainWindow::OpenFile1);
    connect(ui->secondOpenFile, &QPushButton::pressed, this, &MainWindow::OpenFile2);
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

   diffs = TextCompare::FindDifferentLines(firstVeiwLines, secondViewLines);

    QColor lineColor = QColor(Qt::blue).lighter(175);
    QTextCharFormat format;
    format.setProperty(QTextFormat::FullWidthSelection, true);
    format.setBackground(lineColor);

    for (int line : diffs.first)
        ui->firstView->HighlightLine(line, format);

    for (int line : diffs.second)
        ui->secondView->HighlightLine(line, format);
}

bool MainWindow::SaveComparison()
{
    QMessageBox msgBox;
    if (!DbConnection.Database.isOpen())
    {
        msgBox.setText("Нет подключения к базе данных");
        msgBox.exec();
        return false;
    }

    if (ui->firstFilename->text() == "" || ui->secondFilename->text() == "")
    {
        msgBox.setText("Укажите имена файлов.");
        msgBox.exec();
        return false;
    }

    QSqlQuery sqlQuerry;
    sqlQuerry.prepare(
                "INSERT INTO diff_table (\"firstFilename\", \"firstFileChangesCount\", \"secondFilename\", \"secondFileChangesCount\", \"date\", \"firstFileContent\", \"secondFileContent\")\n"
                "VALUES (?, ?, ?, ?, CURRENT_DATE, ?, ?);"
                );
    Compare();
    sqlQuerry.addBindValue(ui->firstFilename->text());
    sqlQuerry.addBindValue(diffs.first.count());
    sqlQuerry.addBindValue(ui->secondFilename->text());
    sqlQuerry.addBindValue(diffs.second.count());
    sqlQuerry.addBindValue(ui->firstView->toPlainText());
    sqlQuerry.addBindValue(ui->secondView->toPlainText());

    sqlQuerry.exec();

    return true;
}

QString MainWindow::readFile(const QString &filePath)
{
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QTextStream fileTextStream(&file);
    return fileTextStream.readAll();
}

void MainWindow::OpenFile1()
{
    ui->firstFilename->setText(QFileDialog::getOpenFileName(this));
    ui->firstView->setPlainText(readFile(ui->firstFilename->text()));
}

void MainWindow::OpenFile2()
{
    ui->secondFilename->setText(QFileDialog::getOpenFileName(this));
    ui->secondView->setPlainText(readFile(ui->secondFilename->text()));
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
