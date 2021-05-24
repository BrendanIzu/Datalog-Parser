#ifndef INTERPRETER_H
#define INTERPRETER_H
#pragma once

#include "datalogProgram.h"
#include "relation.h"
#include "header.h"
#include "predicateClass.h"
#include "database.h"

#include<string>
#include<map>

class interpreter {
public: 
interpreter(datalogProgram userData); //constructor
datalogProgram data;
database base;
relation evaluatePredicate(predicateClass p, bool queries);
void addSchemes();
void addFacts();
void evaluateQueries();
void evaluateRules();
};

#endif
