// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include "GameLoop.h"

GameLoop::GameLoop(GLFWwindow* window, Renderer * renderer) {
	if (window == nullptr) {
		throw "Window passed to the main game loop was null";
	}

	this->window = window;
	this->renderer = renderer;
}

GameLoop::~GameLoop() {

}

void GameLoop::step() {

	glClear(GL_COLOR_BUFFER_BIT);

	renderer->render();

	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void GameLoop::on_press(int key)
{
	if (key == GLFW_KEY_W) {
		printf("W Pressed \r\n");
	}
	else if (key == GLFW_KEY_A) {
		printf("A Pressed \r\n");
	}
	else if (key == GLFW_KEY_S) {
		printf("S Pressed \r\n");
	}
	else if (key == GLFW_KEY_D) {
		printf("D Pressed \r\n");
	}
}

void GameLoop::mouse_position_changed(double xpos, double ypos)
{
	//printf("Mouse is at position %f, %f \r\n", xpos, ypos);
}

