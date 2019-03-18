#include "Mesh.h"





Mesh::Mesh(SubMesh subMesh_, std::map<std::string, GLuint> shaderPrograms_) : VAO(0), VBO(0), meshVAO(0), meshVBO(0), skyVAO(0), skyVBO(0){

	shaderPrograms = shaderPrograms_;
	subMesh = subMesh_;
	GenerateBuffers();
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &meshVAO);
	glDeleteBuffers(1, &meshVBO);
	glDeleteVertexArrays(1, &skyVAO);
	glDeleteBuffers(1, &skyVBO);
	//glDeleteFramebuffers(1, &hdrFBO);
	//glDeleteRenderbuffers(1, &rboDepth);
	//glDeleteFramebuffers(2, pingpongFBO);
	//delete other framebuffers

}

void Mesh::GenerateBuffers() {
	if (subMesh.skyboxFlag == false) {
		if (subMesh.isGlowing == false) {
			glDeleteVertexArrays(1, &meshVAO);
			glDeleteBuffers(1, &meshVBO);
			glGenVertexArrays(1, &meshVAO);
			glGenBuffers(1, &meshVBO);
			glBindBuffer(GL_ARRAY_BUFFER, meshVBO);
			glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW); //sizeof(subMesh.vertexList)
			glBindVertexArray(meshVAO);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			modelLoc = glGetUniformLocation(shaderPrograms["baseShader"], "model");
			viewLoc = glGetUniformLocation(shaderPrograms["baseShader"], "view");
			projLoc = glGetUniformLocation(shaderPrograms["baseShader"], "proj");
			textureLoc = glGetUniformLocation(shaderPrograms["baseShader"], "inputTexture");
			viewPositionLoc = glGetUniformLocation(shaderPrograms["baseShader"], "viewPosition");//viewPosition
			lightPosLoc = glGetUniformLocation(shaderPrograms["baseShader"], "light.lightPos");
			lightAmbientLoc = glGetUniformLocation(shaderPrograms["baseShader"], "light.ambient");
			lightDiffuseLoc = glGetUniformLocation(shaderPrograms["baseShader"], "light.diffuse");
			lightColourLoc = glGetUniformLocation(shaderPrograms["baseShader"], "light.lightColor");
		}

		else {
			modelLoc = glGetUniformLocation(shaderPrograms["bloomShader"], "model");
			viewLoc = glGetUniformLocation(shaderPrograms["bloomShader"], "view");
			projLoc = glGetUniformLocation(shaderPrograms["bloomShader"], "proj");
			textureLoc = glGetUniformLocation(shaderPrograms["baseShader"], "inputTexture");
			viewPositionLoc = glGetUniformLocation(shaderPrograms["bloomShader"], "viewPosition");
			lightPosLoc = glGetUniformLocation(shaderPrograms["baseShader"], "light.lightPos");
			lightAmbientLoc = glGetUniformLocation(shaderPrograms["baseShader"], "light.ambient");
			lightDiffuseLoc = glGetUniformLocation(shaderPrograms["baseShader"], "light.diffuse");
			lightColourLoc = glGetUniformLocation(shaderPrograms["baseShader"], "light.lightColor");
		}
	}
	else {
		glGenVertexArrays(1, &skyVAO);
		glBindVertexArray(skyVAO);
		glGenBuffers(1, &skyVBO);
		glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
		glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), NULL, GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		modelLoc = glGetUniformLocation(shaderPrograms["SkyboxShader"], "model");
		viewLoc = glGetUniformLocation(shaderPrograms["SkyboxShader"], "view");
		projLoc = glGetUniformLocation(shaderPrograms["SkyboxShader"], "proj");
		cubeTextureLoc = glGetUniformLocation(shaderPrograms["SkyboxShader"], "cubeTexture");

	}
	
}


void Mesh::RenderMesh() {
	glGenVertexArrays(1, &meshVAO);
	glGenBuffers(1, &meshVBO);
	glBindBuffer(GL_ARRAY_BUFFER, meshVBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW); //sizeof(subMesh.vertexList)
	glBindVertexArray(meshVAO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(meshVAO);
	glDrawArrays(GL_QUADS, 0, subMesh.vertexList.size());
	glBindVertexArray(0);

	glDeleteVertexArrays(1, &meshVAO);
	glDeleteBuffers(1, &meshVBO);
	
}
void Mesh::Render(Camera* camera_, std::vector<glm::mat4> instances_, const std::string& shaderProgram_) {

	if (shaderProgram_ == "glowShader") {

	
		glUseProgram(shaderPrograms["bloomShader"]);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
		
		glBindTexture(GL_TEXTURE_2D, subMesh.textureID);
		// set lighting uniforms
		for (unsigned int i = 0; i < camera_->GetLightSources().size(); i++)
		{


			const std::string Lpos = "lights[" + std::to_string(i) + "].Position";
			const std::string Lcolor = "lights[" + std::to_string(i) + "].Color";
			glUniform3fv(glGetUniformLocation(shaderPrograms["bloomShader"], Lpos.c_str()), 1, &camera_->GetLightSources()[i]->GetPosition()[0]);
			glUniform3fv(glGetUniformLocation(shaderPrograms["bloomShader"], Lcolor.c_str()), 1, &camera_->GetLightSources()[i]->GetLightColour()[0]);

		}

		glUniform3fv(glGetUniformLocation(shaderPrograms["bloomShader"], "viewPosition"), 1, &camera_->GetPosition()[0]);

		for (int i = 0; i < instances_.size(); i++) {
			glUniformMatrix4fv(glGetUniformLocation(shaderPrograms["bloomShader"], "model"), 1, GL_FALSE, glm::value_ptr(instances_[i]));
			RenderMesh();
		}
		glUseProgram(shaderPrograms["bloomLightShader"]);
		for (int i = 0; i < instances_.size(); i++) {
			glUniformMatrix4fv(glGetUniformLocation(shaderPrograms["bloomLightShader"], "model"), 1, GL_FALSE, glm::value_ptr(instances_[i]));
			glUniform3fv(glGetUniformLocation(shaderPrograms["bloomLightShader"], "lightColor"), 1, &camera_->GetLightSources()[0]->GetLightColour()[0]);
			RenderMesh();
		}

		/*
		glUseProgram(shaderPrograms["bloomLightShader"]);
		glUniformMatrix4fv(glGetUniformLocation(shaderPrograms["bloomLightShader"], "proj"), 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
		glUniformMatrix4fv(glGetUniformLocation(shaderPrograms["bloomLightShader"], "view"), 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
		*/

		//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	else if(shaderProgram_ == "baseShader") {
	
		glUseProgram(shaderPrograms["baseShader"]);
		GenerateBuffers();
		glUniform1i(textureLoc, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, subMesh.textureID);

		glUniform3f(viewPositionLoc, camera_->GetPosition().x, camera_->GetPosition().y, camera_->GetPosition().z);
		glUniform3f(lightPosLoc, camera_->GetLightSources()[0]->GetPosition().x, camera_->GetLightSources()[0]->GetPosition().y, camera_->GetLightSources()[0]->GetPosition().z);
		glUniform1f(lightAmbientLoc, camera_->GetLightSources()[0]->GetAmbient());
		glUniform1f(lightDiffuseLoc, camera_->GetLightSources()[0]->GetDiffuse());
		glUniform3f(lightColourLoc, camera_->GetLightSources()[0]->GetLightColour().x, camera_->GetLightSources()[0]->GetLightColour().y, camera_->GetLightSources()[0]->GetLightColour().z);

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

		glBindVertexArray(meshVAO);
		for (int i = 0; i < instances_.size(); i++) {
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
			glDrawArrays(GL_QUADS, 0, subMesh.vertexList.size());
		}

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	else if (shaderProgram_ == "SkyboxShader") {
		//glUseProgram(shaderPrograms["SkyboxShader"]);

		//for (int i = 0; i < instances_.size(); i++) {
		//	glUniformMatrix4fv(glGetUniformLocation(shaderPrograms["SkyboxShader"], "model"), 1, GL_FALSE, glm::value_ptr(instances_[i]));
		//	glBindVertexArray(skyVAO);
		//	glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
		//	glEnableVertexAttribArray(0);
		//}
	}



}