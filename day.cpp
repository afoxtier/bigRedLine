//day.cpp

#include "framework.h"
#include "day.h"
#include "task.h"


//constructs a Day object with all values set to nothing
Day::Day()
{
	month = 0;
	day = 0;
	year = 0;
	for (int i = 0; i < 24; i++)
	{
		tasks[i] = nullptr;
	}//for all members of tasks
	numTasks = 0;
} //default constructor()


//constructs a Day object and assigns a date but nothing to the tasks
Day::Day(int dateM, int dateD, int dateY)
{
	month = dateM;
	day = dateD;
	year = dateY;
	for (int i = 0; i < 24; i++)
	{
		tasks[i] = nullptr;
	}//for all members of tasks
	numTasks = 0;
} //constuctor()


//deconstructs a Day object
Day::~Day()
{
	//delete all tasks
	for (int i = 0; i < numTasks; i++)
	{
		delete tasks[i];
	}//for all tasks
} //deconstructor()



//overloads the assignment operator to copy one Day to another
Day& Day::operator=(const Day& dayArg)
{	
	//copy date
	month = dayArg.month;
	day = dayArg.month;
	year = dayArg.year;

	//remove any tasks in this day
	for (int i = 0; i < numTasks; i++)
	{
		delete tasks[i];
	} //for all tasks

	//create new copies of assigned tasks
	for (int i = 0; i < dayArg.numTasks; i++)
	{
		addTask(*(dayArg.tasks[i]));
	}//for all tasks to be copied

	return *this;
} //operator=()



//sets the date of a Day. returns false if not real date
bool Day::setDate(int dateM, int dateD, int dateY)
{
	//check if date is possible
	if (dateM > 12 || dateM < 1
		|| dateD > 31 || dateD < 1
		|| dateY > 30000 || dateY < 0)
	{
		return false;
	}

	//set new date
	month = dateM;
	day = dateD;
	year = dateY;

	return true;
} //setDate()


//Adds a task to the list of Day's Tasks and asigns it an ID. If error, return false.
bool Day::addTask(Task& task)
{
	if (numTasks <= 24)
	{
		//make new Task copy, set ID, and increment the number of tasks
		tasks[numTasks] = new Task(task);
		tasks[numTasks]->setID(numTasks);
		numTasks++;

		return true;
	} //if room for more tasks

	return false;
} //addTask()


//Removes a Task from the tasks and reorganizes tasks. If task not found, returns false.
bool Day::removeTask(int taskID)
{
	if (numTasks == 0 || taskID >= numTasks)
	{
		return false;
	} //if taskID is not in this day or no tasks to remove

	for (int i = taskID+1; i < numTasks - 1; i++)
	{
		tasks[i - 1] = tasks[i];
	}//for all Tasks with IDs higher than the removed task

	numTasks--; //decrement numTasks
	delete tasks[numTasks]; //delete the Task that is now an extra at the end of the list

	return true;
} //removeTask()


//Returns a string that details a particular Task
void Day::getTask(WCHAR* out, short taskID)
{
	tasks[taskID]->getWideStr(out);
	/*out.assign("Name: ");
	out.append(tasks[taskID]->getName().c_str());
	out.append(", ");
	out.append("Description:");
	out.append(tasks[taskID]->getDescription().c_str());
	out.append(", ");
	out.append("ID: ");
	out.append(std::to_string((int)tasks[taskID]->getID()));
	out.append(", ");
	out.append("Start Time: ");
	out.append(std::to_string((int)tasks[taskID]->getStartTime()));
	out.append(", ");
	out.append("End Time: ");
	out.append(std::to_string(tasks[taskID]->getEndTime()));
	out.append(", ");
	out.append("Is Complete: ");
	out.append(std::to_string(tasks[taskID]->isComplete()));
	out.append("\n");*/
}


//Returns month
short Day::getMonth()
{
	return month;
} //getMonth()


//Returns day
short Day::getDay()
{
	return day;
} //getDay


//Returns year
short Day::getYear()
{
	return year;
} //getYear()