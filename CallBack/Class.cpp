#include <iostream>
#include <queue>
//#include <mutex>
//#include <condition_variable>

#include "Class.h"
#include "../DrawBoard/GlCirclePainter.h"
#include "../DrawBoard/BoardLocation.h"
#include "../Gl_wuziqi/migration/data_base/DataWuziqi.h"
#include "../Gl_wuziqi/migration/rule/rule.h"
#include "../Gl_wuziqi/migration/socket/GameSocketManager.h"

#include <glfw3.h>




using std::cout;
using std::endl;

extern class DataWuziqiSpecType dataWuziqiSpecType;
extern class GameSocketManager gameSocketManager;
extern GlCirclePainter* ptrChessWhitePainter;
extern bool myCharacter;
extern int chess_width;
extern GameSocketManager gameSocketManager;
//extern std::mutex m;
//extern std::condition_variable cv;
extern bool bReady;

struct SocketData;
extern std::queue<SocketData> chess_point_buffer;
extern std::queue<PointGl> SocketReceiveBuffer;

void handleClickInput_socket(double xpos, double ypos) {
	PointGl chessCoor;
	ptrBoardLoc->getChessPointGl(static_cast<int>(xpos), static_cast<int>(ypos), chessCoor);
	DataWuziqiSpecType::Point clickPoint(chessCoor.first, chessCoor.second);

	//add data to buffer to be analyzed
	SocketData temp{ clickPoint };
	chess_point_buffer.push(temp);
	if (chess_point_buffer.empty()) {
		return;
	}


	//dataBase
	dataWuziqiSpecType.insert(clickPoint, myCharacter);
	MapPoint* ptr_m_chesses = dataWuziqiSpecType.get();


	//drawe chess
	if (ptrChessWhitePainter != nullptr) {
		if (ptrChessWhitePainter != nullptr) {
			gameSocketManager.setBReceive(true);
			SocketReceiveBuffer.push(chessCoor);
			//std::unique_lock lk(m);

			//cv.wait(lk, [] {return bReady; });

			////ptrChessWhitePainter->addOne(ChessCoor, ptrBoardLoc->getWidth());

			//gameSocketManager.setBReceive(false);
			//bReady = false;
		}
	}

	//rule
	bool isWin = is_win(clickPoint, ptr_m_chesses, chess_width, myCharacter, true);
	cout << isWin << endl;
}

void handleClickInput(double xpos, double ypos) {
	PointGl ChessCoor;
	ptrBoardLoc->getChessPointGl(static_cast<int>(xpos), static_cast<int>(ypos), ChessCoor);
	DataWuziqiSpecType::Point clickPoint(ChessCoor.first, ChessCoor.second);

	//add data to socket buffer to be analyzed
	SocketData temp{ clickPoint };
	chess_point_buffer.push(temp);
	if (chess_point_buffer.empty()) {
		return;
	}


	//dataBase
	dataWuziqiSpecType.insert(clickPoint, myCharacter);
	MapPoint* ptr_m_chesses = dataWuziqiSpecType.get();


	//drawe chess
	if (ptrChessWhitePainter != nullptr) {
		ptrChessWhitePainter->addOne(ChessCoor, ptrBoardLoc->getWidth());
	}

	//rule
	bool isWin = is_win(clickPoint, ptr_m_chesses, chess_width, myCharacter, true);
	cout << isWin << endl;
}


void mouseClick_callback(GLFWwindow * window, int button, int xposIn, int yposIn)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
	int newState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (newState == GLFW_RELEASE) {
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
	}
}