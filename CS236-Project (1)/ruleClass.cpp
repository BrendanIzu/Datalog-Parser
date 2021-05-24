#include "ruleClass.h"

void ruleClass::addPredicate(predicateClass add) {
	ruleVec.push_back(add);
}

void ruleClass::clear() {
	ruleVec.clear();
}

void ruleClass::getRule() {
	for(unsigned int i = 0; i < ruleVec.size(); i++) {
		cout << ruleVec[i].getPredicate();
		if(i == 0) {
			cout << " :- ";
			continue;
		}
		else if(i == ruleVec.size()-1) {
			cout << ".";
			continue;
		}
		else {
			cout << ",";
			continue;
		}
	}
}

predicateClass ruleClass::getPredicate(const int& i) {
	return ruleVec[i];
}

int ruleClass::getNumPredicates() {
	return ruleVec.size();
}

std::string ruleClass::toString() {
	std::string sendThis;
	for(unsigned int i = 0; i < ruleVec.size(); i++) {
		sendThis+=ruleVec[i].getPredicate();
		if(i == 0) {
			sendThis+=" :- ";
			continue;
		}
		else if(i == ruleVec.size()-1) {
			sendThis+=".";
			continue;
		}
		else {
			sendThis+=",";
			continue;
		}
	}
	return sendThis;
}
