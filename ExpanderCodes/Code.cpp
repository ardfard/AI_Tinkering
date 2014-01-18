/*
 * Code.cpp
 *
 *  Created on: May 7, 2011
 *      Author: ardfard
 */

#include "Code.h"
#include <boost/foreach.hpp>
#include <algorithm>
#include <iostream>
#include "matrix.h"

#define foreach BOOST_FOREACH

using namespace math;

#define c 5
#define d 10

Code::Code(unsigned int len):length(len),
		pGraph(new RandBipartiteGraph(c, d, length))
{
	st.reserve(length);
	Initialize();
}

void printS(SetNousc &s){
	int iter = 0;
	foreach(list<Variable*> l, s){
		cout<<"himpunan "<<iter++<<":"<<endl;
		foreach(Variable* var, l){
			cout<<var->name<<" ";
		}
		cout<<endl<<"Total : "<<l.size()<<endl;
	}
}

bool Code::CorrectError(){
	SetNousc s(c+1); // sets of vertex with i unsatisfied constraint
	std::pair<unsigned int, Variable*> itv;
	std::pair<unsigned int, Constraint*> itc;

	// check wether constraint satisfied or not
	foreach(itc, pGraph->constraints){
		UpdateConstraintStatus(itc.second);
	}

	// check how many constraint tha unsatisfied for every variable
	foreach(itv, pGraph->variables){
		UpdateVariableStatus(itv.second);
		s[itv.second->nousc].push_back(itv.second);
	}
	// find biggest non-empty set
	unsigned int i = GetBiggestNonEmptySet(s);
	while (i>c/2){
		Variable *var = s[i].front();
		st[var->name].flip();
		foreach(Vertex* cons, var->adj ){
			UpdateConstraintStatus(static_cast<Constraint*>(cons));
			foreach(Vertex *v, cons->adj){
				Variable *var = static_cast<Variable*>(v);
				s[var->nousc].erase(find(s[var->nousc].begin(),s[var->nousc].end(), var));
				UpdateVariableStatus(var);
				s[var->nousc].push_back(var);
			}
		}
		i = GetBiggestNonEmptySet(s);
	}
	if (s[0].size() == length){
		return true;
		// print code
	} else{
		return false;
		//code false
	}
}

unsigned int Code::GetBiggestNonEmptySet(SetNousc &s)
{
	for(int i = c; i>=c/2; i--){
		if(!s[i].empty()){
			return i;
		}
	}
	return 0;
}

void Code::UpdateConstraintStatus(Constraint* cons)
{
	// assume the linear codes is even code
	int sum = 0;
	foreach(Vertex* var, cons->adj){
		sum += st[var->name];
	}
	if(sum%2)
		cons->isSatisfied = false;
	else
		cons->isSatisfied = true;
}

void Code::UpdateVariableStatus(Variable *var)
{
	unsigned int sum = 0;
	foreach(Vertex* con, var->adj){
		if(!static_cast<Constraint *>(con)->isSatisfied)
			++sum;
	}
	var->nousc = sum;
}

void Code::Initialize()
{


}

Code::~Code() {
	if(pGraph!=NULL)
		delete pGraph;
}
