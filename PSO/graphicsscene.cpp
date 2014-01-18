#include "graphicsscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <graphicsvertex.h>
#include "graphicsedge.h"
#include <QDebug>

GraphicsScene::GraphicsScene(NGraph::Graph* graph, QObject *parent) :
    QGraphicsScene(parent)
{
    graph_ = graph;
    mode = Move;
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch(mode) {
    case InsertVertex:
    {
        double size = 20;
        QGraphicsEllipseItem* item = addEllipse(-size/2, - size/2, size, size);
        item->setPos(event->scenePos());
        item->setBrush(Qt::white);
        item->setFlag(QGraphicsItem::ItemIsMovable);
        item->setAcceptHoverEvents(true);
        emit vertexInserted(item);
        break;
    }
    case InsertEdge:
    {
        line = new QGraphicsLineItem(QLineF(event->scenePos(),
                                            event->scenePos()));
        line->setPen(QPen(Qt::black, 2));
        addItem(line);
        break;
    }
    default:
        ;
    }
    QGraphicsScene::mousePressEvent(event);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (mode == InsertEdge && line != 0) {
        QLineF newLine(line->line().p1(), event->scenePos());
        line->setLine(newLine);
    } else if (mode == Move) {
        QGraphicsScene::mouseMoveEvent(event);
    }
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (line != 0 && mode == InsertEdge) {
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;

        if (startItems.count() > 0 && endItems.count() > 0 &&
                startItems.first()->type() == QGraphicsEllipseItem::Type &&
                endItems.first()->type() == QGraphicsEllipseItem::Type &&
                startItems.first() != endItems.first()) {
            QGraphicsEllipseItem *startItem =
                    qgraphicsitem_cast<QGraphicsEllipseItem *>(startItems.first());
            QGraphicsEllipseItem *endItem =
                    qgraphicsitem_cast<QGraphicsEllipseItem *>(endItems.first());
            GraphicsEdge *arrow = new GraphicsEdge(startItem, endItem);
            arrow->setZValue(-1000.0);
            addItem(arrow);
            emit EdgeInserted(arrow);
            arrow->updatePosition();
        }
    }
    line = 0;
    QGraphicsScene::mouseReleaseEvent(event);
}
