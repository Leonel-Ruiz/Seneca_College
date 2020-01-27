
// Name: Leonel Said Ruiz Navarrete
// Seneca Student ID: 104657184
// Seneca email:lruiz-navarrete
// Date of completion: November 19th, 2019.
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include "Utilities.h"
#include "Task.h"

class LineManager
{
private:
	//A container containing all the references of the Task objects on the assembly line
	std::vector<Task*> AssemblyLine; 

	//A queue of customer orders to be filled
	std::deque<CustomerOrder> ToBeFilled;

	//A queue of customer orders completed
	std::deque<CustomerOrder> Completed;

	//The number of CustomerOrder objects the assembly line started with.
	unsigned int m_cntCustomerOrder;

public:
	//Custom Constructor
	LineManager(const string& filename, vector<Task*>& addressTask, vector<CustomerOrder>& CustomerOobjFilled);

	//this function performs one cycle of operations on the assembly line 
	bool run(std::ostream& os);

	//Displays all the orders that were completed
	void displayCompleted(std::ostream&) const; 

	//Validates each task on the assembly line
	void validateTasks() const;
};