//day.h defines the day class

#pragma once

#include "task.h"
#include <string>

class Day
{
	short month;
	short day;
	short year;
	Task* tasks[24];
	short numTasks;

public:
	Day();
	Day(int dateM, int dateD, int dateY);
	~Day();
	Day& operator=(const Day& dayArg);
	bool setDate(int dateM, int dateD, int dateY);
	bool addTask(Task& tsk);
	bool removeTask(int taskID);
	void getTask(WCHAR* out, short taskID);
	short getMonth();
	short getDay();
	short getYear();

};