#include "OBJLoader.h"

#include "objload.h"

using namespace std;

OBJLoader::OBJLoader() {
	faceCount = 0;
}

OBJLoader::~OBJLoader() {
}

bool OBJLoader::open_file(string path) {

	bool retVal = true;
	ifstream file_stream;

	file_stream.open(path);

	if (!file_stream.is_open())
	{
		return false;
	}

	// Load the file
	obj::ObjModel model = obj::parseObjModel(file_stream);

	// Just get the start iterator for the faces map
	auto it = model.faces.cbegin();

	// Second in this context refers to the value of the map
	//  second.first refers to the first item of the contaned tuple
	//  which in this case is a vector
	faceCount = it->second.first.size() / 3;

	// second.first is refering to the underlying vector of facepoints 
	for (auto x = it->second.first.begin(); x != it->second.first.end(); ++x)
	{
		// Get the vertex info and then multiply it by 3 to offset it
		//  around the x y and z points
		int vertex_index = (x->v) * 3;

		// Push back each point that is listed in the face description
		verticies.push_back(model.vertex[vertex_index]);
		verticies.push_back(model.vertex[vertex_index + 1]);
		verticies.push_back(model.vertex[vertex_index + 2]);

		int normal_index = (x->n) * 3;

		normals.push_back(model.normal[normal_index]);
		normals.push_back(model.normal[normal_index + 1]);
		normals.push_back(model.normal[normal_index + 2]);
	}

	return true;
}