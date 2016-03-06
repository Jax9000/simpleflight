#include "Cube.h"

Cube::Cube(string path, string directory, Shader * shader)
{
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	for (int i = 0; i < 6 * 6; i+= 5)
	{
		Vertex vertex;
		vertex.Position = glm::vec3(cube_vertices[i], cube_vertices[i+1], cube_vertices[i+2]);
		vertex.TexCoords = glm::vec2(cube_vertices[i + 3], cube_vertices[i + 4]);
		vertices.push_back(vertex);
	}

	Texture texture;
	texture.id = Model::LoadTexture(path.c_str(), directory);
	texture.path = path.c_str() + '/' + directory;
	texture.type = "texture_spcular";
	textures.push_back(texture);

	this->mesh = new Mesh(vertices, indices, textures);
}

Cube::~Cube()
{
}

void Cube::Draw(glm::mat4 projection, glm::mat4 view)
{
	shader->Use();
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model_matrix));

	mesh->Draw(*shader);
}
