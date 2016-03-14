#include "Plane.h"

Plane::Plane(string path, string directory, Shader* shader, float scale)
{
	EventController::AddKeyListener(this);
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	Vertex vertex;
    vertex.Normal = glm::vec3(0, 0, 0);

	vertex.Position = glm::vec3(1.0f, 0.0f, 1.0f);
	vertex.TexCoords = glm::vec2(scale/10, scale/10);
	vertices.push_back(vertex);

	vertex.Position = glm::vec3(1.0f, 0.0f, -1.0f);
	vertex.TexCoords = glm::vec2(scale/10, 0.0f);
	vertices.push_back(vertex);

	vertex.Position = glm::vec3(-1.0f, 0.0f, -1.0f);
	vertex.TexCoords = glm::vec2(0.0f, 0.0f);
	vertices.push_back(vertex);

	vertex.Position = glm::vec3(-1.0f, 0.0f, 1.0f);
	vertex.TexCoords = glm::vec2(0.0f, scale/10);
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

	mesh->Draw(*shader);
}

void Plane::OnKeyHold(int key)
{
	OnKey(key);
}

void Plane::OnKeyPress(int key)
{
	OnKey(key);
}

void Plane::OnKey(int key)
{
	if (key == GLFW_KEY_LEFT)
		Rotate(glm::vec3(0.0f, 0.10f, 0.0f));
}
