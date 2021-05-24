#include "interpreter.h"

interpreter::interpreter(datalogProgram userData) {
	bool done = false;
	std::map<std::string,int>sizes_map;
	data = userData;
	addSchemes();
	addFacts();
	int num_times = 0;
	std::cout << "Rule Evaluation\n";
	while(!done) {
		int itr = 0;
		for (auto a : base.myMap) sizes_map[a.first] = a.second.getNumTuples();
		evaluateRules();
		for (auto a : base.myMap) { //TODO: something is wrong with how it checks to see if it should run again, I think this is because when project reorders the headers, then the sizes dont match up iykwim
			if(a.second.getNumTuples() != sizes_map[a.first]) {
				done = false;
				break;
			}
			else done = true;
			itr++;
		}
		sizes_map.clear();
		num_times++;
	}
	std::cout << "\nSchemes populated after " << num_times << " passes through the Rules.\n\n";
	std::cout << "Query Evaluation\n";
	evaluateQueries();
	std::cout << std::endl;
}

void interpreter::addSchemes() {
	std::string name;
	std::vector<std::string>newAttributes;
	for(unsigned int i=0; i<data.schemes.size(); i++) { //for every scheme in data
		for(unsigned int j=0; j<data.schemes[i].predicateVec.size(); j++) { //for every predicate in a scheme
			if(data.schemes[i].predicateVec[j].tokenType == ID) { //if predicate is an ID, we need to add it to relation vector
				if(j == 0) { //i.e the first ID in a given scheme
					name = data.schemes[i].predicateVec[j].value;
				}
				else newAttributes.push_back(data.schemes[i].predicateVec[j].value); //else add it to vector of attributes
			}
		}
		base.addRelation(name, newAttributes);
		base.names.push_back(name);
		newAttributes.clear();
	}
}
void interpreter::addFacts() {
	std::string checkName;
	std::vector<string>newTuple; //vector of strings which we will add as a tuple
	for(unsigned int i=0; i < data.facts.size(); i++) { //for every fact in data
		for(unsigned int j=0; j < data.facts[i].predicateVec.size(); j++) { //for every predicate in a fact
			if(data.facts[i].predicateVec[j].tokenType == ID) { //only care about the ID
				checkName = data.facts[i].predicateVec[j].value;
			}
			else if(data.facts[i].predicateVec[j].tokenType == STRING) {
				newTuple.push_back(data.facts[i].predicateVec[j].value);
			}
		}
		tupleClass* tuplePtr = new tupleClass;
		(*tuplePtr).addvalues(newTuple);
		base.myMap[checkName].addTuple(*tuplePtr);
		newTuple.clear();
		delete tuplePtr;
	}
}

void interpreter::evaluateRules() {
	for(int i=0; i<data.getNumRules(); i++) { //for every rule
		relation* temp_rel = new relation;
		std::vector<relation>relations;
		// STEP 1: we need to evaluate the predicates on the right side of every rule, and populate a vector of the resulting relations
		cout << data.getRule(i).toString() << std::endl;
		for(int j=0; j<data.getRule(i).getNumPredicates(); j++) relations.push_back(evaluatePredicate(data.getRule(i).getPredicate(j),false)); //evaluate each of the right side predicates and put them on this vector 

		// STEP 2: use join to join all of the resulting relations in relations vector
		
		*temp_rel = relations[1];
		if(relations.size()) {
			for(unsigned int j=2; j<relations.size();j++) *temp_rel = temp_rel->join(relations[j]);
		}

		//STEP 3: use project with header predicate (header predicate is relations[0])
		std::vector<int>project_columns;

		for(unsigned int j=0; j<relations[0].getHeader().getNumAttributes(); j++) {
			for(unsigned int k=0; k<temp_rel->getHeader().getNumAttributes(); k++) {
				if(relations[0].getHeader().get_attribute(j) == temp_rel->getHeader().get_attribute(k)) {
					project_columns.push_back(k);
				}
			}
		}

		*temp_rel = temp_rel->project(project_columns);

		relation db_relation = base.getRelation(data.getRule(i).getPredicate(0).predicateVec[0].value);
		temp_rel->rename(db_relation.getHeader().getAttributes()); 
		
		//STEP 4: union the result relation with the relation from database (result relation should be the parameter)
		*temp_rel = db_relation.onion(*temp_rel);
		temp_rel->addName(data.getRule(i).getPredicate(0).predicateVec[0].value);

		//STEP 5: replace relation in the database with result relation
		base.replaceRelation(*temp_rel);
	}
}

void interpreter::evaluateQueries() {
	for(auto i : data.queries) evaluatePredicate(i,true);
}

relation interpreter::evaluatePredicate(predicateClass p, bool queries) {
	int itr = 0;
	std::vector<int> qp_nums;
	std::vector<std::string> qp_vals;
	relation* temp = new relation;
	for(int i = 0; i < p.size(); i++) { //for all the seperat parts of a predicate SK ( A , 'c' )
		bool found = false;
		std::string q = p.getValue(i); // get one portion of the predicate

		if(!i) { // first part will always be the relation name
			std::string relation_name = q; 
			*temp = base.getRelation(relation_name); // sets temp equal to the relation that we want to look at

		} 
		else if(isalpha(q[0])) { // if parameter is a variable (i.e. X, Y, Z)
			found = false;
			for(unsigned int j = 0; j < qp_vals.size(); j++) { //search to see if we have seen this variable before
				if(qp_vals[j] == q) { // variable has been spotted
					*temp = (*temp).select2(itr,j); //change the relation with select2
					found = true;
				}
			}
			if(!found) { // variable was never found
				qp_vals.push_back(q);
				qp_nums.push_back(itr);
			}
			itr++;
		}
		else if(q[0] == '\'') { // if parameter is a constant (i.e. 'snoopy')
			*temp = (*temp).select1(itr,q);
			itr++;
		}
	}
	if(qp_nums.size()) *temp = (*temp).project(qp_nums);
	(*temp).rename(qp_vals);

	if(queries) {
		cout << p.getPredicate() << "? ";
		if((*temp).getNumTuples()!= 0) {
			cout << "Yes(" << (*temp).getNumTuples() << ")\n";
			if(qp_vals.size()) {
				cout << (*temp).toString();
			}
		}
		else cout << "No\n";
	}
	return *temp;
}
