#include "card.h"

Card::Card()
{
    CreatePlane();
}
//игровое поле
int pole[19][19]=
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,
    1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,
    1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,
    1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,
    1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,
    1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
    1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

void Card::CreatePlane()
{
    //size pixel
    int ww = 40;
    int hh = 40;


    //make plane Vector
    for(int i=0;i<19;i++)
    {
        for(int q=0;q<19;q++)
        {
            QVector<int> pos;
            pos.push_back(ww*q);
            pos.push_back(hh*i);
            if(pole[i][q]==1)pix.push_back(pos);
        }
    }
    //qDebug()<<pix;
}

QVector<Block*> Card::getBlock()
{
    QVector <Block*> bbb;
    for(QVector<int>tmp : pix)
    {
        Block *bl = new Block(40,40);
        bl->setPos(tmp[0],tmp[1]);
        bbb.append(bl);
    }
    return bbb;
}