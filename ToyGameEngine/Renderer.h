#pragma once
#include <map>

#include "GraphicsLib.h"

#include "Camera.h"

class Renderable {
	public:
		GLfloat* shape_data;
		GLfloat* color_data;
		GLfloat* normal_data;

		GLuint verticies;
		GLuint colors;
		GLuint normals;

		glm::mat4 transform;

		glm::vec3 position;
		glm::vec3 scale;
		float rotation;

		GLuint MatrixID;
		GLuint ViewMatrixID;
		GLuint ModelMatrixID;

		GLuint shader;

		unsigned int face_count;

		unsigned int id;
};

class Renderer {
	public:
		Renderer(Camera * camera);
		~Renderer();

		void add_item(Renderable * item);
		void remove_item(unsigned int id);

		void render();

		void render_item(unsigned int item);
		void render_item(Renderable * item);

		void swap_camera(Camera * camera);

		Camera* camera;

	private:
		std::map<unsigned int, Renderable*>* items_to_render;
};

