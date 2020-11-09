#pragma once

#include <map>
#include <vector>

#include "GraphicsLib.h"

class InputCallback {
public:
	virtual void on_press(int key) = 0;
	virtual void on_release(int key) = 0;

	virtual void mouse_position_changed(double xpos, double ypos) = 0;
	virtual void mouse_position_changed(double xpos, double ypos, double prev_xpos, double prev_ypos) = 0;
};

class Input {
	public: 
		Input();
		~Input();

		void add_listener(InputCallback * callback);

		void process_keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
		void process_mouse(double xpos, double ypos);

		// TODO: Joysticks - Austin Haskell

	private:
		std::vector<InputCallback*> * input_callbacks;

		double prev_mouse_xpos;
		double prev_mouse_ypos;
};

