#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ServerPacketHandler.h"

GameSession::GameSession()
{

}

GameSession::~GameSession()
{
}

void GameSession::OnConnected()
{
	// 입장하면 입장해있던 모든 클라이언트들에게 입장했다고 방송고지

	// shared_ptr<SendBuffer> buf = make_shared<SendBuffer>(100);
	// string temp = "client entered!!!";
	// 
	// BYTE* buffer = buf->Buffer();
	// ((PacketHeader*)buffer)->id = 1; // id : 1 이면 Hello MSG
	// ((PacketHeader*)buffer)->size = (sizeof(temp) + sizeof(PacketHeader));
	// 
	// // sendBuffer의 writePos에 접근 불가
	// // ::memcpy(&buffer[4], temp.data(), sizeof(temp));
	// buf->CopyData_Packet((BYTE*)temp.data(), sizeof(temp));

	vector<BuffData> buffs;
	buffs.push_back({ 1,48.0f });
	buffs.push_back({ 2,2.0f });

	shared_ptr<SendBuffer> sendBuffer = ServerPacketHandler::Make_S_TEST(1234, 10, 5, buffs,L"Cherol");
	G_GameSessionManager->BroadCast(sendBuffer);

	G_GameSessionManager->Add(static_pointer_cast<GameSession>(shared_from_this()));
}


void GameSession::OnSend(int32 len)
{
	cout << "Send 성공 : " << len << endl;
}

int32 GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketHeader header = *((PacketHeader*)buffer);

	cout << "Paket ID : " << header.id << "  Size : " << header.size << endl;

	return len;
}

void GameSession::DisConnected()
{
	G_GameSessionManager->Remove(static_pointer_cast<GameSession>(shared_from_this()));
	cout << "DisConnected" << endl;
}