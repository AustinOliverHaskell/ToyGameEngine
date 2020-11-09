#pragma once
// Shader Loader
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "GraphicsLib.h"

class Util {
	public:
		static GLuint load_shaders(const char* vertex_file_path, const char* fragment_file_path);

		static glm::vec3 calc_normal(glm::vec3 one, glm::vec3 two, glm::vec3 three);
		static glm::vec3 normalize(glm::vec3 vec);
};

