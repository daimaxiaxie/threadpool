#include "pch.h"
#include "task.h"


task::task()
{
	id = 0;
	priority = 0;
}

task::task(int ID):id(ID)
{
	priority = 0;
}

task::task(int ID, int Priority):id(ID),priority(Priority)
{
}


task::~task()
{
}

void task::run()
{
}

int task::getID()
{
	return id;
}

void task::setID(int ID)
{
	id = ID;
}

void task::setPriority(int p)
{
	priority = p;
}

int task::getPriority()
{
	return priority;
}
