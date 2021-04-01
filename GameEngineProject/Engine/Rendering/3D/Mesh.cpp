#include "Mesh.h"

Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_) : VAO(0), VBO(0), shaderProgram(0), modelLoc(0), viewLoc(0), projectionLoc(0)
{
	subMesh = subMesh_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();

}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertexList.size() > 0) {
		subMesh.vertexList.clear();
	}
	if (subMesh.meshIndices.size() > 0) {
		subMesh.meshIndices.clear();
	}
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4>& instances_)
{
	glUniform1i(diffuseMap, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	glBindVertexArray(VAO);

	glEnable(GL_DEPTH_TEST);

	

	glUniform3fv(cameraPos, 1, glm::value_ptr(camera_->GetPosition()));
	glUniform3fv(position, 1, glm::value_ptr(camera_->GetLightSources()[0]->GetPosition()));
	glUniform1f(ambientValue, camera_->GetLightSources()[0]->getAmbient());
	glUniform1f(diffuseValue, camera_->GetLightSources()[0]->getDiffuse());
	glUniform1f(specularValue, camera_->GetLightSources()[0]->getSpecular());
	glUniform3fv(lightColor, 1, glm::value_ptr(camera_->GetLightSources()[0]->getLightColor()));

	glUniform1f(shininess, subMesh.material.shininess);
	glUniform1f(transparency, subMesh.material.transparency);
	glUniform3fv(matAmbient, 1, glm::value_ptr(subMesh.material.ambient));
	glUniform3fv(matDiffuse, 1, glm::value_ptr(subMesh.material.diffuse));
	glUniform3fv(matSpecular, 1, glm::value_ptr(subMesh.material.specular));

	for (int i = 0; i < instances_.size(); i++) {
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}
	
	
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);
	//Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	//Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	//Tex Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	
	cameraPos = glGetUniformLocation(shaderProgram, "cameraPos");
	position = glGetUniformLocation(shaderProgram, "light.position");
	ambientValue = glGetUniformLocation(shaderProgram, "light.ambientValue");
	diffuseValue = glGetUniformLocation(shaderProgram, "light.diffuseValue");
	specularValue = glGetUniformLocation(shaderProgram, "light.specularValue");
	lightColor = glGetUniformLocation(shaderProgram, "light.lightColor");


	diffuseMap = glGetUniformLocation(shaderProgram, "material.diffuseMap");
	shininess = glGetUniformLocation(shaderProgram, "material.shininess");
	transparency = glGetUniformLocation(shaderProgram, "material.transparency");
	matAmbient = glGetUniformLocation(shaderProgram, "material.ambient");
	matDiffuse = glGetUniformLocation(shaderProgram, "material.diffuse");
	matSpecular = glGetUniformLocation(shaderProgram, "material.specular");
}
