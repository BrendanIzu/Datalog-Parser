#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H
#pragma once

#include "predicateClass.h"
#include "ruleClass.h"

class datalogProgram {
	public:
	void addDomain(string add);
	void listDomain();

	void addScheme(predicateClass add);
	void listSchemes();

	void addFact(predicateClass add);
	void listFacts();

	void addQuery(predicateClass add);
	void listQueries();
	int getNumQueries();
	predicateClass getQuerie(int& i);

	void addRule(ruleClass add);
	void listRules();
	int getNumRules();
	ruleClass getRule(int& i);
	
	
	vector<predicateClass>schemes;
	vector<predicateClass>facts;
	vector<predicateClass>queries;
	vector<ruleClass>rules;
	vector<string>domain;
	vector<string> alphabaticallySort(vector<string> a);
};

#endif