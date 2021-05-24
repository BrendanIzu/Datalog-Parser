//
// Created by Brendan on 1/23/2021.
//

#include "token.h"

token::token(string &userValue, int &userIndex, TokenType &userToken) { //constructor
    value = userValue;
    index= userIndex;
    tokenType = userToken;
}

token::~token() = default;

string token::toString() const {
    string tokenString;
    switch(tokenType) {
        case COMMA:
            tokenString = "COMMA";
            break;
        case PERIOD:
            tokenString = "PERIOD";
            break;
        case Q_MARK:
            tokenString = "Q_MARK";
            break;
        case LEFT_PAREN:
            tokenString = "LEFT_PAREN";
            break;
        case RIGHT_PAREN:
            tokenString = "RIGHT_PAREN";
            break;
        case COLON:
            tokenString = "COLON";
            break;
        case COLON_DASH:
            tokenString = "COLON_DASH";
            break;
        case MULTIPLY:
            tokenString = "MULTIPLY";
            break;
        case ADD:
            tokenString = "ADD";
            break;
        case SCHEMES:
            tokenString = "SCHEMES";
            break;
        case FACTS:
            tokenString = "FACTS";
            break;
        case RULES:
            tokenString = "RULES";
            break;
        case QUERIES:
            tokenString = "QUERIES";
            break;
        case ID:
            tokenString = "ID";
            break;
        case STRING:
            tokenString = "STRING";
            break;
        case COMMENT:
            tokenString = "COMMENT";
            break;
        case ENOF:
            tokenString = "EOF";
            break;
        case UNDEFINED:
            tokenString = "UNDEFINED";
            break;
    }
    return '('+tokenString+','+'\"'+value+"\","+to_string(index)+")\n";
}

string token::getValue() {
	return value;
}