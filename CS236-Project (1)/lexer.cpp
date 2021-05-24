//
// Created by Brendan on 1/23/2021.
//

#include "lexer.h"
#include "parser.h"

//logic of when to call token::getNextToken() should be in the lexer class

lexer::lexer(string& filename) {

    ifstream ifs(filename);
    string content((istreambuf_iterator<char>(ifs) ),(istreambuf_iterator<char>()));
    parse(content, 0);
} //constructor

lexer::~lexer() = default;

/**Algorithm for parse
 *
 * (WHEN A CHAR IS READ INTO A STRING, i IS INCREMENTED)
 *
 * For all of the contents of a file (given as a string)
 *  if there is whitespace skip it and i++
 *  if there is and end line, skip it and lineNum++
 *  if there is an open quote
 *      read the contents of the quote into a string until EOR or single quote is found
 *      if end line, lineNum++
 *  if there is a block comment indicator
 *      same as for the string except using end of comment indicator rather than single quote
 *  if there is a single line comment indicator
 *      read contents into a string until EOF is reach
 *      when EOF is reached, lineNum++
**/


void lexer::parse(string& contents, int newIndex) {
    string sendThis;
    unsigned int i = 0;
    while(i < contents.length()) {                                      //---FILE CONTENTS TO TOKENS---
        sendThis = "";                                                  //erase the contents of the sendThis string at every iteration
        if(contents[i] == '\n') {                                       //---END LINE---
            lineNum++;                                                  //increment lineNum+1
            i++;
        }
        else if(contents[i] == '\'') {                                  //----STRING----
            sendThis += contents[i];                                    //add initial single quote
            i++;
            lineVec.push_back(lineNum);                                 //add the linNum which will correspond to linNum of the final token
            while(true) {
				if(i == contents.length()) { break; }                		//-BREAK for EOF-
                else if(contents[i] == '\'' && contents[i+1] != '\'') {     //-SINGLE QUOTE FOLLOWED BY NON_SINGLE QUOTE-
                    sendThis += contents[i];                                //add closing single quote
                    i++;
                    break;                                                  //break out of the loop because string is done
                }
                else if(contents[i] == '\'' && contents[i+1] == '\'') {     //-TWO SINGLE QUOTES-
                    sendThis+= "\'\'";                                      //add to the string two single quote chars
                    i+=2;                                                   //increment i+=2 (we need to skip over the second single quote)
                }               
                else {                                                      //-DEFAULT CASE-
                    if(contents[i] == '\n') { lineNum++; }                  //if reaches an \n char, increment linNum
                    sendThis += contents[i];                                //add a char to the string
                    i++;
                }
            }
            sendVec.push_back(sendThis);                                //add sendThis string to the sendVec
        }
        else if(contents[i] == '#' && contents[i+1] == '|') {           //---BLOCK COMMENTS---
            sendThis+= "#|";                                            //add block comment indicator to the string
            i+=2;                                                       //increment i+2 (comment indicator is 2 chars long)
            lineVec.push_back(lineNum);                                 //add the linNum which will correspond to linNum of the final token
            while(true) {
				if(i == contents.length()) { break; }                		//-BREAK FOR EOF-
                else if(contents[i] == '|' && contents[i+1] == '#') {       //-END OF COMMENT INDICATOR-
                    sendThis += "|#";                                       //add end of comment indicator to string
                    i+=2;                                                   //i+=2 (end of comment indicator is 2 chars long)
                    break;                                                  //break out of loop because block comment is finished
                }
                else {                                                      //-DEFAULT CASE-
                    if(contents[i] == '\n') { lineNum++; }                  //if reaches an \n char, increment linNum
                    sendThis += contents[i];                                //else add next char to the string
                    i++;
                }
            }
            sendVec.push_back(sendThis);                                //add sendThis string to the sendVec
        }
        else if(contents[i] == '#') {                                   //---SINGLE LINE COMMENTS---
            sendThis += contents[i];                                    //add comment start indicator to the string
            i++;
            lineVec.push_back(lineNum);                                 //add the linNum which will correspond to linNum of the final token
            while(true) {
				if(i == contents.length()) { break; }                		//-BREAK FOR EOF-
                else if(contents[i] == '\n') {                              //-END LINE-
                    i++;
                    lineNum++;
                    break;                                                  //the comment is done
                }
				
                else {                                                      //-DEFAULT CASE-
                    sendThis += contents[i];                                //add next char to the string
                    i++;
                }
            }
            sendVec.push_back(sendThis);                                 //add sendThis string to the sendVec
        }
        else if(contents[i] == ' ' || contents[i] == '\t') { i++; }     //---WHITESPACE--- (ignore it)
        else if(contents[i] == ':' && contents[i+1] == '-') {           //---COLON DASH---
            lineVec.push_back(lineNum);                                 //add the linNum which will correspond to linNum of the final token
            sendVec.push_back(":-");                                    //add a colon dash to the sendVec
            i+=2;                                                       //increment i+=2 (colon dash is two chars long)
        }

        else if(isalpha(contents[i])) {                                 //---ID---
            lineVec.push_back(lineNum);                                 //add the linNum which will correspond to linNum of the final token
            while(isalpha(contents[i]) or isdigit(contents[i])) {      //add any number or letter to the string
                sendThis+= contents[i];
                i++;
            }
            sendVec.push_back(sendThis);                                //add sendThis string to the sendVec
        }
        else {                                                          //---SINGLE CHAR SYMBOLS---
            lineVec.push_back(lineNum);                                 //add the linNum which will correspond to linNum of the final token
            sendThis+= contents[i];                                     //add contents to the string
            sendVec.push_back(sendThis);                                //add sendThis string to the sendVec
            i++;
        }
    }

    for(unsigned int i = 0; i < sendVec.size(); i++) {                           //---CREATE VECTOR OF TOKENS---
        auto*temp = new tokenizer(sendVec[i], lineVec[i]);   			//send each string with it's corresponding lineNum to be tokenized
        tokenVec.push_back(temp->getNextToken());                       //add each new token to the tokenVec
    }
    string endFile;                                                     //---EOF TOKEN---
    auto* temp = new tokenizer(endFile, lineNum);                    	//send an empty string with the last lineNum
    tokenVec.push_back(temp->getNextToken());                           //will be read as an EOF token

    //for(auto & i : tokenVec) { cout << i.toString(); }                //print out all tokens in toString form
    //cout << "Total Tokens = " << tokenVec.size() << endl;             //print out total number of tokens

	vector<token>tokenVecNoComments;
	for(auto & i : tokenVec) {											//create a vector of tokens without the comment tokens because our parser does not need those
		if(i.tokenType != COMMENT) {tokenVecNoComments.push_back(i);}
	}

	new parser(tokenVecNoComments); 									//calls parser to parse through the vector of tokens
}