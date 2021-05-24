#ifndef RULECLASS_H
#define RULECLASS_H
#pragma once

#include "token.h"
#include "predicateClass.h"

#include<list>

class ruleClass {
	public:
	void addPredicate(predicateClass add);
	void clear();
	void getRule();
	std::string toString();
	predicateClass getPredicate(const int& i);
	int getNumPredicates();
	private:
	vector<predicateClass> ruleVec; //stores 3 predicateClass things as one RULE;
};

#endif