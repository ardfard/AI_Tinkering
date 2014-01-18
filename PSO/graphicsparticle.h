#ifndef GRAPHICSPARTICLE_H
#define GRAPHICSPARTICLE_H

#include <QGraphicsEllipseItem>
#include "pso.h"

class GraphicsParticle : public QGraphicsEllipseItem, public Particle
{
public:
    explicit GraphicsParticle(Swarm* swarm);
    void updateScenePosition();
    void advance(int phase);

private:
    Bound posBound_;

};

#endif // GRAPHICSPARTICLE_H
