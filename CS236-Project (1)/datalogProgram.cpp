#include "datalogProgram.h"
#include <bits/stdc++.h>

void datalogProgram::addScheme(predicateClass add) {
	schemes.push_back(add);
}
void datalogProgram::addFact(predicateClass add) {
	facts.push_back(add);
}

void datalogProgram::addQuery(predicateClass add) {
	queries.push_back(add);
}

void datalogProgram::addRule(ruleClass add) {
	rules.push_back(add);
}

void datalogProgram::addDomain(string add) {
	bool alreadythere = false;
	for(unsigned int i = 0; i < domain.size(); i++ ) {
		if(domain[i] == add) {alreadythere = true;}
	}
	if(!alreadythere) domain.push_back(add);
}

void datalogProgram::listSchemes() {
	cout << "Schemes(" << schemes.size() << "):\n"; 
	for(auto & i: schemes) {
		cout << "  ";
		cout << i.getPredicate();
		cout << "\n";
	}
}

void datalogProgram::listFacts() {
	cout << "Facts(" << facts.size() << "):\n"; 
	for(auto & i: facts) {
		cout << "  ";
		cout << i.getPredicate();
		cout << ".\n";
	} 
}

void datalogProgram::listQueries() {
	cout << "Queries(" << queries.size() << "):\n";  
	for(auto & i: queries) {
		cout << "  ";
		cout << i.getPredicate();
		cout << "?\n";
	}
}

predicateClass datalogProgram::getQuerie(int& i) {
	return queries[i];
}

void datalogProgram::listRules() {
	cout << "Rules(" << rules.size() << "):\n"; 
	for(unsigned int i = 0; i < rules.size(); i++) {
		cout << "  ";
		rules[i].getRule();
		cout << "\n";
	}
}

void datalogProgram::listDomain() {
	domain = alphabaticallySort(domain);
	cout << "Domain(" << domain.size() << "):\n"; 
	for(auto & i: domain) {cout << "  " << i << endl;}
}

bool mycomp(string a, string b){
	return a<b;
}

vector<string> datalogProgram::alphabaticallySort(vector<string> a){
	sort(a.begin(),a.end(),mycomp);
	return a;
}

int datalogProgram::getNumQueries() {
	return queries.size();
}

ruleClass datalogProgram::getRule(int& i) {
	return rules[i];
}

int datalogProgram::getNumRules() {
	return rules.size();
}