//task.cpp defines the methods of Task
//by Aidan Fox-Tierney

#include "task.h"
#include "framework.h"
#include <string>

//Construct a Task with values to indicate that no Task has been set yet
Task::Task()
{
	name.assign("No Name");
	description.assign("No Description");
	ID = -1;
	startTime = -1;
	endTime = -1;
	complete = false;
} //default constructor()


//Construct a Task with given values
Task::Task(std::string _name, std::string _description, short _ID, short _startTime, short _endTime)
{
	name.assign(_name);
	description.assign(_description);
	ID = _ID;
	startTime = _startTime;
	endTime = _endTime;
	complete = false;
} //constructor from values()


//Construct a Task from another Task
Task::Task(Task& task)
{
	name.assign(task.name);
	description.assign(task.description);
	ID = task.ID;
	startTime = task.startTime;
	endTime = task.endTime;
	complete = task.complete;
} //constructor from Task

/*
//default destructor
Task::~Task()
{
	//I'm not sure if this is necessary, but I know that dynamically allocated char* need to be deleted
	delete name;
	delete desctiption;
} //destructor()
*/

//Overlodes the assignment operator to copy one Task to another
Task& Task::operator=(const Task& task)
{
	name.assign(task.name);
	description.assign(task.description);
	ID = task.ID;
	startTime = task.startTime;
	endTime = task.endTime;
	complete = task.complete;

	return *this;
} //operator=()


//Sets the ID of Task to new ID
void Task::setID(short newID)
{
	ID = newID;
}//setID()


//Sets the complete status to true or false
void Task::setComplete(bool completion)
{
	complete = completion;
}//setComplete


//Sets time to a new time returns false if invalid time
bool Task::setTime(short newStartTime, short newEndTime)
{
	if (newStartTime < newEndTime)
	{
		startTime = newStartTime;
		endTime = newEndTime;

		return true;
	} //if new times valid

	return false;
}//setTime()


//Returns name string
std::string Task::getName()
{
	return name;
} //getName()


//Returns description string
std::string Task::getDescription()
{
	return description;
} //getDescription()


//Returns ID short
short Task::getID()
{
	return ID;
} //getID()


//Returns startTime short
short Task::getStartTime()
{
	return startTime;
} //getStartTime()


//Returns endTime short
short Task::getEndTime()
{
	return endTime;
} //getEndTime()


//Returns completion state bool
bool Task::isComplete()
{
	return complete;
} //isComplete()


//Converts Task into summery in wide UNICODE string form
void Task::getWideStr(WCHAR* wideSum)
{
	std::string taskBuffer;
	//format output string
	taskBuffer.assign("Name: ");
	taskBuffer.append(name);
	taskBuffer.append(", ");
	taskBuffer.append("Description:");
	taskBuffer.append(description);
	taskBuffer.append(", ");
	taskBuffer.append("ID: ");
	taskBuffer.append(std::to_string(ID));
	taskBuffer.append(", ");
	taskBuffer.append("Start Time: ");
	taskBuffer.append(std::to_string(startTime));
	taskBuffer.append(", ");
	taskBuffer.append("End Time: ");
	taskBuffer.append(std::to_string(endTime));
	taskBuffer.append(", ");
	taskBuffer.append("Is Complete: ");
	taskBuffer.append(std::to_string(complete));
	taskBuffer.append("\n");

	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wideSum, strlen(taskBuffer.c_str()), taskBuffer.c_str(), _TRUNCATE);
}//getWideStr