#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphicsscene.h"
#include <QtGui>
#include <QMessageBox>
#include <QGraphicsItem>
#include "graphicsparticle.h"
#include "ngraph.hpp"
#include "pso.h"
#include <boost/foreach.hpp>
#include <graphicsedge.h>
#include "graphcoloringobjfun.h"

using namespace std;
using namespace NGraph;

Graph graph;
extern QHash<Color, double> colorCost;
extern QMap<double, Color> costColor;

namespace {



}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QActionGroup* toolGroup = new QActionGroup(this);
    toolGroup->addAction(ui->actionInsertEdge);
    toolGroup->addAction(ui->actionInsertVertex);
    toolGroup->addAction(ui->actionPointer);
    toolGroup->setExclusive(true);

    graphicsScene = new GraphicsScene(&graph, this);
    emit ui->actionPointer->trigger();
    ui->graphicsView->setScene(graphicsScene);
    graphicsScene->setSceneRect(0,0,500,500);
    bestCostText = graphicsScene->addSimpleText("0");
    bestCostText->setPos(10,10);

    //connect(graphicsScene, SIGNAL(Inserted(QGraphicsEllipseItem*)), SLOT(addVertex(QGraphicsEllipseItem*)));
    connect(graphicsScene, SIGNAL(EdgeInserted(GraphicsEdge*)), SLOT(addEdge(GraphicsEdge*)));

    srand(time(NULL));

    // Color Cost
    colorCost[RED] = 10;
    costColor[colorCost[RED]] = RED;
    colorCost[BLUE] = 20;
    costColor[colorCost[BLUE]] = BLUE;
    colorCost[GREEN] = 30;
    costColor[colorCost[GREEN]] = GREEN;
    colorCost[YELLOW] =40;
    costColor[colorCost[YELLOW]] = YELLOW;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRunSimulation_triggered()
{
    QHash<unsigned int, QGraphicsEllipseItem*> indexToVertex;
    QHash<QGraphicsItem*, unsigned int> vertexToIndex;

    unsigned int i = 0;
    foreach(GraphicsEdge* edge, edges_){
        if (vertexToIndex.find(edge->startItem()) == vertexToIndex.end()) {
            indexToVertex[i] = edge->startItem();
            vertexToIndex[edge->startItem()] = i++;
        }
        if (vertexToIndex.find(edge->endItem()) == vertexToIndex.end()) {
            indexToVertex[i] = edge->endItem();
            vertexToIndex[edge->endItem()] = i++;
        }
        graph.insert_edge(vertexToIndex[edge->startItem()], vertexToIndex[edge->endItem()]);
    }
    Bound posBound(arma::zeros(vertexToIndex.size()), arma::ones(vertexToIndex.size()));
    Bound velBound(arma::zeros(vertexToIndex.size()), 0.1*arma::ones(vertexToIndex.size()));

    Swarm swarm;
    const int maxGen = 2000;

    swarm.populationSize = 50;
    swarm.maxVelocity = 1.0;
    swarm.c1 = 1.20;
    swarm.c2 = 1.20;
    swarm.positionBound = posBound;
    swarm.velocityBound = velBound;
    swarm.objFun_ = std::auto_ptr<ObjectiveFunction>(new graphColoringObjFun);
    swarm.setup();
    for (int i = 0; i < maxGen; i++) {
        swarm.advance();
        cout << " > gen "<< i + 1 << ", fitness = " << swarm.globalBest->cost << endl;
        findGlobalBest(swarm.population, swarm.globalBest.get());
        cout << "position 0: " << endl;
        cout << (arma::sort_index(swarm.population[0]->position))  << endl;
        cout << (swarm.population[0]->cost) << endl;
    }

    bestCostText->setText(QString("Optimal Cost : %1").arg(swarm.globalBest->cost));

    VertexToColor indexToColor;
    getColorMapping(indexToColor, swarm.globalBest->position);
    QHashIterator<Graph::vertex, Color> p(indexToColor);
    while(p.hasNext()) {
        p.next();
        switch (p.value()) {
        case RED:
            indexToVertex[p.key()]->setBrush(Qt::red);
            break;
        case BLUE:
            indexToVertex[p.key()]->setBrush(Qt::blue);
            break;
        case GREEN:
            indexToVertex[p.key()]->setBrush(Qt::green);
            break;
        case YELLOW:
            indexToVertex[p.key()]->setBrush(Qt::yellow);
            break;
        default:
            ;
        }
    }
}

void MainWindow::addVertex(QGraphicsEllipseItem * item)
{
    //ndexToVertex_[
}

void MainWindow::addEdge(GraphicsEdge* edge)
{
    edges_.append(edge);
}

void MainWindow::on_actionInsertEdge_triggered()
{
    graphicsScene->mode = GraphicsScene::InsertEdge;
}

void MainWindow::on_actionInsertVertex_triggered()
{
    graphicsScene->mode = GraphicsScene::InsertVertex;
}

void MainWindow::on_actionPointer_triggered()
{
    graphicsScene->mode = GraphicsScene::Move;
}
