// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "GraphicsLib.h"

#include "SpriteRenderer.h"
#include "Input.h"
#include "GameLoop.h"
#include "Primitives.h"
#include "Util.h"

std::string SHADER_PATH = "C:\\Users\\austi\\Documents\\ToyGameEngine\\ToyGameEngine\\shaders\\";

Input* input;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

int main(void) {
	GLFWwindow* window;
	input = new Input();
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Game Engine", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Load in the shaders that were going to use
	std::string vertex = SHADER_PATH + "SimpleVertexShader.vertexshader";
	std::string fragment = SHADER_PATH + "SimpleFragmentShader.fragmentshader";

	GLuint shader = Util::load_shaders(vertex.c_str(), fragment.c_str());

	glm::vec3 camera_position(0, 0, 0);
	Camera* camera = new Camera(camera_position);
	Renderer* renderer = new Renderer(camera);

	GameLoop game_loop(window, renderer);

	input->add_listener((InputCallback*)&game_loop);
	input->add_listener((InputCallback*)camera);

	glm::vec3 cube_position(-1, -1, -1);
	glm::vec3 cube_scale(1, 1, 1);

	Cube* cube = new Cube(cube_position, 
						  cube_scale, 
						  glm::mat4(1.0f),
						  shader,
						  10);

	renderer->add_item((Renderable*)cube);

	// TODO: Move this to it's own thread. - Austin Haskell
	double last_frame_time = glfwGetTime();;
	do {

		game_loop.step();

		// TODO: Implement a text framecount - Austin Haskell
		double current_time = glfwGetTime();
		double delta = current_time - last_frame_time;
		last_frame_time = current_time;

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	input->process_keyboard(window, key, scancode, action, mods);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	input->process_mouse(xpos, ypos);
}