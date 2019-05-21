#include "Game.h"

Game::Game()
{
}


Game::~Game()
{

	delete model;
	model = nullptr;
	delete projectileModel;
	projectileModel = nullptr;
	delete Land1;
	Land1 = nullptr;
	delete spawnerModel;
	spawnerModel = nullptr;
	models.clear();
	models.shrink_to_fit();
	delete projectileObj;
	projectileObj = nullptr;
	delete character;
	character = nullptr;
	delete Land1;
	Land1 = nullptr;
	delete Land1Obj;
	Land1Obj = nullptr;
	delete projectile;
	projectile = nullptr;
	delete planetSpawner;
	planetSpawner = nullptr;

	delete planetSpawnerObject;
	planetSpawnerObject = nullptr;

	delete audioHandler;
	audioHandler = nullptr;


	projectileList.clear();
	projectileList.shrink_to_fit();
	objects.clear();
	objects.shrink_to_fit();


	//delete object1;
	//object1 = nullptr;
}

bool Game::Initialize() {
	//Setting Camera options and lights
	ContinuumEngine3D::Camera::GetInstance()->SetPosition(glm::vec3(0.0f, 1.0f, 15.0f));
	ContinuumEngine3D::Camera::GetInstance()->AddLightSource(new ContinuumEngine3D::LightSource(glm::vec3(0.0f, 0.0f, 8.0f), 0.1f, 0.9f, glm::vec3(1.0f, 1.0f, 1.0f))); //0.5,0.3
	ContinuumEngine3D::Camera::GetInstance()->AddLightSource(new ContinuumEngine3D::LightSource(glm::vec3(-10.0f, -7.0f, -15.0f), 0.1f, 0.9f, glm::vec3(1.0f, 1.0f, 1.0f)));
	ContinuumEngine3D::Camera::GetInstance()->AddLightSource(new ContinuumEngine3D::LightSource(glm::vec3(10.0f, -7.0f, -15.0f), 0.1f, 0.9f, glm::vec3(1.0f, 1.0f, 1.0f)));
	//initiating audio
	audioHandler = new ContinuumEngine3D::AudioHandler();

	//Creating Models
	Land1 = new ContinuumEngine3D::Model("../Resources/Models/Land11.obj", "../Resources/Materials/Land11.mtl", "ParallaxShader", false, true);//8
	projectileModel = new ContinuumEngine3D::Model("../Resources/Models/projectile.obj", "../Resources/Materials/projectile.mtl", "glowShader", true, false);
	model = new ContinuumEngine3D::Model("../Resources/Models/Aircraft_obj.obj", "../Resources/Materials/Aircraft_obj.mtl", "glowShader", false, false);
	spawnerModel = new ContinuumEngine3D::Model("../Resources/Models/spawner.obj", "../Resources/Materials/spawner.mtl", "glowShader", false, false);

	Continuum_CollapseModel = new ContinuumEngine3D::Model("../Resources/Models/CCollapse.obj", "../Resources/Materials/CCollapse.mtl", "ParallaxShader", false, true);//13
	ContinuumLogoModel = new ContinuumEngine3D::Model("../Resources/Models/ContinuumEngineLogo.obj", "../Resources/Materials/ContinuumEngineLogo.mtl", "ParallaxShader", false, true);
	Game_OverModel = new ContinuumEngine3D::Model("../Resources/Models/GameOver.obj", "../Resources/Materials/GameOver.mtl", "ParallaxShader", false, true);
	High_ScoresModel = new ContinuumEngine3D::Model("../Resources/Models/HighScores.obj", "../Resources/Materials/HighScores.mtl", "ParallaxShader", false, true);





	//Creating Objects  //v0.00: scaling objects breaks collision

	character = new ContinuumEngine3D::GameObject(model);
	character->SetPosition(glm::vec3(10.0f, -7.0f, -6.0f));
	character->getBody()->getProxyShapesList()[0].setCollisionCategoryBits(0x0002);
	character->getBody()->getProxyShapesList()[0].setCollideWithMaskBits(0x0003);


	Land1Obj = new ContinuumEngine3D::GameObject(Land1);
	Land1Obj->SetPosition(glm::vec3(0.0f, 0.0f, -30.0f));
	Land1Obj->getBody()->getProxyShapesList()[0].setCollisionCategoryBits(0x0001);
	Land1Obj->getBody()->getProxyShapesList()[0].setCollideWithMaskBits(0x0009);

	Continuum_CollapseObj = new ContinuumEngine3D::GameObject(Continuum_CollapseModel);
	Continuum_CollapseObj->SetPosition(glm::vec3(0.0f, 0.0f, -26.0f));
	Continuum_CollapseObj->SetRotation(glm::vec3(1.0f, 0.0f, 0.0f));
	Continuum_CollapseObj->SetAngle(3.14);
	Continuum_CollapseObj->SetScale(glm::vec3(-0.9f, 0.9f, 0.9f));
	Continuum_CollapseObj->getBody()->getProxyShapesList()[0].setCollisionCategoryBits(0x0001);
	Continuum_CollapseObj->getBody()->getProxyShapesList()[0].setCollideWithMaskBits(0x0009);


	//character2 = new ContinuumEngine3D::GameObject(model);
	//character2->SetPosition(glm::vec3(-10.0f, -7.0f, -6.0f));
	//character2->getBody()->getProxyShapesList()[0].setCollisionCategoryBits(0x0002);
	//character2->getBody()->getProxyShapesList()[0].setCollideWithMaskBits(0x0003 | 0x0002);


	planetSpawner = new ContinuumEngine3D::GameObject(spawnerModel);
	planetSpawner->SetPosition(glm::vec3(0.0f, 0.0f, -40.0f));
	planetSpawner->getBody()->getProxyShapesList()[0].setCollisionCategoryBits(0x0001);
	planetSpawner->getBody()->getProxyShapesList()[0].setCollideWithMaskBits(0x0009);

	//Creating planet spawner
	planetSpawnerObject = new ContinuumEngine3D::PlanetSpawner(planetSpawner);
	for (auto planet_models : planetSpawnerObject->planetModels) {
		models.push_back(planet_models);
	}



	models.push_back(model);
	models.push_back(projectileModel);
	models.push_back(Land1);
	models.push_back(spawnerModel);
	models.push_back(Continuum_CollapseModel);

	objects.push_back(character);
	//objects.push_back(Land1Obj);

	//objects.push_back(character2);

	for (auto loadedModels : models) {

		if (!loadedModels) {
			return false;
		}
	}



	for (auto object : objects) {

		if (!object) {
			return false;
		}
	}

	return true;
}

void Game::Update(const float deltaTime_) {
	//Setting Game parameters
	//audioHandler->PlayMusic("Background.wav");
	k = ContinuumEngine3D::ContinuumEngine::GetInstance()->mContactManager->k_;
	moveSpeed = ContinuumEngine3D::ContinuumEngine::GetInstance()->mContactManager->moveSpeed_;

	moveObjects();
	checkKeymap();
	updateState();
}

void Game::Render() {

	ContinuumEngine3D::RenderMachine::GetInstance()->Render(models, delta);
	delta += 0.05f;

}

void Game::spawnPlanet() {
	int randomNumber = (int)(ContinuumEngine3D::ContinuumEngine::GetInstance()->Randomize(0.0f, 3.9f));
	int randomX = (int)(ContinuumEngine3D::ContinuumEngine::GetInstance()->Randomize(-10.0f, 10.0f));
	int randomY = (int)(ContinuumEngine3D::ContinuumEngine::GetInstance()->Randomize(-6.0f, 6.0f));
	planetSpawnerObject->spawnPlanet(randomNumber, randomX, randomY);

	objects.push_back(planetSpawnerObject->planetsObjs[planetSpawnerObject->planetsObjs.size() - 1]);

}

void Game::moveObjects() {
	ContinuumEngine3D::Camera::GetInstance()->SetPosition(ContinuumEngine3D::Camera::GetInstance()->GetPosition() + glm::vec3(0.0f, 0.0f, -k));
	planetSpawner->SetPosition(planetSpawner->GetPosition() + glm::vec3(0.0f, 0.0f, -k));
	Land1Obj->SetPosition(Land1Obj->GetPosition() + glm::vec3(0.0f, 0.0f, -k));
	Continuum_CollapseObj->SetPosition(Continuum_CollapseObj->GetPosition() + glm::vec3(0.0f, 0.0f, -k));
	if (characterAlive) {
		for (int i = 0; i < ContinuumEngine3D::Camera::GetInstance()->GetLightSources().size(); i++) {
			ContinuumEngine3D::Camera::GetInstance()->GetLightSources()[i]->SetPosition(ContinuumEngine3D::Camera::GetInstance()->GetLightSources()[i]->GetPosition() + glm::vec3(0.0f, 0.0f, -k));
		
		}
		for (int i = 0; i < projectileList.size(); i++) {

			projectileList[i]->SetPosition(projectileList[i]->GetPosition() + glm::vec3(0.0f, 0.0f, -k * 10.0f));

		}
	}


	if (characterAlive) {
		character->SetPosition(character->GetPosition() + glm::vec3(0.0f, 0.0f, -k));
	}

	//if (character2) {

	//	character2->SetPosition(character2->GetPosition() + glm::vec3(0.0f, 0.0f, -k));
	//}
	

}



void Game::updateState() {

	spawnTimer += 0.05;
	if (int(spawnTimer + 1.0f) % 6 == 0) {
		spawnTimer = 0.0f;
		spawnPlanet();
		//std::cout << "planet spawned" << std::endl;
	}
	if (delta > 10.0f) {

		Continuum_CollapseObj->SetPosition(Land1Obj->GetPosition() + glm::vec3(0.0f, 0.0f, -k ));
		//Continuum_CollapseObj->deleteInstance();
		//objects[i]->GetModel()->DeleteInstance(objects[i]->modelInstance);
		//objects.erase(objects.begin() + i);
		//objects.shrink_to_fit();
	}




	if (projectileAlive) {
		projectileShot += 0.05;
		if (int(projectileShot + 1.0f) % 2 == 0) {
			projectileAlive = false;
			projectileShot = 0.0f;
			//std::cout << projectileAlive << std::endl;
		}
	}


	ContinuumEngine3D::ContinuumEngine::GetInstance()->mContactManager->resetPoints();
	ContinuumEngine3D::ContinuumEngine::GetInstance()->world->testCollision(ContinuumEngine3D::ContinuumEngine::GetInstance()->mContactManager);

}

void Game::onCollision() {

	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->mBody->getId() == ContinuumEngine3D::ContinuumEngine::GetInstance()->collidingBody1 || objects[i]->mBody->getId() == ContinuumEngine3D::ContinuumEngine::GetInstance()->collidingBody2) {

			if (objects[i]->model->name == "../Resources/Models/Aircraft_obj.obj") {


			}


			objects[i]->mBody->setTransform(rp3d::Transform::identity());
			//std::cout << objects[i]->mBody->getId() << std::endl;
			score += 10.0f;
			objects[i]->deleteInstance();
				//objects[i]->GetModel()->DeleteInstance(objects[i]->modelInstance);
				objects.erase(objects.begin() + i);
				objects.shrink_to_fit();
				//objects.shrink_to_fit();
			if (i == 0) {
				characterAlive = false;
			}

		}
	}
	for (int j = 0; j < projectileList.size(); j++) {
		if (projectileList[j]->mBody->getId() == ContinuumEngine3D::ContinuumEngine::GetInstance()->collidingBody1 || projectileList[j]->mBody->getId() == ContinuumEngine3D::ContinuumEngine::GetInstance()->collidingBody2) {
			projectileList.erase(projectileList.begin() + j);
			projectileList.shrink_to_fit();
		}
	}
}


void Game::checkKeymap() {


	if (ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[0] == glm::vec2(1, 0) || ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[0] == glm::vec2(0, 1) || ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[0] == glm::vec2(1, 1)) {
		if (characterAlive) {
			character->SetPosition(character->GetPosition() + glm::vec3(-moveSpeed, 0.0f, 0.0f));
			//Camera::GetInstance()->SetPosition(glm::vec3(character->GetPosition().x + 10.0f, Camera::GetInstance()->GetPosition().y, character->GetPosition().z + 25.0f));
			rp3d::Transform transform = character->getBody()->getTransform();
			rp3d::Vector3 position = transform.getPosition();
			rp3d::Quaternion orientation = transform.getOrientation();
		}
	}
	if (ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[2] == glm::vec2(1, 0) || ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[2] == glm::vec2(0, 1) || ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[2] == glm::vec2(1, 1)) {
		if (characterAlive) {
			character->SetPosition(character->GetPosition() + glm::vec3(moveSpeed, 0.0f, 0.0f));
			//audioHandler->PlaySFX("EngineSound.wav", 0, 4);
			//Camera::GetInstance()->SetPosition(glm::vec3(character->GetPosition().x + 10.0f, Camera::GetInstance()->GetPosition().y, character->GetPosition().z + 25.0f));
		}

	}
	if (ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[1] == glm::vec2(1, 0) || ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[1] == glm::vec2(0, 1) || ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[1] == glm::vec2(1, 1)) {
		if (characterAlive) {
			character->SetPosition(character->GetPosition() + glm::vec3(0.0f, -moveSpeed, 0.0f));
		//	audioHandler->PlaySFX("EngineSound.wav", 0, 3);
		}
	}
	if (ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[3] == glm::vec2(1, 0) || ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[3] == glm::vec2(0, 1) || ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[3] == glm::vec2(1, 1)) {
		if (characterAlive) {
			character->SetPosition(character->GetPosition() + glm::vec3(0.0f, moveSpeed, 0.0f));
		//	audioHandler->PlaySFX("EngineSound.wav", 0, 5);
		}
	}
	if (ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[6] == glm::vec2(1, 0) || ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[6] == glm::vec2(0, 1) || ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[6] == glm::vec2(1, 1)) {
		if (characterAlive) {
			character->SetPosition(character->GetPosition() + glm::vec3(0.0f, 0.0f, -moveSpeed));
		//	audioHandler->PlaySFX("EngineSound.wav", 0, 6);
		}
	}
	if (ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[7] == glm::vec2(1, 0) || ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[7] == glm::vec2(0, 1) || ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[7] == glm::vec2(1, 1)) {
		if (characterAlive) {
			character->SetPosition(character->GetPosition() + glm::vec3(0.0f, 0.0f, moveSpeed));
		//	audioHandler->PlaySFX("EngineSound.wav", 0, 7);
		}
	}
	if (ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[4] == glm::vec2(1, 0) || ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[4] == glm::vec2(0, 1) || ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[4] == glm::vec2(1, 1)) {
		if (characterAlive) {
			character->SetAngle(character->GetAngle() + k * 0.1f);
		//	audioHandler->PlaySFX("EngineSound.wav", 0, 8);
			ContinuumEngine3D::ContinuumEngine::GetInstance()->mContactManager->k_ += 0.01f;
		}
	}
	if (ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[5] == glm::vec2(1, 0) || ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[5] == glm::vec2(0, 1) || ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[5] == glm::vec2(1, 1)) {
		if (characterAlive) {
			character->SetAngle(character->GetAngle() - k * 0.1f);
		//	audioHandler->PlaySFX("EngineSound.wav", 0, 2);
			ContinuumEngine3D::ContinuumEngine::GetInstance()->mContactManager->k_ += -0.01f;
		}
	}
	if (ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[10] == glm::vec2(1, 0) || ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[10] == glm::vec2(0, 1) || ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[10] == glm::vec2(1, 1)) {
		//Just play audio.
	
	}


	if (ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[9] == glm::vec2(1, 0) || ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[9] == glm::vec2(0, 1) || ContinuumEngine3D::ContinuumEngine::GetInstance()->keyMap[9] == glm::vec2(1, 1)) {

		if (characterAlive) {
			if (!projectileAlive) {
				projectileAlive = true;
				projectile = new ContinuumEngine3D::GameObject(projectileModel);
				projectile->SetPosition(character->GetPosition() + glm::vec3(0.0f, 0.0f, -8.0f));
				projectile->getBody()->getProxyShapesList()[0].setCollisionCategoryBits(0x0004);
				projectile->getBody()->getProxyShapesList()[0].setCollideWithMaskBits(0x0003);
				projectileList.push_back(projectile);
				objects.push_back(projectile);
				audioHandler->PlaySFX("FireSound.wav", 0, 1);
				//std::cout << projectileAlive << std::endl;
			}
		}

	}

}



//std::couts
//std::cout << character->GetBoundaryBox().minVert.x << " x " << character->GetBoundaryBox().minVert.y << " y " << character->GetBoundaryBox().minVert.z << " z " << std::endl;
//std::cout << character->GetBoundaryBox().maxVert.x << " x " << character->GetBoundaryBox().maxVert.y << " y " << character->GetBoundaryBox().maxVert.z << " z " << std::endl;
//std::cout << character->GetBoundaryBox().xyZ.x << " x " << character->GetBoundaryBox().xyZ.y << " y " << character->GetBoundaryBox().xyZ.z << " z " << std::endl;
//std::cout << character->GetBoundaryBox().xYz.x << " x " << character->GetBoundaryBox().xYz.y << " y " << character->GetBoundaryBox().xYz.z << " z " << std::endl;
//std::cout << character->GetBoundaryBox().Xyz.x << " x " << character->GetBoundaryBox().Xyz.y << " y " << character->GetBoundaryBox().Xyz.z << " z " << std::endl;
//std::cout << character->GetBoundaryBox().xYZ.x << " x " << character->GetBoundaryBox().xYZ.y << " y " << character->GetBoundaryBox().xYZ.z << " z " << std::endl;
//std::cout << character->GetBoundaryBox().XyZ.x << " x " << character->GetBoundaryBox().XyZ.y << " y " << character->GetBoundaryBox().XyZ.z << " z " << std::endl;
//std::cout << character->GetBoundaryBox().XYz.x << " x " << character->GetBoundaryBox().XYz.y << " y " << character->GetBoundaryBox().XYz.z << " z " << std::endl;
//std::cout << character->GetBoundaryBox().xSize << " xSize " << std::endl;
//std::cout << character->GetBoundaryBox().ySize << " ySize " << std::endl;
//std::cout << character->GetBoundaryBox().zSize << " zSize " << std::endl;


//std::cout << "position: (" << position.x << " , " << position.y << " , " << position.z << "); " << std::endl;
//std::cout << "orientation: (" << orientation.x << " , " << orientation.y << " , " << orientation.z << "); " << std::endl;
