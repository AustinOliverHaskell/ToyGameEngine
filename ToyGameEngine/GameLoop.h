#pragma once

#include "Input.h"
#include "Renderer.h"

class GameLoop : InputCallback {
	public:
		GameLoop(GLFWwindow* window, Renderer * renderer);
		~GameLoop();

		void step();

		virtual void on_press(int key);
		virtual void on_release(int key) {};

		virtual void mouse_position_changed(double xpos, double ypos);
		virtual void mouse_position_changed(double xpos, double ypos, double prev_xpos, double prev_ypos) {};

	private:
		GLFWwindow* window;
		Renderer* renderer;
};

