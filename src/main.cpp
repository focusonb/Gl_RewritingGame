//#include <wglew.h>
#ifdef _DEBUG
#pragma comment(lib, "glfw3d.lib")
#else
#pragma comment(lib, "glfw3.lib")
#endif
#pragma comment(lib, "opengl32.lib")
#include "migration\socket\GameSocketManager.h"
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Windows.h>
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

#include "UI/ShaderReader/FIleManager/FileManagerControler.h"
#include "UI/ShaderReader/MyShader.h"



#include "UI/TextureManager/TextureManager.h"
#include "UI/GlfwConfigure/GlfwConfigure.h"
#include "UI/DrawBoard/glSquarePainter.h"
#include "UI/DrawBoard/GlCirclePainter.h"


#include "migration\data_base\DataWuziqi.h"
#include "migration\rule\rule.h"
#include "Data/PlayerData.h"

using std::cout;
using std::endl;

const int CHESS_WIDTH = 50;


GlCirclePainter* ptrChessWhitePainter = nullptr;
GlCirclePainter* ptrChessBlackPainter = nullptr;
BoardLocation* ptrBoardLoc = nullptr;


std::mutex m;
std::condition_variable cv;

//buffer for communication of  socket thread, rule thread and UI thread.
ChessPointBuffer chess_point_buffer;
std::mutex ChessPointBuffer::m;

//buffer for communication of socket thread and UI thread.
std::queue<PointGl> SocketReceiveBuffer;

//data for saving history of chess.
DataWuziqiSpecType dataWuziqiSpecType;


volatile bool HasData = true;
static std::thread* thread_socket = nullptr;
static std::thread* thread_rule = nullptr;


GameSocketManager gameSocketManager(&dataWuziqiSpecType, handleClickInput_socket);



std::thread* startSocketThread(GameSocketManager* gameSocketManager)
{
	if (gameSocketManager->getBEventMaked() == true) {
		return nullptr;
	}
	gameSocketManager->prepareForWaitLoop();
	std::thread* thread = new std::thread(&GameSocketManager::looprecvsend, gameSocketManager);

	//there may be a problem, that is when function getBRequestConnection() execute, the task of setting value has
	// not been done.
	bool myCharacter = gameSocketManager->getBRequestConnection();
	if (myCharacter == true) {
		//show message box telling seccess of matching a existing player.
		cout << "match one opponent" << endl;
	}
	else {
		cout << "waiting for one opponent" << endl;
	}
	return thread;
}

void worker_rule() {
	//analyze a queue of data.
	while (1) {
		if (chess_point_buffer.empty()) {
			//what if here release a mutex.
			std::unique_lock<std::mutex> lk(m);
			HasData = false;
			cv.wait(lk, [] {return HasData; });
		}
		else {
			while (!chess_point_buffer.empty())
			{
				SocketData& socket_data = chess_point_buffer.front();
				if (is_win(socket_data.point_chess, dataWuziqiSpecType.get(), CHESS_WIDTH, PlayerData::myCharacter, true)) {
					//
					cout << "win" << endl;
				}
				else {

				}
				chess_point_buffer.pop();
			}
		}
	}
}

std::thread* startRuleThread() {
	std::thread* thread = new std::thread(worker_rule);
	return thread;
}

int main()
{

	thread_socket = startSocketThread(&gameSocketManager);
	thread_rule = startRuleThread();

	PlayerData::iniPlayerData(gameSocketManager);

	std::thread boardLoopRender([&]() {
		GlfwConfigure* myConfig = GlfwConfigure::getInstance();
		GLFWwindow* window = myConfig->getGlfWindowHandle();

		BoardLocation boardLoc(WINDOWS_WIDTH, WINDOWS_HEIGHT, 16, 16);
		int width = boardLoc.getWidth();
		BoardLocation::MapLoca mapLoca = boardLoc.getAllPoint();
		ptrBoardLoc = &boardLoc;

		GlCirclePainter chessWhitePainter(CorlorChess::white);
		GlCirclePainter chessBlackPainter(CorlorChess::black);
		ptrChessWhitePainter = &chessWhitePainter;
		ptrChessBlackPainter = &chessBlackPainter;

		GlSquarePainter square;
		for (auto it : mapLoca) {
			square.addOne(it.first, width);
		}
		while (!glfwWindowShouldClose(window))
		{
			Sleep(30);

			processInput(window);
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if(!SocketReceiveBuffer.empty()&& !PlayerData::bMyTurn) {
				PointGl chessPoint = SocketReceiveBuffer.front();
				addOneChessToBaord(chessPoint, !PlayerData::myCharacter, width);
				SocketReceiveBuffer.pop();
				PlayerData::bMyTurn = true;
			}

			square.draw();
			chessWhitePainter.draw();
			chessBlackPainter.draw();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		GlPainter::deleteVertexArrays();
		GlPainter::deleteBuffers();
		glfwTerminate();
		cout << "Gl window close" << endl;
		gameSocketManager.TurnOffSocket();
		gameSocketManager.closeConnection();
	});

	thread_socket->join();
	thread_rule->join();
	return 0;
}