/*
 * main.cpp
 *
 *  Created on: May 9, 2011
 *      Author: ardfard
 */

#include "Code.h"
#include "RandBipartiteGraph.h"
#include <iostream>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>
#include <ctime>

#define foreach BOOST_FOREACH

void print(vector<bool> &b)
{
	vector<bool>::iterator it;
		for(it = b.begin(); it != b.end(); it++)
			cout<<*it;
		cout<<endl;
}

bool (IsCodeCorrect(vector<bool>& b))
{
	vector<bool>::iterator it;
	for (it = b.begin(); it != b.end(); it++){
		if(*it){
			return false;
		}
	}
	return true;
}

unsigned int Distance(vector<bool>& b)
{
	unsigned int sum = 0;
	for (unsigned int i = 0 ; i < b.size(); i++){
		sum += b[i];
	}
	return sum;
}

int main()
{
	int codeLen = 4000;
	boost::mt19937 gen;
	gen.seed(time(NULL));
	Code code(codeLen);
	code.st.assign(codeLen,0);
	boost::uniform_int<> randomInt(0,codeLen-1);
	boost::variate_generator<boost::mt19937, boost::uniform_int<> > rand(gen,randomInt);
	unsigned int iter = 10;
	do{
		cout<<iter<<endl;
		iter++;
		for(unsigned int i = 0; i < iter ; i++){
			code.st[rand()] = true;
		}
		code.CorrectError();
	}while(IsCodeCorrect(code.st));
	cout<<"Distance : "<<Distance(code.st)<<endl;

	return 0;
}

