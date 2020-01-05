#include "DatabaseSettingsDialog.h"
#include "DatabaseConnection.h"
#include "ui_DatabaseSettingsDialog.h"
#include <QMessageBox>

DatabaseSettingsDialog::DatabaseSettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::DatabaseSettingsDialog)
{

    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint,false);    
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DatabaseSettingsDialog::SaveSettings);
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

DatabaseSettingsDialog::~DatabaseSettingsDialog()
{
    delete ui;
}
