#include "relation.h"

relation::relation(){} //constructor

void relation::addName(const std::string& userName) {
	name = userName;
}

void relation::addHeader(header userHeader) {
	relationHeader = userHeader;
}

void relation::addTuple(tupleClass newTuple){ //add new tuple to set
	tuples.insert(newTuple);
}

std::string relation::toString() {
	std::string sendThis;
	for(tupleClass t: tuples) {
		sendThis += "  ";
		for(unsigned int j=0; j<relationHeader.attributes.size(); j++) {
			sendThis += relationHeader.attributes[j]+"="+t.values[j];
			if(j == relationHeader.attributes.size()-1) {
				sendThis+= '\n';
			}
			else sendThis += ", ";
		}
	}
	return sendThis;
}

std::string relation::getName() {
	return name;
}

int relation::getNumTuples() {
	return tuples.size();
}

header relation::getHeader() {
	return relationHeader;
}

std::set<tupleClass>relation::getTupleSet() {
	return tuples;
}

bool relation::compareTuple(tupleClass t1, tupleClass t2) { //if the tuples are the exact same this function will return true
	bool same = true;
	if(t1.size() != t2.size()) return false;
	for(int i=0; i<t1.size(); i++) {
		if(t1.get_value(i) != t2.get_value(i)) same = false;
	}
	return same;
}

relation relation::select1(int position, std::string value) { 
	relation* temp = new relation;
	(*temp).addHeader(relationHeader); //header of new relation will be the same as the header of old
	for(tupleClass T: tuples) { //for every tuple (row), we need to check the column of position_index to see if the value there matches the value given 
		if(T.get_value(position) == value) {
			(*temp).addTuple(T); //if the value at the position index is the same then we will add that tuple to the new relation 
		}
	}
	return *temp;
}

relation relation::select2(int position_1, int position_2) {
	relation* temp = new relation;
	(*temp).addHeader(relationHeader); //the header of the new relation will be the same as the header of old

	for(tupleClass t: tuples) {
		if(t.get_value(position_1) == t.get_value(position_2)) { //if the values at the two positions match then add the tuple to the new relation
			(*temp).addTuple(t);
		}
	}
	return *temp;
}

relation relation::project(const std::vector<int>&columns) {
	relation* temp = new relation;
	std::vector<std::string>new_attributes;
	std::vector<std::string>new_values;

	for(unsigned int i=0; i<columns.size(); i++) new_attributes.push_back(relationHeader.get_attribute(columns[i])); //for every value in columns add corresponding header value to new attributes
	(*temp).relationHeader.addAttributes(new_attributes);
	for(tupleClass T: tuples) { // for every tuple
		tupleClass* tempT = new tupleClass;
		for(unsigned int i=0; i<columns.size(); i++) new_values.push_back(T.get_value(columns[i]));
		if(new_values.size() > 0) {
				(*tempT).addvalues(new_values);
				new_values.clear();
				(*temp).addTuple(*tempT);
			}
		delete tempT;
	}
	return *temp;
}

relation relation::join(relation join) {
	relation* result = new relation;
	std::vector<std::pair<int,int>> pair_vector;
	std::vector<std::string>new_attributes;
	std::vector<int>join_values;
	std::vector<std::string>new_tuple_values;
	bool isValid = true;

	// STEP 1: populate a vector which with the pairs of indeces with matching header attributes. These are the headers which must contain same values in r1 and r2
	for(unsigned int i=0; i<getHeader().getNumAttributes(); i++) { //for every attribute in home header
		new_attributes.push_back(getHeader().get_attribute(i)); // copy attributes from relation 1 to the new vector of attributes
		for(unsigned j =0; j<join.getHeader().getNumAttributes(); j++) { //for ever attribute in header of relation 2
			if(getHeader().get_attribute(i) == join.getHeader().get_attribute(j)) { //if we find headers with the same value
				pair_vector.push_back(std::make_pair(i,j));
				break;
			}
		}
	}
	// STEP 2: create new header (TODO: we could make this into a separate function)

		// copy attributes from relation 2 if not already in the vector of new attributes
	for(unsigned int i=0; i<join.getHeader().getNumAttributes(); i++) { 
		bool exists = false;
		for(unsigned int j=0; j<new_attributes.size(); j++) {
			if(join.getHeader().get_attribute(i) == new_attributes[j]) exists = true;
		}
		if(!exists) {
			new_attributes.push_back(join.getHeader().get_attribute(i));
			join_values.push_back(i);
		}
	}
		// create new header using vector of new attributes
	header* tempHeader = new header;
	tempHeader->addAttributes(new_attributes);
	result->addHeader(*tempHeader);
	delete tempHeader;
	
	// STEP 3: create new tuples for the new relation
	for(tupleClass t1: tuples) { //for every tuple in relation 1
		for(tupleClass t2: join.tuples) { //for every tuple in relation 2
			for(unsigned int i=0; i<pair_vector.size(); i++) { //for all of the pairs which should match
				isValid = true;
				if(t1.get_value(pair_vector[i].first) != t2.get_value(pair_vector[i].second)) {
					isValid = false;  //if tuples that should match do not match
					break;
				} 
			}
			if(isValid) { // tuple is valid so we need to add every value in tuple 1 and then all the values in tuple 2 from indeces in join_values vector
				for(int i=0; i<t1.size(); i++) new_tuple_values.push_back(t1.get_value(i));
				for(int i=0; i<t2.size(); i++) {
					for(unsigned int j=0; j<join_values.size(); j++) {
						if(i==join_values[j]) new_tuple_values.push_back(t2.get_value(i));
					}
				}
				tupleClass* temp_tup = new tupleClass;
				temp_tup->addvalues(new_tuple_values);
				result->addTuple(*temp_tup);
				new_tuple_values.clear();
			}
		}
	}
	return *result;
}

void relation::rename(std::vector<std::string> new_attributes) {
	relationHeader.addAttributes(new_attributes);
	/**header* tempH = new header;
	(*tempH).addAttributes(new_attributes);
	relationHeader = *tempH;**/
}

relation relation::onion(relation onion) { // NOTE: Put the tuples from the db relation first 3 relations, home, onion, and result.
	relation* result = this;
	relation* cout_rel = new relation;
	cout_rel->addHeader(this->getHeader()); 
	for(tupleClass t: onion.tuples) {
		if(result->tuples.insert(t).second) {; // tuple was added and needs to be couted
		cout_rel->addTuple(t);
		}
	}
	std::cout << cout_rel->toString();
	delete cout_rel;
	return *result;
}