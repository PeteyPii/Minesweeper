#include "StreamInput.h"

#include <sstream>

using namespace std;

double getDouble(const std::string& prompt, std::istream& is, std::ostream& os)
{
	double returnValue;
	bool validInput = false;
	while(!validInput)
	{
		os << prompt;
		string isInput;
		is >> isInput;
		stringstream ss;
		ss << isInput;
		if(!(ss >> returnValue))
		{
			os << "Invalid input. Please enter a floating point number." << endl;
		}
		else
		{
			validInput = true;
		}
	}
	return returnValue;
}
int getInt(const string& prompt, istream& is, ostream& os)
{
	int returnValue;
	bool validInput = false;
	while(!validInput)
	{
		os << prompt;
		string isInput;
		is >> isInput;
		stringstream ss;
		ss << isInput;
		if(!(ss >> returnValue))
		{
			os << "Invalid input. Please enter an integer." << endl;
		}
		else
		{
			validInput = true;
		}
	}
	return returnValue;
}
unsigned int getUint(const string& prompt, istream& is, ostream& os)
{
	unsigned int returnValue;
	bool validInput = false;
	while(!validInput)
	{
		os << prompt;
		string isInput;
		is >> isInput;
		stringstream ss;
		ss << isInput;
		if(!(ss >> returnValue))
		{
			os << "Invalid input. Please enter non-negative integer." << endl;
		}
		else
		{
			validInput = true;
		}
	}
	return returnValue;
}
string getString(const string& prompt, istream& is, ostream& os, bool wholeLine)
{
	os << prompt;
	string returnValue;
	if(wholeLine)
		getline(is, returnValue);
	else
		is >> returnValue;
	return returnValue;
}
char getChar(const string& prompt, istream& is, ostream& os, bool caseSensitive)
{
	char returnValue;
	bool validInput = false;
	while(!validInput)
	{
		os << prompt;
		string isInput;
		is >> isInput;
		stringstream ss;
		ss << isInput;
		if(!(ss >> returnValue))
		{
			os << "Invalid input. Please enter a single character." << endl;
		}
		else
		{
			if(!caseSensitive && returnValue >= 65 && returnValue <= 90)	// case insensitive and a capital letter input
				returnValue += 32;

			validInput = true;
		}
	}
	return returnValue;
}