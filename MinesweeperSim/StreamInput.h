#pragma once

#include <string>
#include <iostream>

double getDouble(std::string prompt, std::istream& is, std::ostream& os);
int getInt(std::string prompt, std::istream& is, std::ostream& os);
unsigned int getUint(std::string prompt, std::istream& is, std::ostream& os);
std::string getString(std::string prompt, std::istream& is, std::ostream& os);
char getChar(std::string prompt, std::istream& is, std::ostream& os, bool caseSensitive = true);	// if case insesitive, outputs lowercase
