#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glfw3.h>
extern bool firstMouse;
extern float lastX;
extern float lastY;
extern float yaw;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
extern float pitch;
extern float fov;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraPos;
extern glm::vec3 cameraUp;
extern float deltaTime;	// Time between current frame and last frame
extern float lastFrame; // Time of last frame
extern float currentFrame;


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void mouseClick_callback(GLFWwindow* window,int button, int xposIn, int yposIn);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);