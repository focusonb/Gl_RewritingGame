#pragma once
#include <WinSock2.h>

using std::string;
//class string;

void ErrorHandling(const char* str);
void makeEvent(SOCKET&sock, WSAEVENT&event, int fd);
