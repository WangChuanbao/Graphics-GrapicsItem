#ifndef MYITEM_H
#define MYITEM_H
#include <QGraphicsItem>

class MyItem : public QObject, public QGraphicsItem  //多重继承
{
    Q_OBJECT

public:
    MyItem();
    ~MyItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);    //图形项移动的原型函数

private slots:
    void move();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    QColor color;
};

class RectItem : public QGraphicsItem
{
public:
    RectItem();
    ~RectItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

private:
    QColor color;
    bool dragOver;
};

#endif // MYITEM_H
