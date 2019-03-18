#include "RenderMachine.h"


std::unique_ptr<RenderMachine> RenderMachine::RenderMachineInstance = nullptr;






RenderMachine::RenderMachine()
{
	SkyboxObj = new Skybox("Engine/GlobalElements/Resources/Textures/right.jpg", "Engine/GlobalElements/Resources/Textures/left.jpg", "Engine/GlobalElements/Resources/Textures/top.jpg", "Engine/GlobalElements/Resources/Textures/bottom.jpg", "Engine/GlobalElements/Resources/Textures/front.jpg", "Engine/GlobalElements/Resources/Textures/back.jpg" );
}


RenderMachine::~RenderMachine()
{



}



RenderMachine* RenderMachine::GetInstance() {
	if (RenderMachineInstance.get() == nullptr) {
		RenderMachineInstance.reset(new RenderMachine);
	}
	return RenderMachineInstance.get();

}


void RenderMachine::Render(std::vector<Model*> models_, float delta_) {
	delta = delta_;
	std::vector<Model*> GlowingModels;
	std::vector<Model*> NormalModels;

	for (int i = 0; i < models_.size(); i++) {
		
		if (models_[i]->isGlowing) {
			GlowingModels.push_back(models_[i]);
		}
		else {
			NormalModels.push_back(models_[i]);
		}
	}
	
	//Model * modmod = new Model("Engine/GlobalElements/Resources/Models/Aircraft_obj.obj", "Engine/GlobalElements/Resources/Materials/Aircraft_obj.mtl", "glowShader", false);
	//GameObject* object6 = new GameObject(modmod);
	//object6->SetPosition(object6->GetPosition() + glm::vec3(-10.0f, -6.0f, -6.0f));





	// 1. render scene into hdrFBO
	glBindFramebuffer(GL_FRAMEBUFFER, ContinuumEngine::GetInstance()->hdrFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);





	glEnable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
	//make render calls for glowing meshes
	for (int i = 0; i < GlowingModels.size(); i++) {
		//glBindFramebuffer(GL_FRAMEBUFFER, ContinuumEngine::GetInstance()->hdrFBO);
	
		GlowingModels[i]->Render(Camera::GetInstance(), "glowShader");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// 2. blur bright fragments with two-pass Gaussian Blur 
// --------------------------------------------------
	bool horizontal = true, first_iteration = true;
	unsigned int amount = (int)(std::abs(std::sin(delta) * 30));

	glUseProgram(ShaderHandler::GetInstance()->GetShader("blurShader"));
	for (unsigned int i = 0; i < amount; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, ContinuumEngine::GetInstance()->pingpongFBO[horizontal]);
		glUniform1i(glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("blurShader"), "horizontal"), horizontal);
		glBindTexture(GL_TEXTURE_2D, first_iteration ? ContinuumEngine::GetInstance()->colorBuffers[0] : ContinuumEngine::GetInstance()->pingpongColorbuffers[!horizontal]);  // bind texture of other framebuffer (or scene if first iteration)
		ContinuumEngine::GetInstance()->renderQuad();
		horizontal = !horizontal;
		if (first_iteration)
			first_iteration = false;
	}



	//make render calls for non glowing meshes
	glBindFramebuffer(GL_FRAMEBUFFER, ContinuumEngine::GetInstance()->hdrFBO);
	glActiveTexture(GL_TEXTURE0);
	for (int i = 0; i < NormalModels.size(); i++) {
	

		NormalModels[i]->Render(Camera::GetInstance(), "glowShader");
	}






	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//modmod->Render(Camera::GetInstance(), "glowShader");
	// 3. render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
	// --------------------------------------------------------------------------------------------------------------------------

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glActiveTexture(GL_TEXTURE0);
	//glBindFramebuffer(GL_FRAMEBUFFER, ContinuumEngine::GetInstance()->hdrFBO);

	glUseProgram(ShaderHandler::GetInstance()->GetShader("bloomFinalShader"));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ContinuumEngine::GetInstance()->colorBuffers[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, ContinuumEngine::GetInstance()->pingpongColorbuffers[!horizontal]);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, ContinuumEngine::GetInstance()->colorBuffers[1]);

		glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	SkyboxObj->Render(Camera::GetInstance());
	glEnable(GL_DEPTH_TEST);
	//ContinuumEngine::GetInstance()->bloom = true;
	//std::cout << "bloom :" << ContinuumEngine::GetInstance()->bloom << std::endl;
	glUniform1i(glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("bloomFinalShader"), "bloom"), ContinuumEngine::GetInstance()->bloom);
	ContinuumEngine::GetInstance()->exposure = 50.0f; // (std::abs(std::sin(delta) * 30));
	glUniform1f(glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("bloomFinalShader"), "exposure"), ContinuumEngine::GetInstance()->exposure);
	ContinuumEngine::GetInstance()->renderQuad();





	glBindFramebuffer(GL_FRAMEBUFFER, ContinuumEngine::GetInstance()->hdrFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	//SkyboxObj->Render(Camera::GetInstance());

	glDisable(GL_DEPTH_TEST);
	//glActiveTexture(GL_TEXTURE2);
	//glBindTexture(GL_TEXTURE_2D, ContinuumEngine::GetInstance()->colorBuffers[1]);
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default 
	glUseProgram(ShaderHandler::GetInstance()->GetShader("frameShader"));
	//ContinuumEngine::GetInstance()->renderFrame();
	//glEnable(GL_DEPTH_TEST); //!!!!!!!!!!!!if i enable depth test it will render the scene otherwise it wil render the skybox

}