#ifndef TANK_H
#define TANK_H
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
//#include <QtMath>
#include <bullet.h>

class Tank : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Tank(QObject *parent = nullptr, int skin=1);

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QTimer timer_frame;           // Таймер для пролистывания изображения в QPixmap
    QTimer timer_go;              // Таймер для движения изображения
    QPixmap *spriteImage;         // В данный объект QPixamp будет помещён спрайт
    int frame=0,nap=0;
    int ww=800,hh=800;
    int angle=0;
    int speed=0;
    int health=10;
    int i=0;
    bool fire=false;
    int skin=1;


public slots:
    void set_Nap(int nap);
    void set_Fire(bool fire);
    void onDamage();

    void goUP();
    void goDOWN();
    void STOP();
    void turnLEFT();
    void turnRIGHT();
    int getANGLE();
    int getHealth();
private slots:
    void next_Frame();
};

#endif // TANK_H
