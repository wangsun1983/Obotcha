#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QFileSystemWatcher>

#include "clientsender.h"

int target_port = 0;
QString target_ip;

void parseConfig() {
    QFile file("config.txt");
    if(!file.exists()) {
        return;
    }

    file.open(QFile::ReadOnly);
    QVector<QString> blacktags;

    QTextStream in(&file);
    QString line;
    while((line = in.readLine())!= nullptr) {
        if(line.contains("#")) {
            continue;
        }

        if(line.contains("target_server_port")) {
            QStringList list = line.split(":");
            target_port = list[1].toLatin1().toInt();
        } else if(line.contains("target_server_ip")) {
            QStringList list = line.split(":");
            target_ip = list[1];
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    printf("iiiii \n");
    parseConfig();
    clientsender sender(target_ip,target_port,&a);
    sender.start();

    return a.exec();
}
