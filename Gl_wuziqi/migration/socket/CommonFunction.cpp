
#include <stdio.h>
#include <string>

#include "CommonFunction.h"

void ErrorHandling(const char* str)
{
	fputs(str, stderr);
	fputc('\n', stderr);
	exit(1);
}

void makeEvent(SOCKET & sock, WSAEVENT & event, int fd)
{
	if (WSAEventSelect(sock, event, fd) == SOCKET_ERROR)
	{
		const char* str = "WSAEventSelect error";
		ErrorHandling(str);
	}
}
