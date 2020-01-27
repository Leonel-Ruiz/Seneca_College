
// Name: Leonel Said Ruiz Navarrete
// Seneca Student ID: 104657184
// Seneca email:lruiz-navarrete
// Date of completion: November 19th, 2019.
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"

char Utilities::m_delimiter = ' ';
//Sets the field width of the current object to the value of the parameter
void Utilities::setFieldWidth(size_t parameter)
{
	m_widthField = parameter;
}

//returns the field width of the current object
size_t Utilities::getFieldWidth() const
{
	return m_widthField;
}

//extracts tokens from the first parameter
const std::string Utilities::extractToken(const string& str, size_t& next_pos, bool& more)
{
	size_t pos = str.find(getDelimiter(),next_pos);
	string temp = str.substr(next_pos, pos - next_pos);

	more = (temp != "") ? true : false;
	
	int count=0;
	try
	{
		if (temp.find(m_delimiter) == string::npos)
		{
			count++;
			if (count == 2)
			{
				throw "exception";
			}
		}
	}
	catch (...)
	{
		cout << "Two delimiters with no delimiters in between" << endl;
	}
	
	size_t len = strlen(temp.c_str());
	if (m_widthField < len)
	{
		m_widthField = len;
	}
	next_pos = pos + 1;
	return temp;
}

//static void setDelimiter(const char)
void Utilities::setDelimiter(const char character)
{
	m_delimiter = character;
}

//returns the delimiter character of the current object.
const char Utilities::getDelimiter() const
{
	return m_delimiter;
}