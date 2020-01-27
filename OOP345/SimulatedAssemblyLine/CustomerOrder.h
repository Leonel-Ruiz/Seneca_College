
// Name: Leonel Said Ruiz Navarrete
// Seneca Student ID: 104657184
// Seneca email:lruiz-navarrete
// Date of completion: November 19th, 2019.
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#include <stdlib.h>
#include "Item.h"
#include "Utilities.h"
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cstring>

using namespace std;
struct ItemInfo
{
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_fillState = false;

	ItemInfo(std::string src) : m_itemName(src) {};
};
//This class manages a single order on the assembly line and contains the following information:
class CustomerOrder
{
private:
	//Name of the customer(e.g., John)
	string m_name; 

	//Name of the product being assembled(e.g., Desktop, Laptop, etc)
	string m_product;

	//Count of the number of items for the customer's order
	unsigned int m_cntItem;
	
	//Dynamically allocated array of pointers.Each element of the array is a dynamically allocated 
	//object of type ItemInfo(see below).This is the resource that your class must manage.
	ItemInfo** m_lstItem; 

	//Maximum width of a field, used for display purposes

	 static size_t m_widthField; //static

public:
	//default constructor
	CustomerOrder();

	//a custom constructor
	CustomerOrder(string& singleRecord);

	//A CustomerOrder object should not allow copy operations.
	//Copy constructor should throw an exception if called
	CustomerOrder(CustomerOrder&) { throw "Error: No copy operations allowed"; };	
	//Copy operator= should be deleted.
	CustomerOrder& operator=(CustomerOrder&) = delete;

	//move constructor
	CustomerOrder(CustomerOrder&& obj)noexcept;

	//move assignment operator
	CustomerOrder& operator=(CustomerOrder&& obj)noexcept;

	//a destructor
	~CustomerOrder();

	//  returns the ItemInfo::m_fillState of the item specified as a parameter. If the item doesn't 
    //  exist in the order, return true. 
	bool getItemFillState(std::string) const;

	//returns true if all the items in the order have been filled; false otherwise
	bool getOrderFillState() const;

	//fills the item in the current order that corresponds to the item passed into the function 
	//(the parameter item represents what is available in the inventory).
	void fillItem(Item& item, std::ostream&);

	void display(std::ostream&) const;
};
