#include "pch.h"
#include "CoreGlobal.h"

#include "ThreadManager.h"
#include "DeadLockProfiler.h"
#include "Memory.h"
#include "IocpCore.h"
#include "SocketUtility.h"
CoreGlobal* CoreGlobal::_instance = nullptr;

CoreGlobal::CoreGlobal()
{
	_threadManager = new ThreadManager();
	_deadLockProfinler = new DeadLockProfiler();
	_memory = new Memory();


	SocketUtility::Init();
}

CoreGlobal::~CoreGlobal()
{
	delete _threadManager;
	delete _deadLockProfinler;
	delete _memory;

	SocketUtility::Clear();
}

