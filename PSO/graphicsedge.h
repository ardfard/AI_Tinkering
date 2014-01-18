#ifndef GRAPHICSEDGE_H
#define GRAPHICSEDGE_H

#include <QGraphicsLineItem>

class GraphicsEdge : public QGraphicsLineItem
{
public:
    enum {Type = UserType + 1};
    GraphicsEdge(QGraphicsEllipseItem* startItem, QGraphicsEllipseItem* endItem);

    int type() const
    { return Type; }
    QRectF boundingRect() const;
    QPainterPath shape() const;
    QGraphicsEllipseItem *startItem() const
    { return myStartItem; }
    QGraphicsEllipseItem *endItem() const
    { return myEndItem; }

public slots:
    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);

private:
    QGraphicsEllipseItem *myStartItem;
    QGraphicsEllipseItem *myEndItem;
};

#endif // GRAPHICSEDGE_H
