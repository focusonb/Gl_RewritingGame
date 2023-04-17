#pragma comment(lib, "Ws2_32.lib")

#include "SocketManager.h"
#include <string>
#include <iostream>

#include "CommonFunction.h"

using std::string;

SocketManager::SocketManager(ADDRESS_FAMILY sin_family, u_long address, const char* port, bool BRequestConnection):
	m_BRequestConnection(BRequestConnection)
{
	
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() error!");
	}
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = sin_family;
	//servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_addr.s_addr = htonl(address);
	//servAdr.sin_addr.s_addr = htonl(0x84a10068);
	servAdr.sin_port = htons(atoi(port));
	//(*((*((Threadarg_iswin*)arg)).semathree)).acquire();
}

void SocketManager::sendData()
{
	string msgStr(msg);
	send(hServSock, msg, sizeof(msg), 0);
}

void SocketManager::sendStrData(string msgStr)
{
	memset(msg, 0, msgStr.size());
	msgStr.copy(msg, msgStr.size(), 0);
	sendData();
	memset(msg, 0, msgStr.size());
}

void SocketManager::runRecieveLoop()
{
	prepareForWaitLoop();
	looprecvsend();
}

void SocketManager::prepareForWaitLoop()
{
	std::cout << "test" << std::endl;
	if (::connect(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) != SOCKET_ERROR)
	{
		setRequestConnectionState();
		newEvent = WSACreateEvent();
		makeEvent(hServSock, newEvent, FD_READ);
		//makeEvent(hServSock, newEvent, FD_ACCEPT);
		//makeEvent(hServSock, newEvent, FD_CONNECT_BIT);
		//do sth,i.e. send a fisrt message to server
		m_BEventMaked = true;
	}
	else
	{
		setWaitForConnectionState();
	}
}

void SocketManager::reactToMessage(std::string msg)
{
}

void SocketManager::looprecvsend()
{// loop and proccess evnets
	if (m_BRequestConnection == false)
	{
		SOCKET loopsock = socket(PF_INET, SOCK_STREAM, 0);
		memset(&loopAdr, 0, sizeof(loopAdr));
		loopAdr.sin_family = AF_INET;
		loopAdr.sin_addr.s_addr = htonl(INADDR_ANY);
		loopAdr.sin_port = htons(atoi("8198"));
		if (::bind(loopsock, (SOCKADDR*)&loopAdr, sizeof(loopAdr)) == SOCKET_ERROR)
		{
			ErrorHandling("bind error\n");
			return;
		}
		if (::listen(loopsock, 5) == SOCKET_ERROR)
		{
			ErrorHandling("listen error\n");
			return;
		}
		int clntAdrLen = sizeof(clntAdr);
		hServSock = ::accept(loopsock, (SOCKADDR*)&clntAdr, &clntAdrLen);
		if (hServSock == SOCKET_ERROR)
		{
			ErrorHandling("accept error\n");
			return;
		}
		std::cout << "accept a new connection request" << std::endl;

		//emit acceptConnection();

		newEvent = WSACreateEvent();
		makeEvent(hServSock, newEvent, FD_READ);
		//makeEvent(hServSock, newEvent, FD_ACCEPT);
		//makeEvent(hServSock, newEvent, FD_CONNECT_BIT);

		m_BEventMaked = true;
	}
	else {
		std::cout << "join a new connection" << std::endl;

		//emit joinConnection();
	}
	while (!isFinish)
	{
		WSAWaitForMultipleEvents(1, &newEvent, false, WSA_INFINITE, FALSE);
		WSAEnumNetworkEvents(hServSock, newEvent, &netevent);

		if (netevent.lNetworkEvents & FD_CONNECT_BIT) {
			std::cout << "accept a new connection request" << std::endl;
		}

		if (netevent.iErrorCode[FD_READ_BIT] != 0)
		{
			ErrorHandling("read error\n");
			break;
		}
		
		int size = sizeof(msg);
		memset(msg, 0, size);
		int strlen = recv(hServSock, msg, size, 0);
		std::string recstr(msg);
		reactToMessage(recstr);
	}
	closesocket(hServSock);
}

SOCKET & SocketManager::getsocket()
{
	return hServSock;
}

SOCKADDR_IN SocketManager::getClient()
{
	return clntAdr;
}

void SocketManager::TurnOffSocket() {
	isFinish = true;
}