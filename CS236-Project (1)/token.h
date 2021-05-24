//
// Created by Brendan on 1/23/2021.
//

#ifndef TOKEN_H
#define TOKEN_H
#pragma once 

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum TokenType{COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES,
        QUERIES, ID, STRING, COMMENT, UNDEFINED, ENOF };

class token {
public:
    token(string& userValue, int& userIndex, TokenType& userToken); //constructor
    ~token(); //de-constructor
    string value; //actual value
    int index; //line the token starts on
    TokenType tokenType; //type of token
    string toString() const; // --> (COLON_DASH, ":-", 6)
	string getValue();
};

#endif
