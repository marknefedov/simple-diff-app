#include "DatabaseConnection.h"
#include <QSqlQuery>

DatabaseConnection DbConnection;

bool DatabaseConnection::Connect(const QString& hostname, const QString& port, const QString& name, const QString& user, const QString& password)
{
    this->Hostname = hostname;
    bool validPort;
    this->Port = port.toInt(&validPort);
    if (!validPort) return false;
    this->Name = name;
    this->User = user;
    this->Password = password;
    return Connect();
}

bool DatabaseConnection::Connect()
{    
    Database.setHostName(Hostname);
    Database.setPort(Port);
    Database.setDatabaseName(Name);
    Database.setUserName(User);
    Database.setPassword(Password);

    return  Database.open();       
}
