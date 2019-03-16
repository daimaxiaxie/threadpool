#include "pch.h"
#include "thread.h"

#include <iostream>

thread::thread(threadpool * p):p(p)
{
	t = nullptr;
	state = threadstate::RUNNABLE;
	isExit = false;
	id = 0;
	isThreadExit = false;
}

thread::~thread()
{
	isExit = true;
}

void thread::SetThreadState(threadstate state)
{
	this->state = state;
}

bool thread::SetTask(task * t)
{
	if (t == nullptr)
	{
		return false;
	}
	this->t = t;
	return true;
}

bool thread::Terminate(void)
{
	return false;
}

bool thread::Start()
{
	Thread=std::thread(&thread::ThreadFunction, this, this);
	Thread.detach();
	//std::thread::id id = Thread.get_id();
	return true;
}

void thread::Exit()
{
	isExit = true;
	state = TERMINATE;
}

bool thread::Wakeup()
{
	state = threadstate::RUNNING;
	cond.notify_one();
	return false;
}

bool thread::Suspend()
{
	
	return false;
}

bool thread::StartTask()
{
	return Wakeup();
}

threadstate thread::GetThreadState()
{
	return threadstate();
}


unsigned long thread::GetThreadID()
{
	return id;
}

void thread::SetThreadID(unsigned long id)
{
	this->id = id;
}

bool thread::SetPriority(int priority)
{
	this->priority = priority;
	return true;
}

int thread::GetPriority()
{
	return priority;
}

bool thread::isSafeExit()
{
	while (!isThreadExit)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(100));
	}
	return false;
}

void thread::ThreadFunction(void *t)
{
	thread *p = (thread *)t;
	std::mutex mtx;
	std::unique_lock<std::mutex> lck(mtx);
	while (!p->isExit)
	{
		
		while (p->state != RUNNING)
		{
			cond.wait(lck);
		}
		if (p->t != nullptr)
		{
			p->t->run();
			p->t = nullptr;
			p->p->SwitchActive(this);
		}
	}
	isThreadExit = true;
	return;
}
