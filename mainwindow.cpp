#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game_1 = new TankGame(this);
    ui->gridLayout->addWidget(game_1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    game_1->keyPress(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    game_1->keyRelease(event);
}
