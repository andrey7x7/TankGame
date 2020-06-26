#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QtMath>

class Bullet : public QObject , public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Bullet(QPointF point, int angle=0, int tank=0, QObject *parent = nullptr);

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPixmap *spriteImage;         // В данный объект QPixamp будет помещён спрайт
    QTimer *timer_go;             // Таймер для движения изображения
    int skin=1;

private slots:
    void goTARGET();
    void BOOM();
};

#endif // BULLET_H
