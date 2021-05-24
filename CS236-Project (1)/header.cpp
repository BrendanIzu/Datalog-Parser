#include "header.h"

header::header() { //constructor
}

void header::addAttributes(const std::vector<std::string>& newAttributes) {
	attributes = newAttributes;
}

std::vector<std::string> header::getAttributes() {
	return attributes;
}

std::string header::toString() {
	std::string sendThis;
	for(unsigned int i=0; i<attributes.size(); i++) {
		sendThis += attributes[i]+" ";
	}
	return sendThis;
}

unsigned int header::getNumAttributes() {
	return attributes.size();
}

std::string header::get_attribute(int i) {
	return attributes[i];
}