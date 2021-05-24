//
// Created by Brendan on 1/23/2021.
//

#ifndef LEXER_H
#define LEXER_H
#pragma once

#include "tokenizer.h"

#include <vector>

using namespace std;

class lexer {
public:
  lexer(string& filename); //takes file contents as a string
  ~lexer();
  vector<token>tokenVec; //stores tokens received from the tokenizer;
  vector<string>returnVec; //this is the vector we will return eventually; it will call token::toString a bunch of times
  vector<string>sendVec; //send the contents of this vector to be tokenized
  vector<int>indexVec;
  vector<int>lineVec;
  int lineNum = 1;
  void parse(string& contents, int newIndex); //determines when to send a string to be tokenized
private:
    string filename; //the name of the input file
};


#endif
