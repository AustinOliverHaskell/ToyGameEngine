#pragma once

#include <map>
#include <vector>

#include "GraphicsLib.h"

class InputCallback {
public:
	virtual void on_press(int key) = 0;
	virtual void on_release(int key) = 0;
};

class Input {
	public: 
		Input();
		~Input();

		void add_listener(InputCallback * callback);

		void process_input(GLFWwindow* window, int key, int scancode, int action, int mods);

	private:
		std::vector<InputCallback*> * input_callbacks;
};

