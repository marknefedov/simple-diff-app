#ifndef DATABASESETTINGS_H
#define DATABASESETTINGS_H

#include <QString>
#include <QSqlDatabase>

struct DatabaseConnection
{
    QString Hostname;
    int Port;
    QString Name;
    QString User;
    QString Password;
    QSqlDatabase Database;

    bool Connect(const QString& Hostname, const QString& Port, const QString& Name, const QString& User, const QString& Password);
    bool Connect();    
};

extern DatabaseConnection DbConnection;

#endif // DATABASESETTINGS_H
