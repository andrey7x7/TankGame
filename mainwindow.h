#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <tankgame.h>
#include <tcp_lib.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TankGame *game_1;
    QThread *thread_s;
    QThread *thread_c;

    TCP_Server *server_1;
    TCP_Client *client_1;

protected:
   void keyPressEvent(QKeyEvent *event);
   void keyReleaseEvent(QKeyEvent *event);

private slots:
   void on_Button_new_game_clicked();
   void lanGame();
   void LanWriteClient(int key);
   void LanWriteServer(int key);
};

#endif // MAINWINDOW_H
