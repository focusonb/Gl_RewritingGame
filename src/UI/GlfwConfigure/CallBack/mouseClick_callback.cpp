#include <iostream>
#include <queue>
//#include <mutex>
//#include <condition_variable>

#include "mouseClick_callback.h"
#include "../../DrawBoard/GlCirclePainter.h"
#include "../../DrawBoard/BoardLocation.h"
#include "../../../migration/data_base/DataWuziqi.h"
#include "../../../migration/rule/rule.h"
#include "../../../migration/socket/GameSocketManager.h"
#include "../../../Data/PlayerData.h"
#include <glfw3.h>




using std::cout;
using std::endl;

extern class DataWuziqiSpecType dataWuziqiSpecType;
extern class GameSocketManager gameSocketManager;
extern GlCirclePainter* ptrChessWhitePainter;
extern GlCirclePainter* ptrChessBlackPainter;

extern  volatile bool HasData;
extern std::condition_variable cv;
extern GameSocketManager gameSocketManager;
//extern std::mutex m;
//extern std::condition_variable cv;
extern bool bReady;

struct SocketData;
extern ChessPointBuffer chess_point_buffer;
extern std::queue<PointGl> SocketReceiveBuffer;

void addOneChessToBaord(PointGl chessCoor, bool myCharacter, GlSize width ) {
	if (myCharacter == false){
		ptrChessWhitePainter->addOne(chessCoor, width);
	}
	else {
		ptrChessBlackPainter->addOne(chessCoor, width);
	}
}

void handleClickInput_socket(double xpos, double ypos) {
	PlayerData::iniPlayerData(gameSocketManager);
	PointGl chessCoor;
	ptrBoardLoc->getChessPointGl(static_cast<int>(xpos), static_cast<int>(ypos), chessCoor);
	DataWuziqiSpecType::Point clickPoint(chessCoor.first, chessCoor.second);

	//add data to buffer to be analyzed
	SocketData temp{ clickPoint };
	chess_point_buffer.push(temp);


	//dataBase
	dataWuziqiSpecType.insert(clickPoint, !PlayerData::myCharacter);
	MapPoint* ptr_m_chesses = dataWuziqiSpecType.get();


	//drawe chess
	if (ptrChessWhitePainter != nullptr) {
		if (ptrChessWhitePainter != nullptr) {
			gameSocketManager.setBReceive(true);
			SocketReceiveBuffer.push(chessCoor);
		}
	}

	//rule
	HasData = true;
	cv.notify_one();
}

void handleClickInput(double xpos, double ypos) {
	
	PointGl ChessCoor;
	ptrBoardLoc->getChessPointGl(static_cast<int>(xpos), static_cast<int>(ypos), ChessCoor);
	DataWuziqiSpecType::Point clickPoint(ChessCoor.first, ChessCoor.second);

	//add data to socket buffer to be analyzed
	SocketData temp{ clickPoint };
	chess_point_buffer.push(temp);


	//dataBase
	dataWuziqiSpecType.insert(clickPoint, PlayerData::myCharacter);
	MapPoint* ptr_m_chesses = dataWuziqiSpecType.get();


	//drawe chess
	if (ptrChessWhitePainter != nullptr) {
		addOneChessToBaord(ChessCoor, PlayerData::myCharacter, ptrBoardLoc->getWidth());
	}

	//rule
	HasData = true;
	cv.notify_one();
}


void mouseClick_callback(GLFWwindow * window, int button, int xposIn, int yposIn)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
	int newState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (newState == GLFW_RELEASE) {
		return;
	}
	if (!PlayerData::bMyTurn) {
		cout << "its not my turn, please run another one as opponent." << endl;
		return;
	}
	//if (button == GLFW_MOUSE_BUTTON_LEFT) {
		int width;
		int	height;
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		glfwGetWindowSize(window, &width, &height);
		ypos = height - ypos;
		cout << xpos << " " << ypos << endl;

	
		//send data by socket
		std::string message_toopponent(std::to_string(static_cast<int>(xpos)) + 'a' + std::to_string(static_cast<int>(ypos)));
		gameSocketManager.sendStrData(message_toopponent);

		handleClickInput(xpos, ypos);
		PlayerData::bMyTurn = false;
	}
}