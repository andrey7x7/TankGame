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
    QByteArray Socket_Serialize(int key)
    {
        QByteArray dat;

        QDataStream stream(&dat,QIODevice::WriteOnly);
        stream << key;

        return dat;
    };

    //Функция десериализации
    int Socket_Deserialize(QByteArray dat)
    {
        int key;
        QByteArray datas;

        QDataStream stream(&datas,QIODevice::ReadOnly);
        datas = dat;
        stream >> key;

        return key;
    };
};

class TCP_Server : public QObject, public MySerialize
{
    Q_OBJECT
public:
    explicit TCP_Server(QObject *parent = 0,int port=8080);

public slots:
    void on_connectToServer();
    void on_write(int key);
    void on_read();

private:
    bool client=false;//наличие клиента
    QTcpServer *server_tcp;
    QTcpSocket *clientSocket;

signals:
    void Client_Connected();
    void Client_Message(int key);
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
    void on_write(int key);
    void on_read();

signals:
    void Server_Message(int key);
};

#endif // TCP_LIB_H
