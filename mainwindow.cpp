#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    game_1->keyPress(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    game_1->keyRelease(event);
}

void MainWindow::on_Button_new_game_clicked()
{
    lanGame();
}

void MainWindow::lanGame()
{
    if(ui->radioButton_server->isChecked())
    {
        game_1 = new TankGame(this,true);
        ui->stackedWidget->insertWidget(1,game_1);
        ui->stackedWidget->setCurrentIndex(1);

        thread_s = new QThread();
        this->setWindowTitle("Tank Game (Server)");
        server_1 = new TCP_Server(this,1024);
        connect(server_1,SIGNAL(Client_Message(int)),game_1,SLOT(LanRead(int)));                    //прием данных от клиента
        connect(game_1,SIGNAL(on_keyPress(int)),server_1,SLOT(on_write(int)));    //отправка данных серверу //отправка данных клиенту
        thread_s->start();
    }

    if(ui->radioButton_client->isChecked())
    {
        game_1 = new TankGame(this,false);
        ui->stackedWidget->insertWidget(1,game_1);
        ui->stackedWidget->setCurrentIndex(1);

        this->setWindowTitle("Tank Game (Client)");
        client_1 = new TCP_Client(this);
        QString IP = ui->lineEdit_IP->text();
        client_1->on_connect(QHostAddress(IP),1024);

        connect(client_1,SIGNAL(Server_Message(int)),game_1,SLOT(LanRead(int)));  //прием данных от сервера
        connect(game_1,SIGNAL(on_keyPress(int)),client_1,SLOT(on_write(int)));    //отправка данных серверу
    }
}

void MainWindow::LanWriteServer(int key)
{
    qDebug()<<"SEND<-"<<key;
    client_1->on_write(key);
}

void MainWindow::LanWriteClient(int key)
{
    qDebug()<<"SEND<-"<<key;
    server_1->on_write(key);
}
