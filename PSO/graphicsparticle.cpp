#include "graphicsparticle.h"
#include <QGraphicsScene>

GraphicsParticle::GraphicsParticle(Swarm* swarm)
    : Particle(swarm), posBound_(swarm->positionBound)
{
    setRect(0,0,5,5);
    setBrush(Qt::blue);
}

void GraphicsParticle::updateScenePosition()
{
}

void GraphicsParticle::advance(int phase)
{
    if(phase == 1){
        QRectF rect = scene()->sceneRect();
        double w = rect.width();
        double h = rect.height();
        qreal posx = 0;
        qreal posy = 0;
        posx = (position[0] - posBound_.minVec[0])*w/(posBound_.maxVec[0] -posBound_.minVec[0]);
        posy = (position[1] - posBound_.minVec[1])*h/(posBound_.maxVec[1] - posBound_.minVec[1]);

        setPos(posx, posy);
    }

}
