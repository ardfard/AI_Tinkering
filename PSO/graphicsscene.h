#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <ngraph.hpp>

class QGraphicsEllipseItem;
class GraphicsEdge;

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(NGraph::Graph* graph, QObject *parent = 0);
    enum Mode{InsertVertex, InsertEdge, Move} mode;

signals:
    void vertexInserted(QGraphicsEllipseItem* item);
    void EdgeInserted(GraphicsEdge* item);

public slots:

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    NGraph::Graph* graph_;
    QGraphicsLineItem* line;

};

#endif // GRAPHICSSCENE_H
