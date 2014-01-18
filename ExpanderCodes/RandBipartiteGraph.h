/*
 * Graph.h
 *
 *  Created on: 27 Apr 2011
 *      Author: voyager
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <map>
#include <string>

using namespace std;

class Vertex
{
public:
    unsigned int name;
    vector<Vertex* > adj;
    Vertex(unsigned int nm):name(nm){}
};

class Variable : public Vertex
{
public:
	unsigned int nousc;
	Variable(unsigned int nm):Vertex(nm){}
};

class Constraint : public Vertex
{
public:
	bool isSatisfied;
	Constraint(unsigned int nm):Vertex(nm){}
};

class RandBipartiteGraph
{
	typedef map<unsigned int, Variable*> vmap;
	typedef map<unsigned int, Constraint*> cmap;
public:
    RandBipartiteGraph(unsigned int _c, unsigned int _d, unsigned int _n);
    ~RandBipartiteGraph();
    void GenerateGraph();
    unsigned int GetRightVerticesNumber(){return c*n/d;}
    vmap variables;
    cmap constraints;

private:


    unsigned int c; // left degree
    unsigned int d; // right degree
    unsigned int n; // number of left vertices
    RandBipartiteGraph(const RandBipartiteGraph & rhs){}
    const RandBipartiteGraph & operator= (const RandBipartiteGraph & rhs)
    {return *this;}
    void AddEdge(Vertex *pLeftVertex, Vertex *pRightVertex);
    Variable* AddVariable(unsigned int name);
    Constraint* AddConstraint(unsigned int name);
    Vertex* GetRandRightVertex(vector<Vertex*> &listv);
};

#endif /* GRAPH_H_ */
