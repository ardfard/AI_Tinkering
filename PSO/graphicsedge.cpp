#include "graphicsedge.h"
#include <QtGui>

GraphicsEdge::GraphicsEdge(QGraphicsEllipseItem* startItem, QGraphicsEllipseItem* endItem)
{
    myStartItem = startItem;
    myEndItem = endItem;
    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF GraphicsEdge::boundingRect() const
 {
     qreal extra = (pen().width() + 20) / 2.0;

     return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                       line().p2().y() - line().p1().y()))
         .normalized()
         .adjusted(-extra, -extra, extra, extra);
 }

 QPainterPath GraphicsEdge::shape() const
 {
     QPainterPath path = QGraphicsLineItem::shape();
     return path;
 }

 void GraphicsEdge::updatePosition()
 {
     QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
     setLine(line);
 }

 void GraphicsEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
           QWidget *)
 {
     if (myStartItem->collidesWithItem(myEndItem))
         return;

     QPen myPen = pen();
     painter->setPen(myPen);
     painter->setBrush(Qt::black);
     painter->setRenderHint(QPainter::Antialiasing);


     setLine(QLineF(myEndItem->pos(), myStartItem->pos()));

     painter->drawLine(line());
 }
