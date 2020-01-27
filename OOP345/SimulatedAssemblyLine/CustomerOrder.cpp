
// Name: Leonel Said Ruiz Navarrete
// Seneca Student ID: 104657184
// Seneca email:lruiz-navarrete
// Date of completion: November 19th, 2019.
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include "CustomerOrder.h"

size_t CustomerOrder::m_widthField = 0;
//default constructor
CustomerOrder::CustomerOrder()
{
	m_name = "";
	m_product = "";
	m_cntItem = 0;
	m_lstItem = nullptr;
}

//a custom constructor
CustomerOrder::CustomerOrder(string& singleRecord) 
{
	Utilities UtilityObj;
	bool more = true;
	size_t pos = 0;
	
	m_name = UtilityObj.extractToken(singleRecord, pos, more);
	m_product = UtilityObj.extractToken(singleRecord, pos, more);
	m_cntItem = count(singleRecord.begin(), singleRecord.end(), UtilityObj.getDelimiter()) - 1;

	m_lstItem = new ItemInfo * [m_cntItem];
	for (size_t i = 0; i < m_cntItem; i++)
	{
		m_lstItem[i] = new ItemInfo(UtilityObj.extractToken(singleRecord, pos, more));
	}

	if (CustomerOrder::m_widthField < UtilityObj.getFieldWidth())
	{
		CustomerOrder::m_widthField = UtilityObj.getFieldWidth();
	}
}

//move constructor
CustomerOrder::CustomerOrder(CustomerOrder&& obj) noexcept
{/*
	*this = move(obj);*/
	m_lstItem = nullptr;
	*this = std::move(obj);
}

//move assignment operator
CustomerOrder& CustomerOrder::operator=(CustomerOrder&& obj)  noexcept
{
	// If we're not trying to move the object into itself...
	if (this != &obj)
	{
		// Delete the original data
		delete[] m_lstItem;

		// Copy the other obj's data into this obj.
		m_name = obj.m_name;
		m_product = obj.m_product;
		m_lstItem = obj.m_lstItem;
		m_cntItem = obj.m_cntItem;

		// Finally, reset the other obj's data.
		obj.m_name = "";
		obj.m_product = "";
		obj.m_lstItem = nullptr;
		obj.m_cntItem = 0;
	}

	return *this;
}

//a destructor
CustomerOrder::~CustomerOrder()
{
	delete[] m_lstItem;
}

//  returns the ItemInfo::m_fillState of the item specified as a parameter. If the item doesn't 
//  exist in the order, return true. 
bool CustomerOrder::getItemFillState(std::string string) const
{
	bool state = true;
	size_t i;
	for (i = 0; i < m_cntItem; i++) 
	{
		if (m_lstItem[i]->m_itemName.compare(string) == 0)
		{
			state = m_lstItem[i]->m_fillState;
		}
	}
	return state;
}

//returns true if all the items in the order have been filled; false otherwise
bool CustomerOrder::getOrderFillState() const
{
	bool state = true;
	for (size_t i = 0; i < m_cntItem; i++)
	{
		if (m_lstItem[i]->m_fillState == false)
		{
			state = false;
		}
	}
	return state;
}

//fills the item in the current order that corresponds to the item passed into the function 
//(the parameter item represents what is available in the inventory).
void CustomerOrder::fillItem(Item& item, std::ostream& os)
{
	for (size_t i = 0; i < m_cntItem; i++)
	{
		//if item is found
		if (m_lstItem[i] -> m_itemName.compare(item.getName()) == 0)
		{
			//if the inventory contains at least one element
			if (item.getQuantity() > 0)
			{
				//substracts 1 from the inventory
				item.updateQuantity();

				//updates ItemInfo::m_serialNumber and ItemInfo::m_fillState
				m_lstItem[i]->m_serialNumber = item.getSerialNumber();
				m_lstItem[i]->m_fillState = true;

				//prints the message Filled NAME, PRODUCT[ITEM_NAME].
				os << "Filled " << m_name << ", " << m_product << '[' << item.getName() << ']' << endl;
			}
			else //if the inventory is empty,
			{
				// prints the message Unable to fill NAME, PRODUCT[ITEM_NAME].
				os << "Unable to fill " << m_name << ", " << m_product << '[' << item.getName() << ']' << endl;
			}
		}
	}
}

void CustomerOrder::display(std::ostream& os) const//os
{
	os << m_name << " - " << m_product << endl;
	for (size_t i = 0; i < m_cntItem; i++) 
	{

		os << "[" << setfill('0') << right << setw(6) << m_lstItem[i]->m_serialNumber << "] " << setw(m_widthField) << setfill(' ') << left
		   << m_lstItem[i]->m_itemName << " - " << (m_lstItem[i]->m_fillState ? "FILLED" : "MISSING") << endl;
	}
}