#include "predicateClass.h"

void predicateClass::addToken(token add) {
	predicateVec.push_back(add);
}

void predicateClass::clear() {
	predicateVec.clear();
}

std::string predicateClass::getPredicate() {
	std::string send_this;
	for(unsigned int i = 0; i < predicateVec.size(); i++) {
		send_this+=predicateVec[i].value;
	}
	return send_this;
}

std::string predicateClass::getValue(const int& i) {
	return predicateVec[i].getValue();
}

int predicateClass::size() {
	return predicateVec.size();
}

std::string predicateClass::toString() {
	std::string sendThis;
	for(unsigned int i=0; i<predicateVec.size(); i++) {
		sendThis += predicateVec[i].value;
	}
	return sendThis;
}