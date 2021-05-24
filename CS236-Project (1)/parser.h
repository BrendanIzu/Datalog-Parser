#ifndef PARSER_H
#define PARSER_H
#pragma once

#include "token.h"
#include "datalogProgram.h"
#include "predicateClass.h"
#include "ruleClass.h"

#include<list>
#include<vector>

class parser { 
public:
parser(vector<token>& tokenVec);
~parser();

datalogProgram data;
predicateClass tempPredicate;
ruleClass tempRule;
vector<TokenType> tokens;
vector<token> tokenVecCopy;
bool isFact = false;
bool isRule = false;
int a = 0;
void datalog(vector<TokenType>& tokenVec);
void schemeList(TokenType T);
void factList(TokenType T);
void ruleList(TokenType T);
void queryList(TokenType T);
void scheme(TokenType T);
void fact(TokenType T);
void rule(TokenType T);
void query(TokenType T);
void headPredicate(TokenType T);
void predicate(TokenType T);
void predicateList(TokenType T);
void parameterList(TokenType T);
void stringList(TokenType T);
void idList(TokenType T);
void parameter(TokenType T);
void expression(TokenType T);
void awperator(TokenType T);

private:
};

#endif