#pragma once

#include "GraphicsLib.h"

class Camera {
	public:
		Camera(glm::vec3 pos, float fov = 45.0, float h_angle = 0.0, float v_angle = 0.0);
		~Camera();

		void calculate_matricies();

		glm::mat4 view_matrix;
		glm::mat4 projection_matrix;

		float field_of_view;

		float horizontal_angle;
		float vertical_angle;

		glm::vec3 position;
};

