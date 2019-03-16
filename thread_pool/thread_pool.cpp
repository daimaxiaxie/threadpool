// thread_pool.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <Windows.h>

std::mutex lock;


class test:public task
{
public:
	test(int id):task(id)
	{
		
	}
	~test()
	{

	}

	virtual void run()
	{
		for (size_t i = 0; i < 10; i++)
		{
			int t = 0;
			for (size_t j = 0; j < 100; j++)
			{
				t++;
			}
			std::this_thread::sleep_for(std::chrono::microseconds(rand() % 100 * 10));
			lock.lock();
			std::cout << task::getID() << " : " << i << std::endl;
			lock.unlock();
		}
	}

private:

};


int main()
{
	threadpool p(5);
	test *t = nullptr;
	for (size_t i = 0; i < 7; i++)
	{
		t = new test(i);
		p.addTask(t, 7 - i);
	}
	t = new test(7);
	p.addTask(t, 7);
	while (!p.isEmpty())
	{
		Sleep(1000);
	}
	//delete all t;
	p.destroy();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
