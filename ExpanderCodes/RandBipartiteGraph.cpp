/*
 * RandBipartiteGraph.cpp
 *
 *  Created on: 27 Apr 2011
 *      Author: voyager
 */

#include "RandBipartiteGraph.h"
#include "stdio.h"
#include <math.h>
#include <boost/foreach.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>
#include <algorithm>
#include <list>
#include <ctime>


boost::mt19937 gen;

#define foreach BOOST_FOREACH

RandBipartiteGraph::RandBipartiteGraph(unsigned int _c, unsigned int _d,
        unsigned int _n):c(_c), d(_d), n(_n)
{
    GenerateGraph();
}

void RandBipartiteGraph::GenerateGraph()
{
    // make n left-vertices
    for(unsigned int i = 0; i < n; i++){
        AddVariable(i);
    }

    vector<Vertex*> availableVertexList;
    availableVertexList.reserve(n);
    gen.seed(time(NULL));

    if (c%d != 0){
    // make c/d n right-vertices
        for(unsigned int i = 0; i < GetRightVerticesNumber(); i++){
            availableVertexList.push_back(static_cast<Vertex*>(AddConstraint(i)));
        }
    }

    for (unsigned int i = 0; i < n; i++){
        for(unsigned int j = 0; j < c; j++){
        	AddEdge(static_cast<Vertex*>(variables[i]), GetRandRightVertex(availableVertexList));
        }
    }
}

void RandBipartiteGraph::AddEdge(Vertex *pLeftVertex, Vertex *pRightVertex)
{
	pLeftVertex->adj.push_back(pRightVertex);
	pRightVertex->adj.push_back(pLeftVertex);
}

Variable* RandBipartiteGraph::AddVariable(unsigned int name)
{
    Variable *var = new Variable(name);
    variables[name] = var;
    return var;
}

Constraint* RandBipartiteGraph::AddConstraint(unsigned int name)
{
	Constraint *con = new Constraint(name);
	constraints[name] = con;
	return con;
}

Vertex* RandBipartiteGraph::GetRandRightVertex(vector<Vertex* > &listv)
{
	if(!listv.empty()){
		boost::uniform_int<> random(0,static_cast<int>(listv.size()-1));
		boost::variate_generator<boost::mt19937&, boost::uniform_int<> > randVertex(gen,random);
		Vertex* pVertex = listv[static_cast<unsigned int>(randVertex())];
		if(pVertex->adj.size() >= d-1){
			listv.erase(find(listv.begin(), listv.end(), pVertex));
		}
		return pVertex;
	}else{
		return NULL;
	}
}

RandBipartiteGraph::~RandBipartiteGraph()
{
	std::pair<unsigned int, Variable*> itv;
	std::pair<unsigned int, Constraint*> itc;
	foreach(itv, variables){
		delete itv.second;
	}
	foreach(itc, constraints){
		delete itc.second;
	}
}
