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
	Camera::GetInstance()->SetPosition(glm::vec3(0.0f, 1.0f, 15.0f));
	Camera::GetInstance()->AddLightSource(new LightSource(glm::vec3(5.0f, 3.0f, 1.0f), 0.1f, 0.9f, glm::vec3(1.0f, 1.0f, 1.0f)));

	

	model = new Model("Engine/GlobalElements/Resources/Models/Aircraft_obj.obj", "Engine/GlobalElements/Resources/Materials/Aircraft_obj.mtl", "glowShader", false);
	model2 = new Model("Engine/GlobalElements/Resources/Models/Astaramis.obj", "Engine/GlobalElements/Resources/Materials/Astaramis.mtl", "glowShader", false);
	model5 = new Model("Engine/GlobalElements/Resources/Models/sun.obj", "Engine/GlobalElements/Resources/Materials/sun.mtl", "glowShader", true); //glowShader
	models.push_back(model);
	models.push_back(model2);
	models.push_back(model5);

	object5 = new GameObject(model5);
	object5->SetPosition(object5->GetPosition() + glm::vec3(5.0f, 1.0f, -13.0f));
	object5->SetAngle(object5->GetAngle() + 60.0f);

	object1 = new GameObject(model2);
	object1->SetPosition(object1->GetPosition() + glm::vec3(5.0f, 2.0f, -28.0f));


	object2 = new GameObject(model);
	object2->SetAngle(object2->GetAngle() + 180.0f);		
	object2->SetPosition(object2->GetPosition() + glm::vec3(-10.0f, -4.0f, -6.0f));
	object3 = new GameObject(model);
	object3->SetAngle(object3->GetAngle() + 180.0f);		
	object3->SetPosition(object3->GetPosition() + glm::vec3(-10.0f, -4.0f, -10.0f));
	object4 = new GameObject(model);
	object4->SetAngle(object4->GetAngle() + 180.0f);		
	object4->SetPosition(object4->GetPosition() + glm::vec3(-10.0f, -0.0f, -8.0f));


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

}

void Game::Update(const float deltaTime_) {
	
	object2->SetPosition(object2->GetPosition() + glm::vec3(0.05f, 0.0f, 0.0f));
	object3->SetPosition(object3->GetPosition() + glm::vec3(0.05f, 0.0f, 0.0f));
	object4->SetPosition(object4->GetPosition() + glm::vec3(0.05f, 0.0f, 0.0f));
	
}

void Game::Render() {


	RenderMachine::GetInstance()->Render(models, delta);
	delta += 0.05f;

}