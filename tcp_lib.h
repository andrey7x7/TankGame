#ifndef TCP_LIB_H
#define TCP_LIB_H
#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDataStream>
#include "qdebug.h"
#include "QMap"
#include "QPoint"

//[class Serializable]
class This_position
{
public:
    This_position() {}
    This_position(QPoint t1,QPoint t2) {this->t1 = t1;this->t2=t2;}

    QPoint get_t1(){return t1;}
    QPoint get_t2(){return t2;}

    QPoint t1;
    QPoint t2;

    //перегрузка записи
    friend QDataStream &operator <<(QDataStream &stream, This_position &pos)
    {
        stream << pos.t1;
        stream << pos.t2;
        return stream;
    }

    //перегрузка чтения
    friend QDataStream &operator >>(QDataStream &stream, This_position &pos)
    {
        stream >> pos.t1;
        stream >> pos.t2;
        return stream;
    }
};

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

    //Функция сериализации
    QByteArray Point_Serialize(This_position *pos)
    {
        QByteArray dat;

        QDataStream stream(&dat,QIODevice::WriteOnly);
        stream << pos;

        return dat;
    };

    //Функция десериализации
    This_position Point_Deserialize(QByteArray dat)
    {
        This_position pos;
        QByteArray datas;

        QDataStream stream(&datas,QIODevice::ReadOnly);
        datas = dat;
        stream >> pos;

        return pos;
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

    void on_write_point(This_position *pos);
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
    void Server_Message(This_position pos);
};

#endif // TCP_LIB_H
