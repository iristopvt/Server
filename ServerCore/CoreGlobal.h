#pragma once
class ThreadManager;
class DeadLockProfiler;
class Memory;

class CoreGlobal
{
private:
	CoreGlobal();
	~CoreGlobal();

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new CoreGlobal();
	}

	static void Delete()
	{
		if (_instance != nullptr)
		{
			delete _instance;
			_instance = nullptr;
		}
	}

	static CoreGlobal* Instance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}

	ThreadManager* GetThreadManager() { return _threadManager; }
	DeadLockProfiler* GetDeadLockProfiler() { return _deadLockProfinler; }
	Memory* GetMemory() { return _memory; }
private:
	static CoreGlobal* _instance;

	class ThreadManager*	_threadManager;
	DeadLockProfiler*		_deadLockProfinler;
	Memory* _memory;
};

