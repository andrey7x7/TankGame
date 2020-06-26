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

namespace Ui {
class TankGame;
}

class TankGame : public QWidget
{
    Q_OBJECT

public:
    explicit TankGame(QWidget *parent = 0);
    ~TankGame();
    QGraphicsScene  *scene;
    QTimer timer_colides;
    Card *card_1;
    Tank *tank_1;
    Tank *tank_2;

public slots:
    void keyPress(QKeyEvent *event);
    void keyRelease(QKeyEvent *event);
private slots:
    void search_Collides();
private:
    Ui::TankGame *ui;


};

#endif // TANKGAME_H
