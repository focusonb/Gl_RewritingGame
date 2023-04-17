#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <string>
//#include <QObject>

class SocketManager
{

	//Q_OBJECT
	
protected:
	SOCKADDR_IN loopAdr, clntAdr, servAdr;
	WSADATA wsaData;
	SOCKET hServSock;
	WSAEVENT newEvent;
	WSANETWORKEVENTS netevent;
	char msg[100];
	bool stopwait = true;
	bool m_BEventMaked = false;
	bool isFinish = false;

protected:
	bool m_BRequestConnection = false;

//signals:
public:
	void acceptConnection() {};
	void joinConnection() {};
	void closeConnection() {
		closesocket(hServSock);
	}
//public slots:
public:
	void sendStrData(std::string msgStr);

public:
	SocketManager(ADDRESS_FAMILY sin_family = AF_INET,
		u_long address = 0x7f000001, 
		const char* port = "8198",
		bool BRequestConnection = true);

	void sendData();//input
	void runRecieveLoop();
	void prepareForWaitLoop();
	virtual void reactToMessage(std::string msg);//output
	void looprecvsend();
	inline bool getBEventMaked() const { return m_BEventMaked; }
	void TurnOffSocket();
private:
	SOCKET& getsocket();
	SOCKADDR_IN getClient();
	virtual void setRequestConnectionState() {}
	virtual void setWaitForConnectionState() {}
};