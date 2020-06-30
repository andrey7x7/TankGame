#include "tankgame.h"
#include "ui_tankgame.h"

TankGame::TankGame(QWidget *parent,bool server) :
    QWidget(parent),
    ui(new Ui::TankGame)
{
    ui->setupUi(this);
    this->server_mode=server;
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,ui->graphicsView->width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);

     ui->graphicsView->setStyleSheet("background-color: rgb(198, 198, 0)");

    tank_1 = new Tank(this,1);
    scene->addItem(tank_1);
    tank_1->setPos(450,450);

    tank_2 = new Tank(this,2);
    scene->addItem(tank_2);
    tank_2->setPos(300,300);

    connect(&timer_colides,SIGNAL(timeout()),this,SLOT(search_Collides()));
    timer_colides.start(25);

    scene->addItem(new Block(40,40));

    card_1 = new Card();
    for(QGraphicsItem *item : card_1->getBlock())
    {
        scene->addItem(item);
    }

    if(server)
    {
        connect(&timer_sinc,SIGNAL(timeout()),this,SLOT(SincClient()));
        timer_sinc.start(500);
    }
}

TankGame::~TankGame()
{
    delete ui;
}

void TankGame::keyPress(QKeyEvent *event)
{
    emit on_keyPress(event->key());
    gaz=true;

    if(server_mode)
    {
        //Tank 1
        if (event->key()==Qt::Key_Up)
        {
            tank_1->goUP();
        }

        if (event->key()==Qt::Key_Down)
        {
            tank_1->goDOWN();
        }

        if (event->key()==Qt::Key_Left)
        {
            tank_1->turnLEFT();
        }

        if (event->key()==Qt::Key_Right)
        {
            tank_1->turnRIGHT();
        }

        if (event->key()==Qt::Key_Space)
        {
            scene->addItem(new Bullet(tank_1->pos(),tank_1->getANGLE(),1));
        }

        //Tank 2
        if (event->key()==Qt::Key_W)
        {
            tank_2->goUP();
        }
        if (event->key()==Qt::Key_S)
        {
            tank_2->goDOWN();
        }
        if (event->key()==Qt::Key_A)
        {
            tank_2->turnLEFT();
        }
        if (event->key()==Qt::Key_D)
        {
            tank_2->turnRIGHT();
        }
        if (event->key()==Qt::Key_E)
        {
            scene->addItem(new Bullet(tank_2->pos(),tank_2->getANGLE(),2));
        }
    }
    else
    {
        //Tank 1
        if (event->key()==Qt::Key_Up)
        {
            tank_2->goUP();
        }

        if (event->key()==Qt::Key_Down)
        {
            tank_2->goDOWN();
        }

        if (event->key()==Qt::Key_Left)
        {
            tank_2->turnLEFT();
        }

        if (event->key()==Qt::Key_Right)
        {
            tank_2->turnRIGHT();
        }

        if (event->key()==Qt::Key_Space)
        {
            scene->addItem(new Bullet(tank_2->pos(),tank_2->getANGLE(),2));
        }
    }

}

void TankGame::keyRelease(QKeyEvent *event)
{
    if(server_mode)
    {
        if (event->key()==Qt::Key_Up || event->key()==Qt::Key_Down)
        {
            tank_1->STOP();

            gaz=false;
            QTimer::singleShot(5,this,SLOT(keyStop()));
        }

        if (event->key()==Qt::Key_W || event->key()==Qt::Key_S)
        {
            tank_2->STOP();
        }
    }
    else
    {
        if (event->key()==Qt::Key_Up || event->key()==Qt::Key_Down)
        {
            tank_2->STOP();

            gaz=false;
            QTimer::singleShot(5,this,SLOT(keyStop()));
        }

        if (event->key()==Qt::Key_W || event->key()==Qt::Key_S)
        {
            tank_1->STOP();
        }
    }
}

void TankGame::keyStop()
{
    if(!gaz)
        emit on_keyPress(127);
}

void TankGame::search_Collides()
{
    scene->update(ui->graphicsView->rect());

    QList <QGraphicsItem * > list = scene->items();

    for(QGraphicsItem *item : scene->items())
    {
        //Попадание пули в блок
        if(item->data(0).toString()=="BULLET")
        {
            for(QGraphicsItem *ttt : item->collidingItems())
            {
                if(ttt->data(0).toString()=="BLOCK")
                {
                    item->setData(1,false);
                }
                //Если попали в пулю, а не в разрыв
                if(ttt->data(0).toString()=="BULLET" && ttt->data(1).toBool() && item->data(1).toBool())
                {
                    item->setData(1,false);
                    ttt->setData(1,false);
                }
            }
        }

        //Попадание в танк
        if(tank_1->collidesWithItem(item) && item->data(0).toString()=="BULLET")
        {
            //Проверяем пулю (живая - не своя)
            if(item->data(1).toBool() && item->data(2).toInt()!=1)
            {
                tank_1->onDamage();
                item->setData(1,false);
            }
        }
        if(tank_2->collidesWithItem(item) && item->data(0).toString()=="BULLET")
        {
            //Проверяем пулю (живая - не своя)
            if(item->data(1).toBool() && item->data(2).toInt()!=2)
            {
                tank_2->onDamage();
                item->setData(1,false);
            }
        }

        //Столкновение танка с блоком
        if(tank_1->collidesWithItem(item) && item->data(0).toString()=="BLOCK")
        {
            if(tank_1->x() < item->x())
            {
                tank_1->setX(tank_1->x()-1);       // left
                tank_1->STOP();
            }
            if(tank_1->x() > item->x())
            {
                tank_1->setX(tank_1->x()+1);       // right
                tank_1->STOP();
            }
            if(tank_1->y() < item->y())
            {
                tank_1->setY(tank_1->y()-1);       // top
                tank_1->STOP();
            }
            if(tank_1->y() > item->y())
            {
                tank_1->setY(tank_1->y()+1);       // bottom
                tank_1->STOP();
            }
        }
        if(tank_2->collidesWithItem(item) && item->data(0).toString()=="BLOCK")
        {
            if(tank_2->x() < item->x())
            {
                tank_2->setX(tank_2->x()-1);       // left
                tank_2->STOP();
            }
            if(tank_2->x() > item->x())
            {
                tank_2->setX(tank_2->x()+1);       // right
                tank_2->STOP();
            }
            if(tank_2->y() < item->y())
            {
                tank_2->setY(tank_2->y()-1);       // top
                tank_2->STOP();
            }
            if(tank_2->y() > item->y())
            {
                tank_2->setY(tank_2->y()+1);       // bottom
                tank_2->STOP();
            }
        }
    }

    //Столкновение танка с танком
    if(tank_1->collidesWithItem(tank_2))
    {
        if(tank_1->x() < tank_2->x())
        {
            tank_1->setX(tank_1->x()-1);       // left
            tank_1->STOP();
        }
        if(tank_1->x() > tank_2->x())
        {
            tank_1->setX(tank_1->x()+1);       // right
            tank_1->STOP();
        }
        if(tank_1->y() < tank_2->y())
        {
            tank_1->setY(tank_1->y()-1);       // top
            tank_1->STOP();
        }
        if(tank_1->y() > tank_2->y())
        {
            tank_1->setY(tank_1->y()+1);       // bottom
            tank_1->STOP();
        }
    }
    if(tank_2->collidesWithItem(tank_1))
    {
        if(tank_2->x() < tank_1->x())
        {
            tank_2->setX(tank_2->x()-1);       // left
            tank_2->STOP();
        }
        if(tank_2->x() > tank_1->x())
        {
            tank_2->setX(tank_2->x()+1);       // right
            tank_2->STOP();
        }
        if(tank_2->y() < tank_1->y())
        {
            tank_2->setY(tank_2->y()-1);       // top
            tank_2->STOP();
        }
        if(tank_2->y() > tank_1->y())
        {
            tank_2->setY(tank_2->y()+1);       // bottom
            tank_2->STOP();
        }
    }

    ui->progressBar_t1->setValue(tank_1->getHealth());
    ui->progressBar_t2->setValue(tank_2->getHealth());
}

void TankGame::LanRead(int key)
{
    if(server_mode)
    {
        //Tank 2
        if (key==Qt::Key_Up)
        {
            tank_2->goUP();
        }

        if (key==Qt::Key_Down)
        {
            tank_2->goDOWN();
        }

        if (key==Qt::Key_Left)
        {
            tank_2->turnLEFT();
        }

        if (key==Qt::Key_Right)
        {
            tank_2->turnRIGHT();
        }

        if (key==127)
        {
            tank_2->STOP();
        }

        if (key==Qt::Key_Space)
        {
            scene->addItem(new Bullet(tank_2->pos(),tank_2->getANGLE(),2));
        }
    }
    else
    {
        //Tank 1
        if (key==Qt::Key_Up)
        {
            tank_1->goUP();
        }

        if (key==Qt::Key_Down)
        {
            tank_1->goDOWN();
        }

        if (key==Qt::Key_Left)
        {
            tank_1->turnLEFT();
        }

        if (key==Qt::Key_Right)
        {
            tank_1->turnRIGHT();
        }

        if (key==127)
        {
            tank_1->STOP();
        }

        if (key==Qt::Key_Space)
        {
            scene->addItem(new Bullet(tank_1->pos(),tank_1->getANGLE(),1));
        }

    }
}

void TankGame::SincClient()
{
    This_position * pos = new This_position(QPoint(tank_1->pos().x(),tank_1->pos().y()),QPoint(tank_2->pos().x(),tank_2->pos().y()));
    emit getPositions(pos);
}

void TankGame::SincPlane(This_position pos)
{
    qDebug()<<"Sinc Point";
    tank_1->setX(pos.get_t1().x());
    tank_1->setY(pos.get_t1().y());
    tank_2->setX(pos.get_t2().x());
    tank_2->setY(pos.get_t2().y());
}
