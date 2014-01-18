/*
 * Code.h
 *
 *  Created on: May 7, 2011
 *      Author: ardfard
 */

#ifndef CODE_H_
#define CODE_H_

#include <vector>
#include <map>
#include <list>
#include "RandBipartiteGraph.h"

typedef vector< list<Variable*> > SetNousc;

class Code{
private:
	unsigned int length;
	RandBipartiteGraph *pGraph;
	vector<Variable*> varList;
	vector<Constraint*> consList;
public:
	vector<bool> st;
	Code(unsigned int len);
	bool CorrectError();
	Code();
	virtual ~Code();
protected:
	void Initialize();
	void UpdateConstraintStatus(Constraint* cons);
	void UpdateVariableStatus(Variable* var);
	unsigned int GetBiggestNonEmptySet(SetNousc &s);
};

#endif /* CODE_H_ */
