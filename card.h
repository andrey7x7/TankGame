#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QVector>

class Block : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    int ww,hh;
    QPixmap *spriteImage;   // В данный объект QPixamp будет помещён спрайт
    Block(int ww,int hh)
    {
        spriteImage = new QPixmap(":/img/1.png");
        this->ww=ww;
        this->hh=hh;
        this->setData(0,"BLOCK");
    };
    ~Block(){qDebug()<<"del blok";};

private:
    QRectF boundingRect() const{

        return QRectF (0,0,ww,hh);
    };

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        painter->setPen(Qt::black);
        painter->setBrush(Qt::gray);

        painter->drawRect(0,0,ww,hh);
        painter->drawRect(ww/4,hh/4,ww/2,hh/2);
        //painter->drawPixmap(0,0, *spriteImage, 6, 51, 40,40);

        Q_UNUSED(option);
        Q_UNUSED(widget);
    };
};

class Card : public QObject
{
    Q_OBJECT

public:
    Card();
    QVector <QVector <int>> pix;

public slots:
    QVector<Block *> getBlock();

private slots:
    void CreatePlane();
};

#endif // CARD_H
