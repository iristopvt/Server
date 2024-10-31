#include "pch.h"
#include "AccountManager.h"
#include "UserManager.h"


AccountManager* AccountManager::_instance = nullptr;

void AccountManager::Login()
{
		/*std::lock_guard<std::mutex> lg(_mutex);*/

		WRITE_LOCK;


		// Login 성공, ,...?
		// -> 어떤 user인지 확인
		cout << "login 시도" << endl;
		this_thread::sleep_for(100ms);
		User* user = UserManager::GetInstance()->GetUser(10);

		// User 확인 성공 및 클라이언트에게 메세지

		return;
}
