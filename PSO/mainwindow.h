#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

class GraphicsScene;
class Particle;
class QGraphicsEllipseItem;
class QGraphicsSimpleTextItem;
class GraphicsEdge;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GraphicsScene *graphicsScene;

private slots:
    void on_actionRunSimulation_triggered();
    void on_actionPointer_triggered();
    void on_actionInsertVertex_triggered();
    void on_actionInsertEdge_triggered();
    void addVertex(QGraphicsEllipseItem*);
    void addEdge(GraphicsEdge* edge);


private:
    QGraphicsSimpleTextItem* bestCostText;

    QList<GraphicsEdge*> edges_;
};

#endif // MAINWINDOW_H
