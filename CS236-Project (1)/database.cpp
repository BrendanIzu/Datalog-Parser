#include "database.h"

void database::addRelation(std::string name, std::vector<std::string>newAttributes) {
	header* headerPtr = new header;
	(*headerPtr).addAttributes(newAttributes);
	relation* relationPtr = new relation; //create new relation with name and newHeader
	(*relationPtr).addName(name);
	(*relationPtr).addHeader(*headerPtr);
	myMap[name] = *relationPtr; //map name and newRelation and store in database
	delete headerPtr;
	delete relationPtr;
}

void database::replaceRelation(relation newRelation) {
	std::string relationName = newRelation.getName();
	myMap[relationName] = newRelation;
}

relation database::getRelation(std::string lookup) {
	return myMap[lookup];
}

int database::getNumRelations() {
	return myMap.size();
}

int database::getNumTuples() {
	int sendit = 0;
	for (auto x : myMap) {
		
		sendit += x.second.getNumTuples(); 
	}
	return sendit;
}