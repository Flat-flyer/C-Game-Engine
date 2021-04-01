#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "..//..//Core/Camera.h"
#include "..//..//Graphics/MaterialHandler.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
};

struct SubMesh {
	std::vector<Vertex> vertexList;
	std::vector<unsigned int> meshIndices;
	Material material;
};

class Mesh {
public:
	Mesh(SubMesh& subMech_, GLuint shaderProgram_);
	~Mesh();

	void Render(Camera* camera_, std::vector<glm::mat4>& instances_);

private:
	void GenerateBuffers();
	GLuint VAO, VBO;
	SubMesh subMesh;
	GLuint shaderProgram;
	GLuint modelLoc, viewLoc, projectionLoc;
	GLuint cameraPos, position, ambientValue, diffuseValue, specularValue, lightColor;
	GLuint diffuseMap, shininess, transparency, matAmbient, matDiffuse, matSpecular;

};

#endif // !MESH_H
