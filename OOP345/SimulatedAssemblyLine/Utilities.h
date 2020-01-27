
// Name: Leonel Said Ruiz Navarrete
// Seneca Student ID: 104657184
// Seneca email:lruiz-navarrete
// Date of completion: November 19th, 2019.
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

//This class is used to support the parsing of input files to setup and 
//configure the assembly line simulation.
class Utilities
{
	//specifies the length of the token extracted
	size_t m_widthField = 1;

	//separates the tokens from a given std::string
	static char m_delimiter;

public:
	//Sets the field width of the current object to the value of the parameter
	void setFieldWidth(size_t parameter);

	//returns the field width of the current object
	size_t getFieldWidth() const;

	//extracts tokens from the first parameter
	const std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

	//static void setDelimiter(const char)
	static void setDelimiter(const char character);

	//returns the delimiter character of the current object.
	const char getDelimiter() const;
};