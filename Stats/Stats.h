#ifndef STATS_H
#define STATS_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlQueryModel>

namespace Ui {
class Stats;
}

class Stats : public QWidget
{
    Q_OBJECT

public:
    explicit Stats(QWidget *parent = nullptr);
    ~Stats();
protected:
    void RefreshData();

private:
    Ui::Stats *ui;
    QSqlQueryModel* model;
};

#endif // STATS_H
