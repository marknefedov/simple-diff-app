#include "Stats.h"
#include "ui_Stats.h"
#include "DatabaseSettings/DatabaseConnection.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>

Stats::Stats(QWidget *parent) : QWidget(parent), ui(new Ui::Stats)
{
    ui->setupUi(this);
    connect(ui->refreshButton, &QPushButton::pressed, this, &Stats::RefreshData);
    model = new QSqlTableModel(this, DbConnection.Database);
}

void Stats::RefreshData()
{
    if (!DbConnection.Database.isOpen())
    {
        QMessageBox msgBox;
        msgBox.setText("Нет подключения к базе данных.");
        msgBox.exec();
        return;
    }

    model->setTable("diff_table");
    model->select();    
    model->setHeaderData(0, Qt::Horizontal, "Первый файл");
    model->setHeaderData(1, Qt::Horizontal, "Отличных строк");
    model->setHeaderData(2, Qt::Horizontal, "Второй файл");
    model->setHeaderData(3, Qt::Horizontal, "Отличных строк");
    model->setHeaderData(4, Qt::Horizontal, "Дата");

    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(5, true);
    ui->tableView->setColumnHidden(6, true);
}

Stats::~Stats()
{    
    delete model;
    delete ui;
}
