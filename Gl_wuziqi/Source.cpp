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

#include "../ShaderReader/FIleManager/FileManagerControler.h"
#include "../ShaderReader/MyShader.h"
#include "myVertices.h"
#include "../CallBack/Class.h"


#include "../TextureManager/TextureManager.h"
#include "../CallBack/callback.h"
#include "../GlfwConfigure/GlfwConfigure.h"
#include "../DrawBoard/glSquarePainter.h"
#include "../DrawBoard/GlCirclePainter.h"


#include "migration\data_base\DataWuziqi.h"
#include "migration\rule\rule.h"


GlCirclePainter* ptrChessWhitePainter = nullptr;
GlCirclePainter* ptrChessBlackPainter = nullptr;
BoardLocation* ptrBoardLoc = nullptr;

//bool is_win(ChessPoint& point_chess, MapPoint*&ptrchesses, int& chess_width, bool&myturn, const bool& gamegoingon);

bool myCharacter = false;
int chess_width = 50;
PointGl myChessCoor;


std::mutex m;
std::condition_variable cv;
//bool bReady = false;
bool bConnectionOrderConfirmed = false;

std::queue<SocketData> chess_point_buffer;
std::queue<PointGl> SocketReceiveBuffer;

static volatile bool HasData = true;

static std::thread* thread_socket = nullptr;
static std::thread* thread_rule = nullptr;

using std::cout;
using std::endl;

DataWuziqiSpecType dataWuziqiSpecType;
GameSocketManager gameSocketManager(&dataWuziqiSpecType, handleClickInput_socket);





std::thread* matchplayer(GameSocketManager* gameSocketManager, bool myCharacter)
{
	if (gameSocketManager->getBEventMaked() == true) {
		return nullptr;
	}
	gameSocketManager->prepareForWaitLoop();
	std::thread* thread = new std::thread(&GameSocketManager::looprecvsend, gameSocketManager);

	//there may be a problem, that is when function getBRequestConnection() execute, the task of setting value has
	// not been done.
	myCharacter = gameSocketManager->getBRequestConnection();
	if (myCharacter == true) {
		//show message box telling seccess of matching a existting player.
	}
	else {

	}
	return thread;
}

void worker_rule() {
	//analyze a queue of data.
	while (1) {
		if (chess_point_buffer.empty()) {
			//what if here release a mutex.
			std::unique_lock lk(m);
			HasData = false;
			cv.wait(lk, [] {return HasData; });
			return;
		}
		else {
			while (!chess_point_buffer.empty())
			{
				SocketData& socket_data = chess_point_buffer.front();
				if (is_win(socket_data.point_chess, dataWuziqiSpecType.get(), chess_width, myCharacter, true)) {
					//
				}
				else {

				}
				chess_point_buffer.pop();
			}
		}
	}
}

void startRuleThread() {
	thread_rule = new std::thread(worker_rule);
}

int main()
{


	thread_socket = matchplayer(&gameSocketManager, myCharacter);
	//std::unique_lock lk(m);

	//cv.wait(lk, [] {return bConnectionOrderConfirmed; });
	myCharacter = gameSocketManager.getBRequestConnection();

	std::thread boardLoopRender([&]() {
		GlfwConfigure* myConfig = GlfwConfigure::getInstance();
		GLFWwindow* window = myConfig->getGlfWindowHandle();

		BoardLocation boardLoc(WINDOWS_WIDTH, WINDOWS_HEIGHT, 16, 16);
		int width = boardLoc.getWidth();
		BoardLocation::MapLoca mapLoca = boardLoc.getAllPoint();
		ptrBoardLoc = &boardLoc;

		GlCirclePainter chessWhitePainter(pair<int,int>(100,100), chess_width, CorlorChess::white);
		GlCirclePainter chessBlackPainter(pair<int,int>(100,100), chess_width, CorlorChess::black);
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


			//std::unique_lock lk(m);
			//chessWhitePainter.addOne(myChessCoor, boardLoc.getWidth());
			//bReady = true;
			//cv.notify_one();

			while (!SocketReceiveBuffer.empty()) {
				PointGl chessPoint = SocketReceiveBuffer.front();
				addOneChessToBaord(chessPoint, !myCharacter, width);
				SocketReceiveBuffer.pop();
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
	
	
	while (thread_socket == nullptr) {
		cout << "thread_socket == nullptr" << endl;
	}
	cout << "thread_socket != nullptr" << endl;
	thread_socket->join();
	return 0;
}