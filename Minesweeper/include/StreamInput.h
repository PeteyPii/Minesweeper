#pragma once

#include <string>
#include <iostream>

// function to get a floating point number from a input stream
// return: the input floating point number
// prompt: what to output to the output stream to prompt for input
// is: stream that the input is coming from
// os: stream that outputs the prompt for the input
double getDouble(const std::string& prompt, std::istream& is, std::ostream& os);

// function to get a signed integer from a input stream
// return: the input signed integer
// prompt: what to output to the output stream to prompt for input
// is: stream that the input is coming from
// os: stream that outputs the prompt for the input
int getInt(const std::string& prompt, std::istream& is, std::ostream& os);

// function to get an unsigned integer from a input stream
// return: the input unsigned integer
// prompt: what to output to the output stream to prompt for input
// is: stream that the input is coming from
// os: stream that outputs the prompt for the input
unsigned int getUint(const std::string& prompt, std::istream& is, std::ostream& os);

// function to get a string from a input stream
// return: the input string
// prompt: what to output to the output stream to prompt for input
// is: stream that the input is coming from
// os: stream that outputs the prompt for the input
std::string getString(const std::string& prompt, std::istream& is, std::ostream& os, bool wholeLine = false);

// function to get a character from a input stream
// return: the input character
// prompt: what to output to the output stream to prompt for input
// is: stream that the input is coming from
// os: stream that outputs the prompt for the input
char getChar(const std::string& prompt, std::istream& is, std::ostream& os, bool caseSensitive = true);	// if case insensitive, outputs lowercase
