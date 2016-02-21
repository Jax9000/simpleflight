#include <string>
#include "GL\glew.h"
#include <assimp/Importer.hpp>

struct Texture {
	GLuint id;
	std::string type;
	aiString path;
};