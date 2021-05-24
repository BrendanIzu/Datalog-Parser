#ifndef PREDICATECLASS_H
#define PREDICATECLASS_H
#pragma once

#include "token.h"

#include<list>

class predicateClass {
	public:
	void addToken(token add);
	void clear();
	std::string getPredicate();
	std::string getValue(const int& i);
	std::string toString();
	int size(); 
	vector<token> predicateVec; //should be made private
};

#endif