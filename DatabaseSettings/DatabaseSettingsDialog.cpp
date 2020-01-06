#include "DatabaseSettingsDialog.h"
#include "DatabaseConnection.h"
#include "ui_DatabaseSettingsDialog.h"
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>

DatabaseSettingsDialog::DatabaseSettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::DatabaseSettingsDialog)
{

    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint,false);    
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DatabaseSettingsDialog::SaveSettings);
    connect(ui->createTableButton, &QPushButton::pressed, this, &DatabaseSettingsDialog::CreateSqlTable);
}

void DatabaseSettingsDialog::SaveSettings()
{    
    bool connected =  DbConnection.Connect(
                ui->hostname->text(),
                ui->port->text(),
                ui->name->text(),
                ui->user->text(),
                ui->password->text()
                );
    QMessageBox msgbox;
    if (connected)
        msgbox.setText("Подключение успешно");
    else
        msgbox.setText("Не удалось подключиться");
    msgbox.exec();

}

void DatabaseSettingsDialog::CreateSqlTable()
{
    const QString tableQuerry(
                      "CREATE TABLE public.diff_table\n"
                      "(\n"
                      "    \"firstFilename\" text COLLATE pg_catalog.\"default\",\n"
                      "    \"firstFileChangesCount\" integer,\n"
                      "    \"secondFilename\" text COLLATE pg_catalog.\"default\",\n"
                      "    \"secondFileChangesCount\" integer,\n"
                      "    date date,\n"
                      "    \"firstFileContent\" text COLLATE pg_catalog.\"default\",\n"
                      "    \"secondFileContent\" text COLLATE pg_catalog.\"default\"\n"
                      ")\n"
                      ""
                );
    if (DbConnection.Database.isOpen())
    {
        if (DbConnection.Database.tables().contains("diff_table"))
        {
            QMessageBox msgBox;
            msgBox.setText("Таблица diff_table уже существует");
            msgBox.exec();
        }
        DbConnection.Database.exec(tableQuerry);
    }
}

DatabaseSettingsDialog::~DatabaseSettingsDialog()
{
    delete ui;
}
