#include "pch.h"
#include "Session.h"
#include "Service.h"


Session::Session()
{
    _socket = SocketUtility::CreateSocket();
}

Session::~Session()
{
    SocketUtility::Close(_socket);
}

void Session::SetService(shared_ptr<Service> service)
{
	_service = service;

	u_long on = 1;
	if (::ioctlsocket(_socket, FIONBIO, &on) == INVALID_SOCKET)
		return;

	_netAddress = service->GetNetAddress();

	//SocketUtility::Bind(_socket,_service.lock()->GetNetAddress());
}

HANDLE Session::GetHandle()
{
    return reinterpret_cast<HANDLE>(_socket);
}

void Session::DisPatch(IocpEvent* iocpEvent, int32 numOfBytes)
{
	EventType evecntType = iocpEvent->GetType();

	switch (evecntType)
	{
	case EventType::CONNECT:
	{
		ProcessConnect();
		break;
	}
	case EventType::RECV:
	{
		ProcessRecv(numOfBytes);
		break;
	}
	case EventType::SEND:
	{
		ProcessSend(static_cast<SendEvent*>(iocpEvent), numOfBytes);  
		break;
	}
	default:
		break;
	}
}

bool Session::Connect()
{
	// Connect
	while (true)
	{
		//NetAddress netAddress = session->GetAddress();
		if (::connect(GetSocket(), (SOCKADDR*)&_netAddress, sizeof(_netAddress)) == SOCKET_ERROR)
		{
			// 원래 블록했어야 했는데... 너가 논블로킹으로 하라며?
			if (::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			// 이미 연결된 상태라면 break
			if (::WSAGetLastError() == WSAEISCONN)
				return false;
			// Error
			return false;
		}
	}
	return true;

	return RegisterConnect(); // 값 반환 ?
	

}


void Session::Send(BYTE* buffer, int32 len)
{
	// TODO : scatter Gatherig

	SendEvent* sendEvent = xnew<SendEvent>();
	sendEvent->SetOwner(GetSessionShared());

	::memcpy(_sendBuffer, buffer, len);

	WRITE_LOCK;
	RegisterSend(sendEvent);
}

void Session::DisConnect(const WCHAR* cause)
{
	if (_connected.exchange(false) == false) // _connected가 애초에 false
	{
		return;
	}

	wcout << "DisConnected : " << cause << endl;

	// TODO : onDisConnected 오버라이딩
	SocketUtility::Close(_socket);
	GetService()->ReleaseSession(GetSessionShared()); // refCount -- 
}

bool Session::RegisterConnect()
{
	// TODO  : IOCP 기반 Connect 비동기, 멀티쓰레드 방식으로 Connect
	return false;
}

void Session::RegisterRecv()
{
	if (IsCOnnected() == false)
		return;

	_recvEvent.Init();
	_recvEvent.SetOwner(shared_from_this()); // event의 주인이 locpObject...session의 rsfCount + 1

	WSABUF wsabuf;
	wsabuf.buf = reinterpret_cast<char*>(_recvBuffer);
	wsabuf.len = len32(_recvBuffer);

	DWORD numOfBytes = 0;
	DWORD flags = 0;

	if (SOCKET_ERROR == ::WSARecv(_socket, &wsabuf, 1, OUT &numOfBytes, &flags, &_recvEvent, nullptr))
	{
		int32 errorCode = ::WSAGetLastError();

		if (errorCode != WSA_IO_PENDING)
		{
			HandleError(errorCode);
			_recvEvent.SetOwner(nullptr); // refCount -1 
		}
	}
}

void Session::RegisterSend(SendEvent* event)
{
	// TODO

	if (IsCOnnected() == false)
	{
		return;
	}

	WSABUF wsaBuf;
	wsaBuf.buf = _sendBuffer;
	wsaBuf.len = 1000; // TODO

	DWORD numOfBytes = 0;
	if (SOCKET_ERROR == ::WSASend(_socket, &wsaBuf, 1, OUT & numOfBytes, 0, event, nullptr))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING) 
		{
			HandleError(errorCode);
			_recvEvent.SetOwner(nullptr); 
			xdelete(event);
		}
	}
}

void Session::ProcessConnect()
{
	_connected.store(true);

	GetService()->AddSession(GetSessionShared());

	OnConnected();

	// 연결 됬으니까 수신하겠다.
	RegisterRecv();
}

// 쓰레드 단 하나만 
void Session::ProcessRecv(int32 numOfBytes)
{
	_recvEvent.SetOwner(nullptr); // session의 refCount -1

	if (numOfBytes == 0)
	{
		DisConnect(L"Recv : 0");
		return;
	}

	OnRecv(reinterpret_cast<BYTE*>(_recvBuffer), numOfBytes);

	// 새 수신 등록
	RegisterRecv();

}

void Session::ProcessSend(SendEvent* event, int32 numOfBytes)
{
	// TODO
	event->SetOwner(nullptr); // session Refcount --
	xdelete(event);

	if (numOfBytes == 0)
	{
		DisConnect(L"Send 0");
		return;
	}

	Onsend(numOfBytes);
}

void Session::HandleError(int32 errorCode)
{
	switch (errorCode)
	{
		case WSAECONNRESET:
		case WSAECONNABORTED:
		{
			DisConnect(L"Handler Error");
			break;
		}
	default:
		cout << "Handle Error : " << errorCode << endl;

		break;
	}
}
