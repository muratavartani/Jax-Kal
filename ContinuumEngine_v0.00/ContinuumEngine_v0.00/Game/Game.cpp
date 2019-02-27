#include "Game.h"



Game::Game()
{
}


Game::~Game()
{
	delete model;
	model = nullptr;

	delete object1;
	object1 = nullptr;
}

bool Game::Initialize() {
	Camera::GetInstance()->SetPosition(glm::vec3(0.0f, 30.0f, 45.0f));
	Camera::GetInstance()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));
	model = new Model("Engine/GlobalElements/Resources/Models/knightModel.obj", "Engine/GlobalElements/Resources/Materials/knightModel.mtl", ShaderHandler::GetInstance()->GetShader("baseShader"));
	//model = new Model("Engine/GlobalElements/Resources/Models/Dice.obj", "Engine/GlobalElements/Resources/Models/Dice.mtl", ShaderHandler::GetInstance()->GetShader("baseShader"));

	object1 = new GameObject(model);
	if (!model) {
		return false;
	}
	if (!object1) {
		return false;
	}
	std::cout << "Object's bounding box: " << std::endl;
	std::cout << "Min vert : " << glm::to_string(object1->GetBoundaryBox().minVert) << std::endl;
	std::cout << "Max vert : " << glm::to_string(object1->GetBoundaryBox().maxVert) << std::endl;
	return true;
	/*tri = new Triangle();
	if (!tri) {
	return false;
	}
	//return true;
	//shape = new Triangle(ShaderHandler::GetInstance()->GetShader("colourShader"));
	TextureHandler::GetInstance()->CreateTexture("CherkerboardTexture", "Resources/Textures/CheckerboardTexture.png");
	shape = new Cube(ShaderHandler::GetInstance()->GetShader("baseShader"), TextureHandler::GetInstance()->GetTexture("CherkerboardTexture"));
	shape->SetScale(glm::vec3(0.5));
	if (!shape) {
	return false;
	}*/



}

void Game::Update(const float deltaTime_) {
	//std::cout << "game's update" << std::endl;
	object1->SetAngle(object1->GetAngle() + 0.005f);
}

void Game::Render() {
	//std::cout << "game's render" << std::endl;
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//tri->Render();

	model->Render(Camera::GetInstance());
}