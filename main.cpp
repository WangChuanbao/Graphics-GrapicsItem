#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QTime>
#include <QTimer>
#include "myitem.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    /**
     * qt提供的图形视图框架，图形视图主要分为三部分：
     * 1.场景（scene）：QGraphicsScene
     * 2.图形项（item）：QGraphicsItem
     * 3.视图（view）：QGraphicsView
     */

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    QGraphicsScene *scene = new QGraphicsScene;
    //QGraphicsRectItem *item = new  QGraphicsRectItem(0,0,30,30);
    for(int i=0;i<5;i++)
    {
        MyItem *item = new MyItem;
        item->setPos(i*50+20,100);
        scene->addItem(item);
        qDebug() << item->shape() << endl;
        qDebug() << item->boundingRect() << endl;
    }
    QGraphicsLineItem *line = new QGraphicsLineItem(0,50,300,50);
    scene->addItem(line);
    RectItem *rect = new RectItem;
    rect->setPos(100,200);
    scene->addItem(rect);
    QGraphicsView *view = new QGraphicsView;
    view->setScene(scene);
    view->resize(400,300);
    view->show();

    //QTimer timer;
    //调用QGraphicsScene类中的advance函数，这样图形项中会调用两次该函数
    //QObject::connect(&timer,SIGNAL(timeout()),scene,SLOT(advance()));
    //timer.start(1000);

    return a.exec();
}
