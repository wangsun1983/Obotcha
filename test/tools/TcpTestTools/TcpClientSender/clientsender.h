#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFileSystemWatcher>
#include <QThread>
#include <QCoreApplication>

class clientsender :public QThread
{
    Q_OBJECT

public:
    clientsender(QString,int,QCoreApplication *);

private:
    QFileSystemWatcher mSystemWatcher;
    QString target_ip;
    int target_port;

    QTcpSocket *client;

    QCoreApplication *app;

private slots:
    void onFileUpdated(QString);
    void readyRead();

public:
    void run();

};

#endif // TCPSERVER_H
