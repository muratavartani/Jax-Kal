#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
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
	bool isGlowing;
	bool skyboxFlag;
};

class Mesh
{
public:

	Mesh(SubMesh subMesh_, std::map<std::string, GLuint> shaderPrograms_);



	~Mesh();
	void Render(Camera* camera_, std::vector<glm::mat4> instances_, const std::string& shaderProgram_);
	void RenderMesh();

private:
	GLuint VAO, VBO, meshVAO, meshVBO, skyVAO, skyVBO;
	void GenerateBuffers();
	SubMesh subMesh;
	std::map<std::string, GLuint> shaderPrograms;

	GLuint modelLoc, viewLoc, projLoc, textureLoc, cubeTextureLoc;
	GLuint viewPositionLoc, lightPosLoc, lightAmbientLoc, lightDiffuseLoc, lightColourLoc;
};

#endif