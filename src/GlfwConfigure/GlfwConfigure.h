#pragma once
struct GLFWwindow;

static const int WINDOWS_WIDTH = 1000;
static const int WINDOWS_HEIGHT = 1000;
static const int VIEW_WIDTH = 1200;
static const int VIEW_HEIGHT = 1200;
class GlfwConfigure
{
public:
	GlfwConfigure(const GlfwConfigure&) = delete;
	void operator=(const GlfwConfigure &) = delete;
	GLFWwindow* getGlfWindowHandle() const;
	static GlfwConfigure* getInstance();
protected:
	GlfwConfigure() { 
		if (run() == false)
			m_singleton = nullptr;
	};
	bool run();
private:
	static GLFWwindow* m_window;
	static GlfwConfigure* m_singleton;
};

