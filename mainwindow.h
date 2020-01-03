#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QMainWindow>
#include <QGridLayout>
#include "CodeViewer/CodeViewer.h"

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
    /*
    QGridLayout* gridLayout;
    CodeViewer* firstView;
    CodeViewer* secondView;
    CodeViewer* diffView;
    QPushButton* pushButton;
    */
    void Compare();
};

#endif // MAINWINDOW_H
