#include "tank.h"

Tank::Tank(QObject *parent,int skin) :  QObject(parent)
{
    this->skin=skin;
    spriteImage = new QPixmap(":/img/sprite.png"); // Загружаем изображение спрайта в QPixmap

    // Подключаем сигнал от таймера к слоту перелистывания кадров спрайта
    connect(&timer_frame, SIGNAL(timeout()), this, SLOT(next_Frame()));

    // Запускаем таймер на генерацию сигнала
    timer_frame.start(100);
}

QRectF Tank::boundingRect() const
{
    return QRectF(-33,-39,65,78);
}

void Tank::set_Nap(int nap)
{
    this->nap=nap;
}

void Tank::set_Fire(bool fire)
{

}

void Tank::onDamage()
{
    health--;
}

int Tank::getHealth()
{
    return health;
}

void Tank::next_Frame()
{
    if(nap==1)
    {
        if(frame>0)
            frame-=1;
        else
            frame=7;
        this->update();
    }
    if(nap==2)
    {
        if(frame<7)
            frame+=1;
        else
            frame=0;
        this->update();
    }
}

void Tank::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->skin==1)
    {
        if(frame==0) {painter->drawPixmap(-33,-39, *spriteImage, 93,  1, 65, 78);}
        if(frame==1) {painter->drawPixmap(-33,-39, *spriteImage, 177, 1, 65, 78);}
        if(frame==2) {painter->drawPixmap(-33,-39, *spriteImage, 261, 1, 65, 78);}
        if(frame==3) {painter->drawPixmap(-33,-39, *spriteImage, 345, 1, 65, 78);}
        if(frame==4) {painter->drawPixmap(-33,-39, *spriteImage, 429, 1, 65, 78);}
        if(frame==5) {painter->drawPixmap(-33,-39, *spriteImage, 513, 1, 65, 78);}
        if(frame==6) {painter->drawPixmap(-33,-39, *spriteImage, 597, 1, 65, 78);}
        if(frame==7) {painter->drawPixmap(-33,-39, *spriteImage, 9,  86, 65, 78);}
    }

    if(this->skin==2)
    {
        if(frame==0) {painter->drawPixmap(-33,-39, *spriteImage, 94,  86, 66, 77);}
        if(frame==1) {painter->drawPixmap(-33,-39, *spriteImage, 178, 86, 66, 77);}
        if(frame==2) {painter->drawPixmap(-33,-39, *spriteImage, 262, 86, 66, 77);}
        if(frame==3) {painter->drawPixmap(-33,-39, *spriteImage, 346, 86, 66, 77);}
        if(frame==4) {painter->drawPixmap(-33,-39, *spriteImage, 430, 86, 66, 77);}
        if(frame==5) {painter->drawPixmap(-33,-39, *spriteImage, 514, 86, 66, 77);}
        if(frame==6) {painter->drawPixmap(-33,-39, *spriteImage, 598, 86, 66, 77);}
        if(frame==7) {painter->drawPixmap(-33,-39, *spriteImage, 10, 170, 66, 77);}
    }

    if(nap==1)this->setPos(mapToParent(0,-0.03));
    if(nap==2)this->setPos(mapToParent(0,0.03));

    if(this->x() - 10 < 30)
    {
        this->setX(40);       // left
    }
    if(this->x() + 10 > 740){
        this->setX(730);        // right
    }

    if(this->y() - 10 < 30){
        this->setY(40);       // top
    }
    if(this->y() + 10 > 740){
        this->setY(730);        // bottom
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Tank::goUP()
{
    nap=1;
}

void Tank::goDOWN()
{
    nap=2;
}

void Tank::STOP()
{
    nap=0;
}

void Tank::turnLEFT()
{
    if(angle>0)
        angle-=4;
    else
        angle=360;

    this->setRotation(angle);
}

void Tank::turnRIGHT()
{
    if(angle<360)

        angle+=4;
    else
        angle=0;

    this->setRotation(angle);
}

int Tank::getANGLE()
{
    return angle;
}
