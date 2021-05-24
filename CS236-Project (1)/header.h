#ifndef HEADER_H
#define HEADER_H
#pragma once

#include<vector>
#include<string>
#include<iostream>

class header {
public: 
header();
void addAttributes(const std::vector<std::string>&newAttributes);
std::vector<std::string>getAttributes();
std::vector<std::string>attributes; //TODO: maybe make this a private variable so only member functions can access it 
std::string toString();

unsigned int getNumAttributes(); //TODO: change the name of this function
std::string get_attribute(int i); //TODO: change the name of this function
};

#endif
