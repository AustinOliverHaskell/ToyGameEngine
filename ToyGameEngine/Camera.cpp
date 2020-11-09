#include "Camera.h"

#include <glm\ext.hpp>

#define ASPECT_RATIO 16.0f/9.0f

Camera::Camera(glm::vec3 pos, float fov, float h_angle, float v_angle)
{
	projection_matrix = glm::mat4(1.0f);
	view_matrix       = glm::mat4(1.0f);

	field_of_view = fov;

	horizontal_angle = h_angle;
	vertical_angle   = v_angle;

	position = pos;
}

Camera::~Camera() { }

void Camera::calculate_matricies() {
	glm::vec3 direction(
		cos(vertical_angle) * sin(horizontal_angle),
		sin(vertical_angle),
		cos(vertical_angle) * cos(horizontal_angle)
	);

	glm::vec3 right(
		sin(horizontal_angle - 3.14f / 2.0f),
		0,
		cos(horizontal_angle - 3.14f / 2.0f)
	);

	glm::vec3 up = glm::cross(right, direction);

	projection_matrix = glm::perspective(glm::radians(field_of_view), ASPECT_RATIO, 0.1f, 100.0f);

	view_matrix = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
	);
}


