#ifndef TUPLECLASS_H
#define TUPLECLASS_H
#pragma once

#include<vector>
#include<string>

class tupleClass {
public: 
tupleClass(); //constructor
bool operator<(const tupleClass & other)const;
std::string toString();
void addvalues(std::vector<std::string>newValues);
std::string get_value(int i); //TODO: rename this function
int size();

std::vector<std::string>values; //make private
};

#endif
