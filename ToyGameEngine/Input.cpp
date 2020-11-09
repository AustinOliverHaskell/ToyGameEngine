#include <stdio.h>
#include <stdlib.h>

#include "Input.h"

Input::Input() {
	input_callbacks = new std::vector<InputCallback*>();

	prev_mouse_xpos = 0.0;
	prev_mouse_ypos = 0.0;
}

Input::~Input() {
	delete input_callbacks;
}

void Input::add_listener(InputCallback* callback)
{
	input_callbacks->push_back(callback);
}

void Input::process_keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {

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

void Input::process_mouse(double xpos, double ypos) {
	for (auto callback : *input_callbacks) {
		callback->mouse_position_changed(xpos, ypos);
	}

	for (auto callback : *input_callbacks) {
		callback->mouse_position_changed(xpos, ypos, prev_mouse_xpos, prev_mouse_ypos);
	}

	prev_mouse_xpos = xpos;
	prev_mouse_ypos = ypos;
}
