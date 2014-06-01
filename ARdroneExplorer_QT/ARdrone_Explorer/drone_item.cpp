#include "drone_item.h"

Drone_item::Drone_item()
{
}

QRectF Drone_item::boundingRect() const
{
    return QRect(0,0,2,2);
}

void Drone_item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);

    painter->fillRect(rec,brush);
    painter->drawRect(rec);
}

void Drone_item::advance(int phase)
{
    if(!phase) return;
//    QPointF location = this->pos();

//    setPos(posX, posY);
}

void Drone_item::newValue(int x, int y)
{
    posX = x;
    posY = y;
    QPointF location = this->pos();

    setPos(posX, posY);
}
