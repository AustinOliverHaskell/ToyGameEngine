#pragma once
// Shader Loader
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "GraphicsLib.h"

class Util {
	public:
		static GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path);
};

