#include "Plane.h"

Plane::Plane(string path, string directory, Shader* shader, float scale)
{
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	Vertex vertex;

	vertex.Position = glm::vec3(1.0f, 0.0f, 1.0f);
	vertex.TexCoords = glm::vec2(scale/10, scale/10);
	vertex.Normal = glm::vec3(0, 1, 0);
	vertices.push_back(vertex);

	vertex.Position = glm::vec3(1.0f, 0.0f, -1.0f);
	vertex.TexCoords = glm::vec2(scale/10, 0.0f);
	vertex.Normal = glm::vec3(0, 1, 0);
	vertices.push_back(vertex);

	vertex.Position = glm::vec3(-1.0f, 0.0f, -1.0f);
	vertex.TexCoords = glm::vec2(0.0f, 0.0f);
	vertex.Normal = glm::vec3(0, 1, 0);
	vertices.push_back(vertex);

	vertex.Position = glm::vec3(-1.0f, 0.0f, 1.0f);
	vertex.TexCoords = glm::vec2(0.0f, scale/10);
	vertex.Normal = glm::vec3(0, 1, 0);
	vertices.push_back(vertex);

	GLuint indices_tab[6] = { 0, 1, 3, 1, 2, 3 };
	for (int i = 0; i < 6; i++)
		indices.push_back(indices_tab[i]);

	Texture texture;
	texture.id = Model::LoadTexture(path.c_str(), directory);
	texture.path = path.c_str() + '/' + directory;
	texture.type = "texture_spcular";
	textures.push_back(texture);

	mesh = new Mesh(vertices, indices, textures);
	this->shader = shader;
	Scale(glm::vec3(scale, 1.0f, scale));
	Transform(glm::vec3(0, -1, 0));
}


Plane::~Plane()
{
}

void Plane::Draw(glm::mat4 projection, glm::mat4 view)
{
	shader->Use();
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model_matrix));
	GLint lightPosLoc = glGetUniformLocation(shader->Program, "lightPos");
	glUniform3f(lightPosLoc, Light::position.x, Light::position.y, Light::position.z);
	mesh->Draw(*shader);
}