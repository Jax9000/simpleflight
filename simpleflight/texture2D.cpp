#include "texture2D.h"
#include <iostream>

Texture2D::Texture2D(char* filePath)
{
	glGenTextures(1, &texture);
	
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	SetFlags(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT, GL_NEAREST, GL_LINEAR, borderColor);
	
	try
	{
		glBindTexture(GL_TEXTURE_2D, texture);
		unsigned char* image = SOIL_load_image(filePath, &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	catch (int e)
	{
		std::cout << "ERROR::TEXTURE::FILE_NOT_SUCCESFULLY_READ\n";
	}

}


void Texture2D::SetFlags(GLenum wrapS, GLenum wrapT, GLenum minFilter, GLenum mapFilter, float* borderColor)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mapFilter);
	glBindTexture(GL_TEXTURE_2D, 0);
}