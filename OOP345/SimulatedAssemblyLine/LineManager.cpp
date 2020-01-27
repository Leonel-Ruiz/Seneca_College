
// Name: Leonel Said Ruiz Navarrete
// Seneca Student ID: 104657184
// Seneca email:lruiz-navarrete
// Date of completion: November 19th, 2019.
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include "LineManager.h"

//Custom Constructor
LineManager::LineManager(const string& filename, vector<Task*>& addressTask, vector<CustomerOrder>& CustomerOobjFilled)
{
	//Class container containing all the references of the Task objects on the assembly
	//line receives the addresses of all the Task objects created for the assembly line
	AssemblyLine = addressTask;

	//Move customers order to be filled to class queue of customer orders to be filled.
	for (size_t i = 0; i < CustomerOobjFilled.size(); i++)
	{
		ToBeFilled.push_front(move(CustomerOobjFilled[i]));
		//The number of CustomerOrder objects the assembly line started with
		m_cntCustomerOrder++;
	}

	fstream file(filename);
	if (file) 
	{
		string record;
		while (getline(file, record))
		{
			bool more = true;
			size_t next_pos = 0;
			Utilities utilitiesObj;
			string name;

			name = utilitiesObj.extractToken(record, next_pos, more);
			for (size_t i = 0; i < addressTask.size(); i++)
			{
				if ((addressTask[i]->getName() == name) && (next_pos != 0))
				{
					name = utilitiesObj.extractToken(record, next_pos, more);
					for (size_t i2 = 0; i2 < addressTask.size(); i2++)
					{
						if (addressTask[i2]->getName() == name)
						{
							//Copy all the Task objects into the AssemblyLine container
							addressTask[i]->setNextTask(*AssemblyLine[i2]);
						}
					}
				}
			}
		}
	}
	else 
	{
		cout << "Error with file" << endl;
	}
}

//Function performs one cycle of operations on the assembly line 
bool LineManager::run(std::ostream& os)
{
	if (ToBeFilled.size())
	{
		//move the last CustomerOrder object onto the starting point of the AssemblyLine
		//Dereference of vector element
		*(AssemblyLine[4]) += move(ToBeFilled.back());
		//Removes last element from the container
		ToBeFilled.pop_back();
	}

	size_t i;
	//Loop through all tasks on the assembly line and run one cycle of the task's process
	for (i = 0; i < AssemblyLine.size(); i++)
	{
		AssemblyLine[i] -> runProcess(os);
	}

	//Loop through all tasks on the assembly line and move the CustomerOrder objects down the line
	for (i = 0; i < AssemblyLine.size(); i++) 
	{
		if (AssemblyLine[i]->moveTask()) 
		{
			CustomerOrder customerOobj;
			//completed orders should be moved into the Completed queue.
			if (AssemblyLine[i]->getCompleted(customerOobj))
			{
				Completed.push_back(move(customerOobj));

			}
		}
	}
	bool state = false;
	if (ToBeFilled.empty() && Completed.size() == m_cntCustomerOrder)
	{
		state = true;
	}
	return state;
}

//Displays all the orders that were completed
void LineManager::displayCompleted(std::ostream& os) const
{
	size_t i;
	for (i = 0; i < Completed.size(); i++)
	{
		if (Completed[i].getOrderFillState()) 
		{
			Completed[i].display(os);
		}
	}
}

//Validates each task on the assembly line
void LineManager::validateTasks() const
{
	size_t i;
	for (i = 0; i < AssemblyLine.size(); i++)
	{
		AssemblyLine[i] -> validate(cout);
	}
}