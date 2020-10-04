//task.h outlines the task class
//by Aidan Fox-Tierney

#pragma once

#include "framework.h"
#include <string>

class Task
{
	std::string name;
	std::string description;
	short ID;
	//times are hours based on 24 hour clock
	short startTime;
	short endTime;
	bool complete;

public:
	Task();
	Task(std::string _name, std::string _description, short _ID, short _startTime, short _endTime);
	Task(Task& task);
	//~Task();
	Task& operator=(const Task& task);
	void setID(short newID);
	void setComplete(bool completion);
	bool setTime(short newStartTime, short newEndTime);
	std::string getName();
	std::string getDescription();
	short getID();
	short getStartTime();
	short getEndTime();
	bool isComplete();
	void getWideStr(WCHAR* wideSum);
};