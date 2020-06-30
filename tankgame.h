#ifndef TANKGAME_H
#define TANKGAME_H

#include <QWidget>
#include <QGraphicsScene>
#include <tank.h>
#include <bullet.h>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>
#include <card.h>
#include <tcp_lib.h>
#include <QPoint>

namespace Ui {
class TankGame;
}

class TankGame : public QWidget
{
    Q_OBJECT

public:
    explicit TankGame(QWidget *parent = 0, bool server=false);
    ~TankGame();
    QGraphicsScene  *scene;
    QTimer timer_colides;
    QTimer timer_sinc;
    Card *card_1;
    Tank *tank_1;
    Tank *tank_2;

public slots:
    void keyPress(QKeyEvent *event);
    void keyRelease(QKeyEvent *event);
    void LanRead(int key);
    void SincClient();
    void SincPlane(This_position pos);
private slots:
    void search_Collides();

    void keyStop();
signals:
    void on_keyPress(int key);
    void on_keyRelease(int key);
    void getPositions(This_position *pos);

private:
    Ui::TankGame *ui;
    bool server_mode;
    bool gaz=false;


};

#endif // TANKGAME_H
