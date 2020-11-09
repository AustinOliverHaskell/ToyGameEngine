#pragma once

#include "Input.h"
#include "Renderer.h"

class GameLoop : InputCallback {
	public:
		GameLoop(GLFWwindow* window, Renderer * renderer);
		~GameLoop();

		void step();

		virtual void on_press(int key);
		virtual void on_release(int key);

	private:
		GLFWwindow* window;
		Renderer* renderer;
};

