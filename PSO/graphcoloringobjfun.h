#ifndef GRAPHCOLORINGOBJFUN_H
#define GRAPHCOLORINGOBJFUN_H

#include "objectivefunction.h"
#include <ngraph.hpp>
#include <QHash>

class Particle;

typedef arma::vec Vector;
enum Color{NONE, RED, BLUE, GREEN, YELLOW, COLOR_NUM};
typedef QHash<NGraph::Graph::vertex, Color> VertexToColor;

int getColorMapping(VertexToColor& vertexToColor, Vector values);


class graphColoringObjFun : public ObjectiveFunction
{
public:
    graphColoringObjFun();
    virtual double call(Vector values);
};

#endif // GRAPHCOLORINGOBJFUN_H
