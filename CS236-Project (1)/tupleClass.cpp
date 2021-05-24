#include "tupleClass.h"
#include<sstream>

tupleClass::tupleClass() {};

std::string tupleClass::toString() {
	std::string sendThis;
	for(unsigned int i = 0; i < values.size(); i++) {
		sendThis += values[i];
	}
	return sendThis;
}

bool tupleClass::operator<(const tupleClass & other)const{
	for(unsigned int i = 0; i < values.size(); i++) {
		if(values.at(i) < other.values[i]) {
			return true;
		}
		else if(values.at(i) > other.values.at(i)) {
			return false;
		}
	}
	return false;
}

void tupleClass::addvalues(std::vector<std::string> newValues) {
	values = newValues;
}

std::string tupleClass::get_value(int i) {
	return values[i];
}

int tupleClass::size() {
	return values.size();
}