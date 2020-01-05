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
    model = new QSqlQueryModel();
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

    model->setQuery(ui->sqlQuerryEdit->text(), DbConnection.Database);
    //model->select();
    qDebug() << model->lastError().text();
    ui->tableView->setModel(model);
}

Stats::~Stats()
{    
    delete model;
    delete ui;
}
