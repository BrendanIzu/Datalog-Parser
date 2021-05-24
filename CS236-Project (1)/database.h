#ifndef DATABASE_H
#define DATABASE_H
#pragma once

#include "relation.h"

#include<map>
#include<iostream>
#include<string>
#include<vector>

class database {
public: 
void addRelation(std::string name, std::vector<std::string>newAttributes);
void replaceRelation(relation newRelation);
int getNumRelations(); 
int getNumTuples();
relation getRelation(std::string lookup); //returns relation given a string
std::map<std::string, relation>myMap; //maps relations to a name aka SNAP to a table
std::vector<std::string>names;
};

#endif
