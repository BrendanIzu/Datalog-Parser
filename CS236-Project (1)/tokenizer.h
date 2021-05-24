//
// Created by Brendan on 1/23/2021.
//

#ifndef TOKENIZER_H
#define TOKENIZER_H
#pragma once

#include <fstream>

#include "token.h"

using namespace std;

class tokenizer {
public:
    tokenizer(string& input, int lineNum); //constructor; takes file contents as a string
    ~tokenizer(); //de-constructor
    token getNextToken(); //read and create just one token

private:
    string userValue; //whatever needs to be tokenized
    unsigned int index = 0; //current index
    int currIndex = 0;
    TokenType localToken = UNDEFINED;

    //FSA functions
    TokenType s0(string& a); // :
    TokenType s1(string& a); // -
    TokenType s2(string& a); // '
    TokenType s3(string& a); // any char
    TokenType s4(string& a); //
    TokenType s5(string &a); // #
    TokenType s6(string &a); // |
    TokenType s7(string &a); // # end
    TokenType s8(string &a); // for strings and IDs
	TokenType s9(string &a); //IDs
};

#endif
