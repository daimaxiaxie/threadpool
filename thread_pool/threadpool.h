#pragma once

#ifndef THREADPOOL_H
#define THREADPOOL_H

//#include "thread.h"
#include <stack>
#include <list>
#include <queue>

//extern class thread;
class thread;


class pool
{
public:
	pool();
	~pool();

	bool switchActive(thread *t);

private:

};


class threadpool
{
public:
	threadpool(int num);
	~threadpool();

	bool SwitchActive(thread *t);
	thread* PopIdleThread();
	task* GetTask();
	bool addTask(task *t, int priority);
	bool start();
	bool destroy();
	bool isEmpty();

private:
	int thread_num;
	std::stack<thread*> idleThread;
	std::list<thread*> activeThread;
	std::deque<task*> taskQueue;
};

#endif // !THREADPOOL_H