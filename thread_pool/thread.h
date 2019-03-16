#pragma once

#ifndef THREAD_H
#define THREAD_H

#include <thread>
#include <condition_variable>
#include <atomic>
#include "task.h"
#include "threadpool.h"

enum threadstate
{
	RUNNABLE,
	RUNNING,
	SUSPEND,
	TERMINATE
};

class thread
{
public:
	thread(threadpool *p);
	virtual ~thread();

	void SetThreadState(threadstate state);
	bool SetTask(task *t);
	bool Terminate(void);
	bool Start();
	void Exit();
	bool Wakeup();
	bool Suspend();
	bool StartTask();

	threadstate GetThreadState();

	unsigned long GetThreadID();
	void SetThreadID(unsigned long id);
	bool SetPriority(int priority);
	int GetPriority();
	bool isSafeExit();

protected:
	void ThreadFunction(void*);

private:
	unsigned long id;
	threadpool *p;
	threadstate state;
	task *t;
	int priority;
	std::thread Thread;
	std::condition_variable cond;
	std::atomic_bool isExit;
	std::atomic_bool isThreadExit;
};


#endif // !THREAD_H