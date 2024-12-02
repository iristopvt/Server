#include "pch.h"

// Socket 만들기
// - ipv6
// - port
// - protocol

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

#include "Service.h"
#include "BufferReader.h"
#include "BufferWriter.h"
#include "ClientPacketHandler.h"
struct Player
{
	int32 mesh;
	int32 material;

	int64 id;
	int32 hp;
	int16 atk;
};

class ServerSession : public PacketSession
{
public:
	ServerSession()
	{
	}

	~ServerSession()
	{
		cout << "Session DisConnected" << endl;
	}

	virtual void OnConnected() override
	{
		cout << "Server에 접속 성공!!!" << endl;

		//shared_ptr<SendBuffer> sendBuf = make_shared<SendBuffer>(100);
		//string temp = "Hello Server!! I'm Client";
		//sendBuf->CopyData((void*)temp.data(), temp.size());
		//Send(sendBuf);
	}

	virtual int32 OnRecvPacket(BYTE* buffer, int32 len) override
	{
		ClientPacketHandler::HandlePacket(buffer, len);

		return len;
	}

	virtual void OnSend(int32 len) override
	{
		cout << "Send 성공 : " << len << endl;
	}

	virtual void DisConnected() override
	{
		cout << "DisConnected" << endl;
	}
};

int main()
{
	this_thread::sleep_for(1s);

	CoreGlobal::Create();

	shared_ptr<ClientService> service = MakeShared<ClientService>
		(
			NetAddress(L"127.0.0.1", 7777),
			MakeShared<IocpCore>(),
			MakeShared<ServerSession>,
			1
		);

	service->Start();

	for (int i = 0; i < 2; i++)
	{
		TM_M->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}


	TM_M->Join();

	CoreGlobal::Delete();

	return 0;
}



	// 	 //we are question
	//		 //who? gatAI! 

	//WSAData wsaData;
	//if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	//	return 0;

	//SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	//if (clientSocket == INVALID_SOCKET)
	//{
	//	int32 errCode = ::WSAGetLastError();
	//	cout << "Socket ErroCode: " << errCode << endl;
	//	return 0;
	//}

	//u_long on = 1;
	//if (::ioctlsocket(clientSocket, FIONBIO, &on) == INVALID_SOCKET) // 논블로킹 소켓 만드는 함수
	//	return 0;

	//SOCKADDR_IN serverAddr;
	//::memset(&serverAddr, 0, sizeof(serverAddr));
	//serverAddr.sin_family = AF_INET;
	//::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	//serverAddr.sin_port = ::htons(7777);

	//this_thread::sleep_for(2s);

	//// Connect
	//while (true)
	//{
	//	auto connectValue = ::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	//	if (connectValue == SOCKET_ERROR)
	//	{
	//		// 블록상태였어야 했음(연결이 아직 되지 않았음)
	//		if (::WSAGetLastError() == WSAEWOULDBLOCK)
	//			continue;

	//		// 이미 연결되어있음
	//		if (::WSAGetLastError() == WSAEISCONN)
	//			break;

	//		// Error

	//		break;
	//	}
	//}

	//cout << "Connected to Server" << endl;

	//// - session -
	//char sendBuffer[100] = "Hello Server!";
	//// Overlapped
	//WSAEVENT wsaEvent = WSACreateEvent();
	//WSAOVERLAPPED overlapped = {};
	//overlapped.hEvent = wsaEvent;
	//// Recv
	//char recvBuffer[100] = "yo! ";

	////// Overlapped
	////WSAEVENT wsaEvent = WSACreateEvent();
	////WSAOVERLAPPED overlapped = {};
	////overlapped.hEvent = wsaEvent;

	//// Send
	//while (true)
	//{
	//	WSABUF wsaBuf;
	//	wsaBuf.buf = sendBuffer;
	//	wsaBuf.len = sizeof(sendBuffer);

	//	DWORD sendLen = 0;
	//	DWORD flags = 0;

	//	// send
	//	if (::WSASend(clientSocket, &wsaBuf, 1, &sendLen, flags, &overlapped, nullptr) == SOCKET_ERROR)
	//	{
	//		// WSARecv가실패

	//		if (::WSAGetLastError() == WSA_IO_PENDING)
	//		{
	//			// Pending :: 보류하고 나중에 확인
	//			::WSAWaitForMultipleEvents(1, &wsaEvent, TRUE, WSA_INFINITE, FALSE);
	//			::WSAGetOverlappedResult(clientSocket, &overlapped, &sendLen, FALSE, &flags);

	//		}
	//		else
	//		{
	//			// TODO : 문제가 있는 상황
	//			break;
	//		}
	//	}

	//	cout << "send Data! Len = " << sizeof(sendBuffer) << endl;
	//	
	//	// Recv
	//	// 과제? 
	//	//wsaBuf.buf = recvBuffer;
	//	//wsaBuf.len = sizeof(recvBuffer);

	//	//DWORD recvLen = 0;
	//	//
	//	//if (WSARecv(clientSocket, &wsaBuf,1,&recvLen,&flags, &overlapped,nullptr) == SOCKET_ERROR)
	//	//{
	//	//	if (::WSAGetLastError() == WSA_IO_PENDING)
	//	//	{
	//	//		::WSAWaitForMultipleEvents(1, &wsaEvent, TRUE, WSA_INFINITE, FALSE);
	//	//		::WSAGetOverlappedResult(clientSocket, &overlapped, &recvLen, FALSE, &flags);
	//	//	}
	//	//	else
	//	//	{
	//	//		// TODO : 문제가 있는 상황
	//	//		break;
	//	//	}

	//	//}
	//	//cout << "recv Data! Len = " << sizeof(recvBuffer) << endl;


	//	this_thread::sleep_for(1s);
	//}

	//::closesocket(clientSocket);
	//::WSACloseEvent(wsaEvent);
	//::WSACleanup();

	// 10/ 29
	//WSAData wsaData;
	//if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	//	return 0;

	//SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	//if (clientSocket == INVALID_SOCKET)
	//{
	//	int32 errCode = ::WSAGetLastError();
	//	cout << "Socket ErroCode: " << errCode << endl;
	//	return 0;
	//}

	//u_long on = 1;
	//if (::ioctlsocket(clientSocket, FIONBIO, &on) == INVALID_SOCKET) // 논블로킹 소켓 만드는 함수
	//	return 0;

	//SOCKADDR_IN serverAddr;
	//::memset(&serverAddr, 0, sizeof(serverAddr));
	//serverAddr.sin_family = AF_INET;
	//::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	//serverAddr.sin_port = ::htons(7777);

	//this_thread::sleep_for(2s);

	//// Connect
	//while (true)
	//{
	//	auto connectValue = ::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	//	if (connectValue == SOCKET_ERROR)
	//	{
	//		// 블록상태였어야 했음(연결이 아직 되지 않았음)
	//		if (::WSAGetLastError() == WSAEWOULDBLOCK)
	//			continue;

	//		// 이미 연결되어있음
	//		if (::WSAGetLastError() == WSAEISCONN)
	//			break;

	//		// Error

	//		break;
	//	}
	//}

	//cout << "Connected to Server" << endl;

	//char sendBuffer[100] = "
	// 
	// 
	// 
	// 
	// World!";

	//// Send
	//while (true)
	//{
	//	if (::send(clientSocket, sendBuffer, sizeof(sendBuffer), 0) == SOCKET_ERROR)
	//	{
	//		if (::WSAGetLastError() == WSAEWOULDBLOCK)
	//			continue;

	//		// Error
	//		break;
	//	}

	//	cout << "Send Data! Len = " << sizeof(sendBuffer) << endl;

	//	while (true)
	//	{
	//		char recvBuffer[1000];

	//		int32 recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
	//		if (recvLen == SOCKET_ERROR)
	//		{
	//			if (::WSAGetLastError() == WSAEWOULDBLOCK)
	//				continue;

	//			// Error
	//			break;
	//		}

	//		cout << "Recv Data Len = " << recvLen << endl;
	//		break;
	//	}

	//	this_thread::sleep_for(1s);
	//}

	//::closesocket(clientSocket);
	//::WSACleanup();


	//while (true)
	//{
	//	for (int i = 0; i < 10; i++)
	//	{
	//		char sendBuffer[100] = "Hello World!!";
	//		int32 sendCode = ::sendto(clientSocket, sendBuffer, sizeof(sendBuffer), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	//		if (sendCode == SOCKET_ERROR)
	//		{
	//			int32 errorCode = ::WSAGetLastError();
	//			cout << "Send ErrorCode : " << errorCode << endl;
	//			return 0;
	//		}
	//	}

	//	SOCKADDR_IN recvAddr;
	//	::memset(&recvAddr, 0, sizeof(recvAddr));
	//	int32 addrLen = sizeof(recvAddr);

	//	char recvBuffer[1000];

	//	// UDP
	//	// 1:1 연결이 아니라, 1: 다 연결 가능
	//	// listener가 없고 SeverSocket으로 나한테 정보를 보낸 것을 Recv한다.

	//	int32 recvLen = ::recvfrom(clientSocket, recvBuffer, sizeof(recvBuffer), 0, (SOCKADDR*)&recvAddr, &addrLen);
	//	if (recvLen <= 0)
	//	{
	//		int32 errCode = ::WSAGetLastError();
	//		cout << "Recv ErrorCode " << endl;
	//		return 0;
	//	}

	//	cout << "Recv Data : " << recvBuffer << endl;
	//	cout << "Recv Len : " << recvLen;

	//	this_thread::sleep_for(1s);
	//}

//	::closesocket(clientSocket);
//	::WSACleanup();
//}

//int main()
//{
//    // 원속 초기화(ws2_32 라이브러리 초기화)
//      //관련정보가 wsaData에 채워짐
//    WSAData wsaData;
//    if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//        return 0;
//
//    // 1. Client Socket 만들기 => 서버에 연결 시킬 Sck 만들기
//    SOCKET clientSocket = ::socket(AF_INET, SOCK_DGRAM, 0); // socket의 번호를 발급받음
//    if (clientSocket == INVALID_SOCKET)
//    {
//        int32 errCode = ::WSAGetLastError();
//        cout << "Socket ErroCode: " << errCode << endl;
//        return 0;
//    }
//
//    // 2. Server에 어디에 연결할지 (IP주소 + 포트번호 필요)
//    SOCKADDR_IN serverAddr; // IPv4
//    ::memset(&serverAddr, 0, sizeof(serverAddr)); // serverAddr 0으로 다 밀어버리기
//    serverAddr.sin_family = AF_INET; // IPv4로 연결하겠다는 것
//    ::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // 127.0.0.1 => Loop Back 주소 : 자기 PC의 주소 // 강사님꺼 : 192.168.0.9
//    serverAddr.sin_port = ::htons(7777); // 1 ~ 1000 여기는 건들면 안됨 (정해진 고유포트임)
//    int32 addrLen = sizeof(serverAddr);
//    // 네트워크 정수표현 => 빅엔디언 
//    // int aInt = 0x1234;  0x000000B45536FA14 34 12 00 00 4.... = 1234 저장될때 이렇게 저장된다..
//    // cpu에서 읽기 쉽게 저렇게 저장된다.
//    // 7777을 빅엔디언으로 저장해서 통합적으로 저장된다..
//
//    //    3. 연결
//    //if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
//    //{
//    //    int32 errCode = ::WSAGetLastError();
//    //    cout << "Connet ErrorCode : " << errCode << endl;
//    //    return 0;
//    //}
//
//    //cout << "Conneted To Server! " << endl;
//    // ----------------연결 성공 ---------------------
//
//    while (true)
//    {
//        //...... 서버데이터 들어온 것 분석, 혹은 클라이언트 코드 실행
//        for (int i = 0; i < 10; i++)
//        {
//            char sendBuffer[100] = "Hello World!!";
//            int32 sendCode = ::sendto(clientSocket, sendBuffer, sizeof(sendBuffer), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
//            if (sendCode == SOCKET_ERROR)
//            {
//                int32 errorCode = ::WSAGetLastError();
//                cout << "Send ErrorCode : " << errorCode << endl;
//                return 0;
//            }
//        }
//
//        // recv
//    
//        SOCKADDR_IN recvAddr;
//        ::memset(&recvAddr, 0, sizeof(recvAddr));
//        int32 addrLen = sizeof(recvAddr);
//
//
//        char recvBuffer[1000];
//
//        // UDP
//        // 1:1 연결이 아니라 1 : 다 연결 가능 
//        // listener 가 없고 ServerSocket으로 나한테 정보를 보낸 것을 Recv한다
//
//        int32 recvLen = ::recvfrom(clientSocket, recvBuffer, sizeof(recvBuffer), 0, (SOCKADDR*)&serverAddr, &addrLen);
//
//        if (recvLen <= 0)
//        {
//            int32 errCode = ::WSAGetLastError();
//            cout << "Recv ErrorCode " << endl;
//            return 0;
//        }
//
//        cout << "Recv Data : " << recvBuffer << endl;
//        cout << "Recv Len : " << recvLen;
//        
//
//        //    4. 소켓 리소스 반환 및 윈속 종료
//
//    }
//        ::closesocket(clientSocket);
//        ::WSACleanup();
//}
