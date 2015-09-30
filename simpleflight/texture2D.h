#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "GL\glew.h"
#include "SOIL\soil.h"

class Texture2D
{
public:
	Texture2D(char* filePath);
	void SetFlags(GLenum wrapS, GLenum wrapT, GLenum minFilter, GLenum mapFilter, float* borderColor);
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	void Use() { glBindTexture(GL_TEXTURE_2D, texture); }
private:
	int width, height;
	GLuint texture;
};

#endif