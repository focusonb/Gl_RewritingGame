#include <mutex>
#include <condition_variable>

#include "GameSocketManager.h"
#include "../myfunction.h"
#include "../data_base/DataWuziqi.h"

using ChessPoint = ClickPoint;
using std::string;

GameSocketManager::GameSocketManager(DataWuziqiSpecType* dataWuziqiSpecType,void* ptr):
	m_dataWuziqiSpecType(dataWuziqiSpecType), m_ptr(ptr)
{
}


void GameSocketManager::reactToMessage(std::string msg)
{
	setBReceive(true);
	ChessPoint point_chess;
	split_a(msg, point_chess);

	//m_dataWuziqiSpecType->insert(point_chess, m_BRequestConnection);
	bool anotherSideColor = !m_BRequestConnection;
	handleInput ptr_handle = static_cast<handleInput>(m_ptr);
	double x = point_chess.x();
	double y = point_chess.y();

	ptr_handle(x, y);

	//emit recievedData(point_chess, anotherSideColor);
}

void GameSocketManager::sendStrData(std::string msgStr)
{
	memset(msg, 0, sizeof(msg));
	msgStr.copy(msg, msgStr.size(), 0);
	sendData();
	memset(msg, 0, sizeof(msg));
}