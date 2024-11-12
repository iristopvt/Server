#pragma once
#include "IocpCore.h"
#include "NetAddress.h"
#include "Service.h"
#include "IocpEvent.h"

class AccepctEvent;
// 역활 : 
// 클라이언트가 연결 시도(식당에 들어옴)
//  Accept한다 ( 몇명이서 오셨어요?)
class Listener : public IocpObject
{
public:
	Listener() = default;
	~Listener();

	bool StartAccept(shared_ptr<class ServerService> service);
	void CloseSocket();


	virtual HANDLE GetHandle() override;
	virtual void DisPatch(IocpEvent* iocpEvent, int32 numOfBytes) override;

	void RegisterAccept(AccepctEvent* acceptEvent);
	void ProcessAccept(AccepctEvent* acceptEvent);

	void OnAccept(shared_ptr<Session> session,IocpEvent* iocpEvent);

protected:
	SOCKET _socket = INVALID_SOCKET;
	Vector< AccepctEvent*> _acceptEvents;
	shared_ptr<class ServerService> _service;
};

