#include "pch.h"
#include "threadpool.h"

pool::pool()
{
}

pool::~pool()
{
}

bool pool::switchActive(thread *t)
{
	return false;
}


threadpool::threadpool(int num):thread_num(num)
{
	while (num--)
	{
		thread *t = new thread(this);
		if (t->Start())
		{
			idleThread.push(t);
		}
		else
		{
			delete t;
			num++;
		}
	}
}


threadpool::~threadpool()
{
}

bool threadpool::SwitchActive(thread * t)
{
	if (!taskQueue.empty())
	{
		task *_task = taskQueue.front();
		taskQueue.pop_front();
		t->SetTask(_task);
		t->StartTask();
	}
	else
	{
		activeThread.remove(t);
		idleThread.push(t);
	}
	return true;
}

thread * threadpool::PopIdleThread()
{
	if (idleThread.empty())return nullptr;
	thread *t = idleThread.top();
	idleThread.pop();
	return t;
}

task * threadpool::GetTask()
{
	if (taskQueue.empty())
	{
		return nullptr;
	}
	task *t = taskQueue.front();
	taskQueue.pop_front();
	return t;
}

bool threadpool::addTask(task * t, int priority = 0)
{
	t->setPriority(priority);
	//PSA   but HRRN better
	if (taskQueue.empty())
	{
		taskQueue.push_back(t);
	}
	else if (taskQueue.front()->getPriority() < t->getPriority())
	{
		taskQueue.push_back(t);
	}
	else
	{
		taskQueue.push_front(t);
	}
	if (!idleThread.empty())
	{
		//task *_task = taskQueue.front();
		//taskQueue.pop_front();
		task *_task = GetTask();
		if (_task == nullptr)
		{
			return false;
		}
		thread *th = PopIdleThread();
		activeThread.push_back(th);
		th->SetTask(_task);
		th->StartTask();
	}
	return true;
}

bool threadpool::start()
{
	return true;
}

bool threadpool::destroy()
{
	/*
	for (auto t : taskQueue)
	{
		delete t;
	}*/
	taskQueue.clear();
	for (auto i : activeThread)
	{
		delete i;
	}
	activeThread.clear();
	while (!idleThread.empty())
	{
		thread *t = idleThread.top();
		idleThread.pop();
		t->Exit();
		t->Wakeup();
		t->isSafeExit();
		delete t;
	}
	return true;
}

bool threadpool::isEmpty()
{
	return activeThread.empty();
}
