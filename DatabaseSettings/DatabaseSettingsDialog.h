#ifndef DATABASESETTINGSDIALOG_H
#define DATABASESETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class DatabaseSettingsDialog;
}

class DatabaseSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseSettingsDialog(QWidget *parent = nullptr);
    ~DatabaseSettingsDialog();    
private:
    Ui::DatabaseSettingsDialog *ui;

    void SaveSettings();
    void CreateSqlTable();
};

#endif // DATABASESETTINGSDIALOG_H
