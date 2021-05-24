#include "parser.h"
#include "interpreter.h"

parser::parser(vector<token>& tokenVec) {
	for(unsigned int i = 0; i < tokenVec.size(); i++) {tokens.push_back(tokenVec[i].tokenType);}
	tokenVecCopy = tokenVec;
	try {	
		datalog(tokens);
	} catch (int error) {
		cout << "Failure!\n  " << tokenVec[error].toString();
	}
}

parser::~parser() = default;

void parser::datalog(vector<TokenType>& tokens) { //SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
	if(tokens[a] == SCHEMES) {a++;} else throw a;
	if(tokens[a] == COLON) {a++;} else throw a;
	if(tokens[a] == ID) {scheme(tokens[a]);} else throw a;
	if(tokens[a] == ID) {schemeList(tokens[a]);}
	if(tokens[a] == FACTS) {a++;} else throw a;
	if(tokens[a] == COLON) {a++;} else throw a;
	if(tokens[a] == ID) {factList(tokens[a]);}
	if(tokens[a] == RULES) {a++;} else throw a;
	if(tokens[a] == COLON) {a++;} else throw a;
	if(tokens[a] == ID) {ruleList(tokens[a]);}
	if(tokens[a] == QUERIES) {a++;} else throw a;
	if(tokens[a] == COLON) {a++;} else throw a;
	if(tokens[a] == ID) {query(tokens[a]);} else throw a;
	if(tokens[a] == ID) {queryList(tokens[a]);}
	if(tokens[a] == ENOF) {/*cout << "Success!\n";*/} else throw a;
	/**data.listSchemes();
	data.listFacts();
	data.listRules();
	data.listQueries();
	data.listDomain();**/
	new interpreter(data);
}

void parser::schemeList(TokenType T) { //scheme schemeList | lambda
	if(tokens[a] == ID) {scheme(tokens[a]);} else return;
	if(tokens[a] == ID) {schemeList(tokens[a]);} else return;
}

void parser::factList(TokenType T) { //fact factList | lambda
	if(tokens[a] == ID) {fact(tokens[a]);} else return;
	if(tokens[a] == ID) {factList(tokens[a]);} else return;
} 

void parser::ruleList(TokenType T) { //rule ruleList | lambda
	if(tokens[a] == ID) {rule(tokens[a]);} else return;
	if(tokens[a] == ID) {ruleList(tokens[a]);} else return;
}

void parser::queryList(TokenType T) { //query queryList | lambda
	if(tokens[a] == ID) {query(tokens[a]);} else return;
	if(tokens[a] == ID) {queryList(tokens[a]);} else return;
}

void parser::scheme(TokenType T) { //ID LEFT_PAREN ID idList RIGHT_PAREN
	if(tokens[a] == ID) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++; 
	} else throw a;

	if(tokens[a] == LEFT_PAREN) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++; 
	} else throw a;
	if(tokens[a] == ID) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++; 
	} else throw a;
	if(tokens[a] == COMMA) {idList(tokens[a]);}
	if(tokens[a] == RIGHT_PAREN) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++; 
		data.addScheme(tempPredicate);
		tempPredicate.clear();
	} else throw a;
}

void parser::fact(TokenType T) { //ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
	isFact = true;
	if(tokens[a] == ID) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++;} else throw a;
	if(tokens[a] == LEFT_PAREN) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++;} else throw a;
	if(tokens[a] == STRING) {
		if(isFact) data.addDomain(tokenVecCopy[a].value);
		tempPredicate.addToken(tokenVecCopy[a]);
		a++;} else throw a;
	if(tokens[a] == COMMA) stringList(tokens[a]);
	if(tokens[a] == RIGHT_PAREN) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++;} else throw a;
	if(tokens[a] == PERIOD) {
		a++;
		data.addFact(tempPredicate);
		tempPredicate.clear();
		} else throw a;
	isFact = false;
}

void parser::rule(TokenType T) { //headPredicate COLON_DASH predicate predicateList PERIOD
	isRule = true;
	if(tokens[a] == ID) headPredicate(tokens[a]); else throw a;
	if(tokens[a] == COLON_DASH) a++; else throw a;
	if(tokens[a] == ID) predicate(tokens[a]); else throw a;
	if(tokens[a] == COMMA) predicateList(tokens[a]);
	if(tokens[a] == PERIOD) {
		a++;
		data.addRule(tempRule);
		tempRule.clear();
		tempPredicate.clear();} else throw a;
	isRule = false;
}

void parser::query(TokenType T) { //predicate Q_MARK
	if(tokens[a] == ID) predicate(tokens[a]); else throw a;
	if(tokens[a] == Q_MARK) {
		a++;
		data.addQuery(tempPredicate);
		tempPredicate.clear();
		} else throw a;
}

void parser::headPredicate(TokenType T) { //ID LEFT_PAREN ID idList RIGHT_PAREN
	if(tokens[a] == ID) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++;} else throw a;
	if(tokens[a] == LEFT_PAREN) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++;} else throw a;
	if(tokens[a] == ID) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++;} else throw a;
	if(tokens[a] == COMMA) idList(tokens[a]);
	if(tokens[a] == RIGHT_PAREN) {
		tempPredicate.addToken(tokenVecCopy[a]);
		if(isRule) {
			tempRule.addPredicate(tempPredicate);
			tempPredicate.clear();
		}
		a++;} else throw a;
}

void parser::predicate(TokenType T) { //ID LEFT_PAREN parameter parameterList RIGHT_PAREN
	if(tokens[a] == ID) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++;} else throw a;
	if(tokens[a] == LEFT_PAREN) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++;} else throw a;
	if(tokens[a] == STRING ||tokens[a] == ID ||tokens[a] == LEFT_PAREN) parameter(tokens[a]); else throw a;
	if(tokens[a] == COMMA) parameterList(tokens[a]);
	if(tokens[a] == RIGHT_PAREN) {
		tempPredicate.addToken(tokenVecCopy[a]);
		if(isRule) {
			tempRule.addPredicate(tempPredicate);
			tempPredicate.clear();
		}
		a++;} else throw a;
}

void parser::predicateList(TokenType T) { //COMMA predicate predicateList | lambda
	if(tokens[a] == COMMA) {
		a++;} else return;
	if(tokens[a] == ID) predicate(tokens[a]); else throw a;
	if(tokens[a] == COMMA) predicateList(tokens[a]);
}

void parser::parameterList(TokenType T) { //COMMA parameter parameterList | lambda
	if(tokens[a] == COMMA) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++;} else return;
	if(tokens[a] == STRING ||tokens[a] == ID ||tokens[a] == LEFT_PAREN) parameter(tokens[a]); else throw a;
	if(tokens[a] == COMMA) parameterList(tokens[a]);
}

void parser::stringList(TokenType T) { //COMMA STRING stringList | lambda
	if(tokens[a] == COMMA) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++;} else return;
	if(tokens[a] == STRING) {
		if(isFact) data.addDomain(tokenVecCopy[a].value);
		tempPredicate.addToken(tokenVecCopy[a]);
		a++;} else throw a;
	if(tokens[a] == COMMA) {stringList(tokens[a]);}
}

void parser::idList(TokenType T) { //COMMA ID idList | lambda
	if(tokens[a] == COMMA) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++;} else return;
	if(tokens[a] == ID) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++;} else throw a;
	if(tokens[a] == COMMA) {idList(tokens[a]);}
}

void parser::parameter(TokenType T) { //STRING | ID | expression
	if(tokens[a] == STRING) {
		if(isFact) data.addDomain(tokenVecCopy[a].value);
		tempPredicate.addToken(tokenVecCopy[a]);
		a++;}
	else if(tokens[a] == ID) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++;}
	else if(tokens[a] == LEFT_PAREN) expression(tokens[a]);
	else throw a;
}

void parser::expression(TokenType T) { //LEFT_PAREN parameter operator parameter RIGHT_PAREN
	if(tokens[a] == LEFT_PAREN) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++;} else throw a;
	if(tokens[a] == STRING ||tokens[a] == ID ||tokens[a] == LEFT_PAREN) parameter(tokens[a]); else throw a;
	if(tokens[a] == ADD ||tokens[a] == MULTIPLY) awperator(tokens[a]); else throw a;
	if(tokens[a] == STRING ||tokens[a] == ID ||tokens[a] == LEFT_PAREN) parameter(tokens[a]); else throw a;
	if(tokens[a] == RIGHT_PAREN) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++;} else throw a;
}

void parser::awperator(TokenType T) { //ADD | MULTIPLY
	if(tokens[a] == ADD) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++;}
	else if(tokens[a] == MULTIPLY) {
		tempPredicate.addToken(tokenVecCopy[a]);
		a++;}
	else throw a;
}