#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"
#include "../../GlobalElements/Debug.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct SubMesh {
	std::vector<Vertex> vertexList;
	std::vector<GLuint> indices;
	GLuint textureID;
};

class Mesh
{
public:
	Mesh(SubMesh subMesh_, GLuint ShaderProgram_);
	~Mesh();
	void Render(Camera* camera_, std::vector<glm::mat4> instances_);

private:
	GLuint VAO, VBO;
	void GenerateBuffers();
	SubMesh subMesh;
	GLuint shaderProgram;
	GLuint modelLoc, viewLoc, projLoc, textureLoc;
	GLuint viewPositionLoc, lightPosLoc, lightAmbientLoc, lightDiffuseLoc, lightColourLoc;
};

#endif