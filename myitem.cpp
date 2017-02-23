#include "myitem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QWidget>
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QPixmap>
#include <QVariant>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QDebug>

MyItem::MyItem()
{
    setToolTip("click and drag me!");
    setCursor(Qt::OpenHandCursor);

    //图形项接受键盘事件，必须设置其可获得焦点
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsMovable);  //设置图形项可拖动

    //1.创建图形项动画类
    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    //2.将该图形项加入到图形项动画类中
    animation->setItem(this);
    //3.创建时间长为1秒的时间线
    QTimeLine *timeLine = new QTimeLine(3000);
    //4.将时间线加入到图形项动画类中
    animation->setTimeLine(timeLine);
    animation->setRotationAt(0.5,180);  //在动画时间的一半时，图形项旋转180度。以左上定点为中心旋转
    animation->setRotationAt(1,360);    //在动画执行完成时，图形项旋转360度
    timeLine->start();

    color = QColor(qrand()%256,qrand()%256,qrand()%256);
}

MyItem::~MyItem()
{

}

QRectF MyItem::boundingRect() const
{
    return QRectF(0,0,50,50);
}
/**
 * @brief MyItem::paint
 * @param painter
 * @param option
 * @param widget
 */
void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    //painter->setBrush(color);
    /**
     * QGraphicsItem类中提供了三个监测碰撞的函数
     * 1.collidesWithItem()：监测该图形项是否与指定的图形项碰撞
     * 2.collidesWithPath()：该图形项是否与指定的路径碰撞
     * 3.collidingItems()：返回所有与该图形项碰撞的图形项的列表
     *
     * 这三个函数有一个共同的参数Qt::ItemSelectionMode，指明监测碰撞方式。它是枚举变量，有四个值：
     * 1.Qt::ContainsItemShape：只有图形项的shape被完全包含时
     * 2.Qt::IntersectsItemShape：默认值，图形项的shape被完全包含时或者图形项与其边界相交
     * 3.Qt::ContainsItemBoundingRect：只有图形项的bounding rectangle被完全包含时
     * 4.Qt::IntersectsItemBoundingRect：图形项bounding rectangle被完全包含或图形项与其边界相交
     */
    painter->setBrush(!collidingItems().isEmpty()?Qt::red:Qt::green);
    painter->drawEllipse(0,10,20,20);
}


/**
 * @brief MyItem::advance
 * @param phase
 * 调用QGraphicsScene类中的advance函数，图形项中会调用两次。
 * 第一次返回0，代表图形项将要移动。
 * 第二次返回1，代表图形项移动
 */
void MyItem::advance(int phase)
{
    if (!phase) return;
    moveBy(0,10);
}

void MyItem::move()
{
    qDebug() << "============" << endl;
    setPos(0,0);
}

void MyItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
        //setCursor(Qt::ClosedHandCursor);
        moveBy(10,0);
}
/*
void MyItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    if(QLineF(event->screenPos(),event->buttonDownScreenPos(Qt::LeftButton)).length()<QApplication::startDragDistance())
//        return;

//    QDrag *drag = new QDrag(event->widget());
//    QMimeData *mimeData = new QMimeData;  //用于存放拖动对象的数据
//    mimeData->setColorData(color);
//    drag->setMimeData(mimeData);

//    QPixmap pix(21,21);
//    pix.fill(Qt::white);
//    QPainter painter(&pix);
//    paint(&painter,0,0);
//    drag->setPixmap(pix);
//    drag->setHotSpot(QPoint(10,15));
//    drag->exec();
//    setCursor(Qt::OpenHandCursor);
}

void MyItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
   // setCursor(Qt::OpenHandCursor);
}
*/
void MyItem::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
    moveBy(0,10);
}

void MyItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *action = menu.addAction("moveTo(0,0)");
    connect(action,SIGNAL(triggered()),this,SLOT(move()));
    menu.exec(event->screenPos());  //在按下鼠标左键的地方弹出菜单
}



RectItem::RectItem()
{
    setAcceptDrops(true);   //接受拖入事件
    color = QColor(Qt::lightGray);

    setFlag(QGraphicsItem::ItemIsFocusable);    //获取焦点
    setFlag(QGraphicsItem::ItemIsMovable);  //可移动

    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    animation->setItem(this);
    QTimeLine *timeLine = new QTimeLine(3000);
    animation->setTimeLine(timeLine);
    animation->setRotationAt(0.5,180);
    animation->setRotationAt(1,360);
    timeLine->start();
}

RectItem::~RectItem()
{

}

QRectF RectItem::boundingRect() const
{
    return QRectF(0,0,50,50);
}

void RectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(dragOver?color.light(130):color);
    painter->drawRect(0,0,50,50);
}

void RectItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if(event->mimeData()->hasColor())
    {
        event->setAccepted(true);
        dragOver = true;
        update();
    }
    else event->setAccepted(false);
}

void RectItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    dragOver = false;
    update();
}

void RectItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    dragOver = false;
    if(event->mimeData()->hasColor())
        color = event->mimeData()->colorData().value<QColor>();
    update();
}
