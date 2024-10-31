#include "pch.h"
#include "UserManager.h"
#include "AccountManager.h"

UserManager* UserManager::_instance = nullptr;

void UserManager::Save()
{
	// lock, atomic : All or Nothing
	WRITE_LOCK;

	// Acount 확인
	cout << "Save 시도" << endl;
	this_thread::sleep_for(100ms);


	Account* account = AccountManager::GetInstance()->GetAccount(10);

	// 계정정보 수정 혹은 저장
	// DB에 저장

	return;
}
