#include <QFile>
#include <QCoreApplication>
#include "clientsender.h"
#include <unistd.h>

clientsender::clientsender(QString ip,int port,QCoreApplication *a) {
    target_ip = ip;
    target_port = port;
    mSystemWatcher.addPath("sendcontent.txt");
    app = a;
    this->connect(&mSystemWatcher, SIGNAL(fileChanged(QString)), this, SLOT(onFileUpdated(QString)));
}

void clientsender::run() {
    mSystemWatcher.addPath("sendcontent.txt");
    this->connect(&mSystemWatcher, SIGNAL(fileChanged(QString)), this, SLOT(onFileUpdated(QString)));
}

void clientsender::onFileUpdated(QString path){
    QFile file(path);
    file.open(QFile::ReadOnly);
    QTextStream in(&file);
    QString content = in.readAll();
    qDebug()<<"write content is "<<content.size()<<";pid is "<<getpid();
    client = new QTcpSocket();
    if(content.size() == 1) {
        qDebug()<<"onFileUpdate 1";
        if(target_ip == nullptr) {
            qDebug()<<"onFileUpdate 1_1"<<target_port;
            client->connectToHost(QHostAddress::LocalHost,target_port);
        } else {
            client->connectToHost(QHostAddress(target_ip),target_port);
        }

        qDebug()<<"onFileUpdate 2_1";
        if(client->waitForConnected(30000)) {
            qDebug()<<"onFileUpdate 2_2";
            connect(client,SIGNAL(readyRead()),this,SLOT(readyRead()));
        }
        qDebug()<<"onFileUpdate 2_3";
    } else if(content.size() == 2) {
        app->quit();
    } else{
        qDebug()<<"onFileUpdate2,";
        client->connectToHost(QHostAddress(target_ip),target_port);
        if(client->waitForConnected(30000)) {
            client->write(content.toLatin1().data());
            client->flush();
            sleep(1);
        }

        client->disconnectFromHost();
        client->close();
        delete client;
    }

    disconnect(&mSystemWatcher, SIGNAL(fileChanged(QString)), this, SLOT(onFileUpdated(QString)));
    mSystemWatcher.removePath("../sendcontent.txt");
    mSystemWatcher.addPath("../sendcontent.txt");
    connect(&mSystemWatcher, SIGNAL(fileChanged(QString)), this, SLOT(onFileUpdated(QString)));
}

void clientsender::readyRead() {
    QByteArray data = client->readAll();
    qDebug()<<"receive data "<<data;
    client->write(data);
    client->flush();

    sleep(1);

    client->disconnectFromHost();
    client->close();
    delete client;
}
