#ifndef RELATION_H
#define RELATION_H
#pragma once

#include "tupleClass.h"
#include "header.h"

#include<set>
#include<string>
#include<iostream>

class relation {
	public:
	relation();
	std::string toString();
	std::string getName();
	int getNumTuples();
	header getHeader();
	void addName(const std::string& userName);
	void addHeader(header userHeader);
	void addTuple(tupleClass newTuple);
	bool compareTuple(tupleClass t1, tupleClass t2);
	std::set<tupleClass> getTupleSet();
	// relation functions
	void rename(std::vector<std::string>new_attributes);
	relation select1(int position, std::string value); //paramter is column we are going to check and the value we are checking for 
	relation select2(int position_1, int position_2);
	relation project(const std::vector<int>&columns); //parameter is list of columns that we are going to keep in final relation
	relation join(relation join); //paramter is relation we wish to join with current relation
	relation onion(relation onion);
	private:
	header relationHeader; //vector of strings which correspond with tuple
	std::set<tupleClass>tuples; //set of vectors
	std::string name; //string name of relation
};

#endif