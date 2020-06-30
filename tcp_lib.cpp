#include "tcp_lib.h"

//**********************   Server   ***************************

TCP_Server::TCP_Server(QObject *parent, int port) :  QObject(parent)
{
    server_tcp = new QTcpServer(this);
    server_tcp->listen(QHostAddress::Any, port);

    connect(server_tcp,SIGNAL(newConnection()),this,SLOT(on_connectToServer()));
}

//Клиент подключился к серверу
void TCP_Server::on_connectToServer()
{
    clientSocket = server_tcp->nextPendingConnection();
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(on_read()));
    QString IP=clientSocket->localAddress().toString().split("ffff:")[1];
    client=true;
    emit Client_Connected();
    qDebug()<<"new connect IP="<<IP;
}

//Сервер получил сообщение от клиента
void TCP_Server::on_read()
{
    clientSocket = static_cast<QTcpSocket*>(QObject::sender());
    QByteArray dat = clientSocket->readAll();

    emit Client_Message(Socket_Deserialize(dat));
    qDebug()<<"SERVER get message";
}

//Сервер отправил сообщение клиенту
void TCP_Server::on_write(QMap <QString,int> map)
{
    if(client)clientSocket->write(Socket_Serialize(map));
    qDebug()<<"SERVER send message";
}


//**********************   Client   ***************************

TCP_Client::TCP_Client(QObject *parent)
{
    client_tcp = new QTcpSocket(this);
    connect(client_tcp,SIGNAL(readyRead()),this,SLOT(on_read()));
}

//Коннект клиена на сервер
void TCP_Client::on_connect(QHostAddress ip_add,int port)
{
    client_tcp->connectToHost(ip_add, port, QIODevice::ReadWrite);
}

//Клиен отправил сообщение серверу
void TCP_Client::on_write(QMap <QString,int> map)
{
    client_tcp->write(Socket_Serialize(map));
    qDebug()<<"SOCKET send message";
}

//Клиент получил сообщние от сервера
void TCP_Client::on_read()
{
    QByteArray dat;

    while (client_tcp->bytesAvailable())
    {
        dat = client_tcp->readAll();
    }
    emit Server_Message(Socket_Deserialize(dat));
    qDebug()<<"SOCKET read message";
}

//************************************************************
