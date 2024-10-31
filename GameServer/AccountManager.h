#pragma once

struct Account
{
	//ID... 등등
};

class AccountManager
{
	USE_LOCK;
private:
	AccountManager() {}
	~AccountManager() {}

public:
	static void Create()
	{
		if (_instance == nullptr) _instance = new AccountManager();
	}
	static void Delete()
	{
		if (_instance == nullptr) delete _instance;
	}

	static AccountManager* GetInstance()
	{
		return _instance;
	}

	Account* GetAccount(int32 id)
	{
		WRITE_LOCK;

		return nullptr;
	}

	void Login();

private:
	//std::mutex _mutex; // 상호 예외적인
	static AccountManager* _instance;

};
