#pragma once
#include <fstream>
#include <vector>
#include <string>

#include "GraphicsLib.h"

class OBJLoader {
	public:
		OBJLoader();
		~OBJLoader();

		bool open_file(std::string path);

		unsigned int getVertexCount() { return verticies.size(); }
		unsigned int getNormalCount() { return normals.size();   }

		GLfloat* getObjectData() { return &verticies[0]; }
		GLfloat* getNormals()    { return &normals[0];   }

		unsigned int faceCount;

	private:
		std::vector <std::ifstream> file_refrences;

		std::vector<glm::vec2> uvs;

		std::vector<float> normals;
		std::vector<float> verticies;

		glm::vec3 calcNormal(glm::vec3 one, glm::vec3 two, glm::vec3 three);
		glm::vec3 normalize(glm::vec3 vec);
};

