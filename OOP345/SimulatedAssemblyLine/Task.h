
// Name: Leonel Said Ruiz Navarrete
// Seneca Student ID: 104657184
// Seneca email:lruiz-navarrete
// Date of completion: November 19th, 2019.
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#include <iostream>
#include <deque>
#include "Item.h"
#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;

class Task : public Item
{
private:
	//is a double ended queue with new CustomerOrders coming in one sideand exiting out the other once 
	//filled.
	deque<CustomerOrder> m_orders;

	//a pointer to the next task on the assembly line
	Task* m_pNextTask = nullptr;

public:

	//Custom Constructor:This string contains a single record (one line) from the input file it
	//will also set the m_pNextTask to a safe state.
	Task(const string& singleRecord);

	//A Task object cannot be copied or moved - Implicit Avoidance
	Task(Task&) = delete;            //Copy Constructor
	Task& operator=(Task&) = delete; //Copy Assignment Operator
	Task(Task&&) = delete;           //Move Copy constructor
	Task& operator=(Task&&) = delete;//Move Copy Assignment Operator

	//Runs a single cycle of the assembly line for the current task.
	void runProcess(ostream& os); 

	//Moves the last CustomerOrder in the queue to the next task on the assembly line 
	bool moveTask();

	//Stores the provided Task object's reference into the m_pNextTask pointer.
	void setNextTask(Task& taskObj);

	//Removes the last CustomerOrder from the queue, places it in the parameterand returns true.
	//If the CustomerOrder queue is empty, return false.
	bool getCompleted(CustomerOrder& COobj);

	//Writes the name of the Item this Task is responsible for into the parameter
	void validate(std::ostream& os);

	//Moves the parameter onto the front of the CustomerOrder queue.
	Task& operator+=(CustomerOrder&& COobj); 
};