#pragma once


#include "IocpCore.h"
#include "IocpEvent.h"
class Service;
class Session : public IocpObject
{
public:
	Session();
	virtual ~Session();

public:

	// 정보관련
	shared_ptr<Service> GetService() { return _service.lock(); }
	void SetService(shared_ptr<Service> service);
	void SetNetAddress(NetAddress address) { _netAddress = address; }
	NetAddress GetAddress() { return _netAddress; }
	SOCKET	GetSocket() { return _socket; }
	// IocpObject을(를) 통해 상속됨, 순수가상함수 구현
	virtual HANDLE GetHandle() override;
	virtual void DisPatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) override;
	bool IsCOnnected() { return _connected; }
	shared_ptr<Session> GetSessionShared() { return static_pointer_cast<Session>(shared_from_this()); }


	// 전송 관련
	// -외부(Client,Server)에서 쓸 함수
	bool Connect();
	void Send(BYTE* buffer, int32 len);
	void DisConnect(const WCHAR* cause);

	bool RegisterConnect(); // 손님이 식탁에 앉기
	void RegisterRecv(); // 손님이 주는 메시지->  커널의 RecvBuffer -> 유저영역에 Session::recvBuffer에 복사 
	void RegisterSend(SendEvent* event); // 내가 손님한테 줄 메시지

	void ProcessConnect();
	void ProcessRecv(int32 numOfBytes);
	void ProcessSend(SendEvent* event,int32 numOfBytes);

	void HandleError(int32 errorCode);

	char _recvBuffer[1000] = {};
	char _sendBuffer[1000] = {};

protected:
	// ServerSession, ClientSession에서 필요한 경우 오버로딩
	virtual void OnConnected() {}
	virtual int32 OnRecv(BYTE* buffer, int32 len) { return len; }
	virtual void Onsend(int32 len) {}
	virtual void DisConnected() {}

private:
	weak_ptr<Service> _service;

	SOCKET _socket = INVALID_SOCKET;
	NetAddress _netAddress = {};
	
	Atomic<bool> _connected = false;

private:
	USE_LOCK;
	// 수신관련

	// 송싱관련
	RecvEvent _recvEvent;
};

