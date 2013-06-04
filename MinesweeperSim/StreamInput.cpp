#include "StreamInput.h"

#include <sstream>

using namespace std;

double getDouble(std::string prompt, std::istream& is, std::ostream& os)
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
int getInt(std::string prompt, std::istream& is, std::ostream& os)
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
unsigned int getUint(std::string prompt, std::istream& is, std::ostream& os)
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
std::string getString(std::string prompt, std::istream& is, std::ostream& os)
{
	return ;
}
char getChar(std::string prompt, std::istream& is, std::ostream& os, bool caseSensitive)
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
			if(!caseSensitive && (returnValue >= 65 || returnValue <= 90))	// case insensitive and a captial letter input
				returnValue += 32;

			validInput = true;
		}
	}
	return returnValue;
}