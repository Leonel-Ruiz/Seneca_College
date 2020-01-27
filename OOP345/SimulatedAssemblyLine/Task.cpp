
// Name: Leonel Said Ruiz Navarrete
// Seneca Student ID: 104657184
// Seneca email:lruiz-navarrete
// Date of completion: November 19th, 2019.
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Task.h"

//Custom Constructor:This string contains a single record (one line) from the input file it
//will also set the m_pNextTask to a safe state.
Task::Task(const string& singleRecord): Item(singleRecord)
{
	m_pNextTask = nullptr;
}

//Runs a single cycle of the assembly line for the current task.
void Task::runProcess(ostream& os)
{
	//If it is not empty
	if (!m_orders.empty())
	{
		//getOrderFillState returns true if all the items in the order have been filled
		//back() to return reference of last element
		if (!m_orders.back().getOrderFillState())//if it hasn't been filled
		{
			//Fills Item
			m_orders.back().fillItem(*this, os);
		}
	}
}

//Moves the last CustomerOrder in the queue to the next task on the assembly line 
bool Task::moveTask()
{
	bool state = false;
	//If order is not empty, if next task is not empty and If order state fill is true
	if (!m_orders.empty())
	{
		if ((m_pNextTask != nullptr) && (m_orders.back().getItemFillState(getName())))
		{
			//moves the last CustomerOrder in the queue to the next task on the assembly line
			*m_pNextTask += move(m_orders.back());
			m_orders.pop_back();
		}
		state = true;
	}
	return state;
}

//Stores the provided Task object's reference into the m_pNextTask pointer.
void Task::setNextTask(Task& taskObj)
{
	//If next task is not empty
	if (m_pNextTask != nullptr)
	{
		//Deallocates any memory
		delete m_pNextTask;	
	}
	//Assignes new reference
	m_pNextTask = &taskObj;
}

//Removes the last CustomerOrder from the queue, places it in the parameterand returns true.
//If the CustomerOrder queue is empty, return false.
bool Task::getCompleted(CustomerOrder& COobj)
{
	bool state = false;
	//Makes sure it is not empty
	if (!m_orders.empty() && m_orders.back().getOrderFillState())
	{
		//Places order into parameter
		COobj = move(m_orders.back());
		//Removes last order from the contain er
		m_orders.pop_back();
		//Sets state to true
		state = true;
	}
	return state;
}

//Writes the name of the Item this Task is responsible for into the parameter
void Task::validate(std::ostream& os)
{
	//If m_pNextTask exist:
	if (m_pNextTask != nullptr)
	{
		os << getName() << " --> " << m_pNextTask->getName() << endl;
	}
	else//If it does not exist
	{
		os << getName() << " --> " << "END OF LINE" << endl;
	}
}

//Moves the parameter onto the front of the CustomerOrder queue.
Task& Task::operator+=(CustomerOrder&& COobj)
{
	//adds element t before the first element in the container
	m_orders.push_front(move(COobj));
	return *this;
}