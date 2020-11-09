#pragma once

#include "GraphicsLib.h"

#include "Input.h"

class Camera : InputCallback {
	public:
		Camera(glm::vec3 pos, float fov = 45.0, float h_angle = 0.0, float v_angle = 0.0);
		~Camera();

		void calculate_matricies();

		virtual void on_press(int key) {};
		virtual void on_release(int key) {};

		virtual void mouse_position_changed(double xpos, double ypos) {};
		virtual void mouse_position_changed(double xpos, double ypos, double prev_xpos, double prev_ypos);

		glm::mat4 view_matrix;
		glm::mat4 projection_matrix;

		float field_of_view;

		float horizontal_angle;
		float vertical_angle;

		glm::vec3 position;
};

