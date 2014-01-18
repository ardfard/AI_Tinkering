#include "graphcoloringobjfun.h"
#include <boost/foreach.hpp>
#include <QMap>
#include <QHash>

using namespace NGraph;

extern Graph graph;

QHash<Color, double> colorCost;
QMap<double, Color> costColor;

Graph::vertex_set getNeighbor(Graph::vertex v)
{
        Graph::vertex_set in = graph.in_neighbors(v);
        Graph::vertex_set out = graph.out_neighbors(v);
        in.insert(out.begin(), out.end());

        return in;
}

int getColorMapping(VertexToColor& vertexToColor, Vector values)
{
    for (Graph::iterator it = graph.begin(); it != graph.end(); it++) {
            vertexToColor[graph.node(it)] = NONE;
    }
    arma::umat idx = arma::sort_index(values);
    double totalCost = 0;
    BOOST_FOREACH(arma::uword i, idx){
        Graph::vertex v = (unsigned int) i;
        Graph::vertex_set n = getNeighbor(v);
        QMapIterator<double, Color> it(costColor);
        while(it.hasNext()) {
            it.next();
            Color c = it.value();
            bool colorTaken = false;
            BOOST_FOREACH(Graph::vertex vn, n) {
                    if (vertexToColor[vn] == c) {
                            colorTaken = true;
                            break;
                    }
            }
            if (!colorTaken) {
                    vertexToColor[v] = c;
                    totalCost += it.key();
                    break;
            }
        }
    }
    return totalCost;
}

double graphColoringObjFun::call(Vector values)
{
    VertexToColor vertexToColor;

    return getColorMapping(vertexToColor, values);
}

graphColoringObjFun::graphColoringObjFun()
{
}

