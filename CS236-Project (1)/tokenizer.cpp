//
// Created by Brendan on 1/23/2021.
//

#include "tokenizer.h"

/**
 * Algorithm for parsing through an input file
 *
 * 1. there should already be a massive string containing all the input from the file
 * 2. read the file one char at a time looking for certain things like ';' or 'a'
 * 3. based on what it finds, call function in tokenizer to determine what it's token needs to be
 *   3a. if parse encounters a \n char, ++lineNum
 *   3b. everytime a new char is read, ++index
 * 4. create a new token with all of the information
 * 5. continue until you reach the end of the string
 */

/**
 * tokenizer should have the entire file stored as a string and then use variables to navigate through
 * and send tokens to the lexers token vector
 * @param input
 */

tokenizer::tokenizer(string& input, int lineNum) {
    userValue = input; //put all the file contents into local variable string contents
    currIndex = lineNum;
}

tokenizer::~tokenizer() = default;

token tokenizer::getNextToken() { //this needs to create a whole new token object
    if(userValue.length() >= 3) { //if the userValue > 1 then it must be a string
        if(userValue == "Schemes") {
            localToken = SCHEMES;
        }
        else if(userValue == "Facts") {
            localToken = FACTS;
        }
        else if(userValue == "Rules") {
            localToken = RULES;
        }
        else if(userValue == "Queries") {
            localToken = QUERIES;
        }
        else if(userValue[0] == '#') {
            localToken = s5(userValue);
        }
        else if(userValue[0] == '\'') {
            localToken = s2(userValue);
        }
        else {
            localToken = s9(userValue);
        }
    }
    else if(isalpha(userValue[0]) || isdigit(userValue[0])) {
        localToken = s9(userValue);
    }
    else if(userValue == "") {
        localToken = ENOF;
    }
    else {
        switch(userValue[0]){
            case ',': localToken = COMMA;
                break;
            case '.': localToken = PERIOD;
                break;
            case '?': localToken = Q_MARK;
                break;
            case '(': localToken = LEFT_PAREN;
                break;
            case ')': localToken = RIGHT_PAREN;
                break;
            case ':': localToken = s0(userValue);
                break;
            case '*': localToken = MULTIPLY;
                break;
            case '+': localToken = ADD;
                break;
            case '\'': localToken = s2(userValue);
                break;
            case '#': localToken = s5(userValue);
                break;
            default: localToken = UNDEFINED;
                break;
        }
    }

    token *brendan = new token(userValue, currIndex, localToken); //FIX: somehow send the right TokenType
    return *brendan;
}

TokenType tokenizer::s0(string &a) {
    if(a[index] == ':') {
        index++;
        return s1(a);
    }
    else return UNDEFINED;
}

TokenType tokenizer::s1(string &a) {
    if(a[index] == '-') {
        return COLON_DASH;
    }
    else {
        return COLON;
    }
}

TokenType tokenizer::s2(string &a) {
    if(a[index] == '\'') {
        index++;
		return s3(a);
    }
	else return UNDEFINED;
}

TokenType tokenizer::s3(string &a) {
	if(index > userValue.length()) {
		return UNDEFINED;
	}
    else if(a[index] == '\'') {
		index++;
		return s4(a);
	}
	else {
		index++;
		return s3(a);
	}
}

TokenType tokenizer::s4(string &a) {
	if(index > userValue.length()) {
		return UNDEFINED;
	}
	else if(a[index] == '\'') {
		index++;
		return s3(a);
	}
	else return STRING;
}

TokenType tokenizer::s5(string &a) {
    if(a[index] == '#') {
        index++;
        return s6(a);
    }
    else if(index > userValue.length()) {
        return COMMENT;
    }
    else return UNDEFINED;
}

TokenType tokenizer::s6(string &a) {
    if(a[index] == '|') {
        index++;
        return s7(a);
    }
    else {
       return COMMENT;
    }
}

TokenType tokenizer::s7(string &a) {
    if(a[index] == '|') {
        ++index;
        return s5(a);
    }
    else if(index == userValue.length()) {
        return UNDEFINED;
    }
    else {
        index++;
        return s7(a);
    }
}

TokenType tokenizer::s8(string &a) {
    if(index == userValue.length()) {
        return ID;
    }
    else if(isalpha(a[index]) || isdigit(a[index])) {
        index++;
        return s8(a);
    }
    else return UNDEFINED;
}

TokenType tokenizer::s9(string &a){
	if(isdigit(a[index])) { return UNDEFINED; }
	else return s8(a);
}
