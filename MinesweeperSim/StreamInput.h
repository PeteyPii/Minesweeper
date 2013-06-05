#pragma once

#include <string>
#include <iostream>

double getDouble(const std::string& prompt, std::istream& is, std::ostream& os);
int getInt(const std::string& prompt, std::istream& is, std::ostream& os);
unsigned int getUint(const std::string& prompt, std::istream& is, std::ostream& os);
std::string getString(const std::string& prompt, std::istream& is, std::ostream& os, bool wholeLine = false);
char getChar(const std::string& prompt, std::istream& is, std::ostream& os, bool caseSensitive = true);	// if case insensitive, outputs lowercase
