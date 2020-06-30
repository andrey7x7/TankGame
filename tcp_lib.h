#ifndef TCP_LIB_H
#define TCP_LIB_H
#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDataStream>
#include "qdebug.h"
#include "QMap"

struct MySerialize
{
    //Функция сериализации
    QByteArray Socket_Serialize(QMap <QString,int> map)
    {
        QByteArray dat;

        QDataStream stream(&dat,QIODevice::WriteOnly);
        stream << map;

        return dat;
    };

    //Функция десериализации
    QMap <QString,int> Socket_Deserialize(QByteArray dat)
    {
        QMap <QString,int> map;
        QByteArray datas;

        QDataStream stream(&datas,QIODevice::ReadOnly);
        datas = dat;
        stream >> map;

        return map;
    };
};

class TCP_Server : public QObject, public MySerialize
{
    Q_OBJECT
public:
    explicit TCP_Server(QObject *parent = 0,int port=8080);

public slots:
    void on_connectToServer();
    void on_write(QMap<QString, int> map);
    void on_read();

private:
    bool client=false;//наличие клиента
    QTcpServer *server_tcp;
    QTcpSocket *clientSocket;

signals:
    void Client_Connected();
    void Client_Message(QMap<QString, int> map);
};


class TCP_Client : public QObject, public MySerialize
{
    Q_OBJECT
public:
    explicit TCP_Client(QObject *parent = 0);

private:
    QTcpSocket *client_tcp;

public slots:
    void on_connect(QHostAddress ip_add, int port);
    void on_write(QMap<QString, int> map);
    void on_read();

signals:
    void Server_Message(QMap<QString, int> map);
};

#endif // TCP_LIB_H
