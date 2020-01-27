
// Name: Leonel Said Ruiz Navarrete
// Seneca Student ID: 104657184
// Seneca email:lruiz-navarrete
// Date of completion: November 19th, 2019.
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Item.h"


//Custom constructor
Item::Item(const std::string& singleLine)
{
	Utilities UtilitiesObj;
	bool more = true;
	size_t pos = 0;

	m_name = UtilitiesObj.extractToken(singleLine, pos, more);
	m_serialNumber = stoi(UtilitiesObj.extractToken(singleLine, pos, more));
	m_quantity = stoi(UtilitiesObj.extractToken(singleLine, pos, more));
	m_description = UtilitiesObj.extractToken(singleLine, pos, more);


	if (UtilitiesObj.getFieldWidth() > m_widthField)
	{
		m_widthField = UtilitiesObj.getFieldWidth();
	}
}

//returns the name of the current Item object
const std::string& Item::getName() const
{
	return m_name;
}

//returns the next serial number to be used on the assembly line and increments m_serialNumber
const unsigned int Item::getSerialNumber()
{
	size_t next = m_serialNumber;
	m_serialNumber++;
	return next;
}

//returns the remaining quantity of the current Item object
const unsigned int Item::getQuantity() const
{
	return m_quantity;
}

// substracts 1 from the available quantity; should not go below 0
void Item::updateQuantity()
{
	if (getQuantity() > 0)
	{
		m_quantity -= 1;
	}
}

void Item::display(std::ostream& os, bool full) const
{
	os << std::setw(13) << std::left << std::fixed << getName();
	string temp = to_string(m_serialNumber);
	if (temp.length() < 6)
	{
		os << "[0" << m_serialNumber << "]";
	}
	else
	{
		os << "[" << m_serialNumber << "]";
	}
	if (full)
	{
		os << " Quantity: " << std::setw(13) << std::left << std::fixed << getQuantity() << "Description: " << m_description;
	}
	os << std::endl;
}
