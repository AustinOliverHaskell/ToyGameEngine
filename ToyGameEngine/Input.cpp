#include <stdio.h>
#include <stdlib.h>

#include "Input.h"

Input::Input() {
	input_callbacks = new std::vector<InputCallback*>();
}

Input::~Input() {
	delete input_callbacks;
}

void Input::add_listener(InputCallback* callback)
{
	input_callbacks->push_back(callback);
}

void Input::process_input(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (action == GLFW_PRESS) {
		for (auto callback : *input_callbacks) {
			callback->on_press(key);
		}
	}
	else if (action == GLFW_RELEASE) {
		for (auto callback : *input_callbacks) {
			callback->on_release(key);
		}
	}

}
