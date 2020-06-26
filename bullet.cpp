#include "bullet.h"
#include <QGraphicsItem>

Bullet::Bullet(QPointF point, int angle, int tank, QObject *parent) : QObject(parent)
{
    this->setData(0,"BULLET");
    this->setData(1,true);
    this->setData(2,tank);

    this->setRotation(angle);
    this->setPos(point.x(),point.y());

    spriteImage = new QPixmap(":/img/sprite.png"); // Загружаем изображение спрайта в QPixmap

    // Подключаем сигнал от таймера к слоту перелистывания кадров спрайта
    timer_go = new QTimer();
    connect(timer_go, SIGNAL(timeout()), this, SLOT(goTARGET()));

    // Запускаем таймер на генерацию сигнала
    timer_go->start(20);
}

QRectF Bullet::boundingRect() const
{
    return QRectF(-8,-45,17,17);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    //painter->drawEllipse(-5,-40,10,10);
    if(skin==1)painter->drawPixmap(-8,-45, *spriteImage, 453, 201, 17, 17);
    if(skin==2){painter->drawPixmap(-8,-45, *spriteImage, 183, 183, 56, 56);timer_go->stop();}

    if(this->x() < 0){
        this->deleteLater();       // left
    }
    if(this->x() > 800){
        this->deleteLater();        // right
    }

    if(this->y() < 0){
        this->deleteLater();       // top
    }

    if(this->y() > 800){
        this->deleteLater();        // bottom
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Bullet::goTARGET()
{
    if(this->data(1)==false)
    {
        QTimer::singleShot(500,this,SLOT(BOOM()));
        skin=2;
    }
    this->setPos(mapToParent(0,-10));

    this->update();
}

void Bullet::BOOM()
{
    this->deleteLater();
}
