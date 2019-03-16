#pragma once
class task
{
public:
	task();
	task(int ID);
	task(int ID, int Priority);
	virtual ~task();

	virtual void run();
	int getID();
	void setID(int ID);
	void setPriority(int p);
	int getPriority();

private:
	int id;
	int priority;
};

