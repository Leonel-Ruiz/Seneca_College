
// Name: Leonel Said Ruiz Navarrete
// Seneca Student ID: 104657184
// Seneca email:lruiz-navarrete
// Date of completion: November 19th, 2019.
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#include "Utilities.h"

using namespace std;

//This class encapsulates the information about a given item on the assembly 
//line that can be filled within a customer order.
class Item
{
	//the name of the Item
	string m_name;

	//description of the item
	string m_description;

	//the next serial number to be assigned on the assembly line
	size_t m_serialNumber; 

	//the number of current items left in stock
	size_t m_quantity;

	//the maximum characters to be displayed for a field
	size_t m_widthField; 

public:
	//Custom constructor
	Item(const std::string& singleLine);

	//returns the name of the current Item object
	const std::string& getName() const;

	//returns the next serial number to be used on the assembly line and increments m_serialNumber
	const unsigned int getSerialNumber();

	//returns the remaining quantity of the current Item object
	const unsigned int getQuantity() const;

	// substracts 1 from the available quantity; should not go below 0
	void updateQuantity();

	//inserts the content of the current object into first parameter.
	void display(std::ostream& os, bool full) const;
};