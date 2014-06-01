#ifndef DRONE_ITEM_H
#define DRONE_ITEM_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class Drone_item : public QGraphicsItem
{
public:
    Drone_item();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
void newValue(int x, int y);
protected:
    void advance(int phase);
private:
    qreal posX;
    qreal posY;

public slots:

};

#endif // DRONE_ITEM_H
