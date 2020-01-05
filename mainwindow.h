#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QMainWindow>
#include <QGridLayout>
#include "CodeViewer/CodeViewer.h"
#include "DatabaseSettings/DatabaseSettingsDialog.h"
#include "Stats/Stats.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DatabaseSettingsDialog* dialog;
    Stats* statsWindow;

    void Compare();
    void OpenDBSettingsWindow();
    void OpenStatsWindow();
};

#endif // MAINWINDOW_H
