#pragma once
#include <ContinuumEngine3D/Engine/Renderer/Graphics/RenderMachine.h>
#include <OpenGL/glm/gtx/string_cast.hpp>
#include <ContinuumEngine3D/Engine/Renderer/GameObject/PlanetSpawner.h>
#include <ContinuumEngine3D/Engine/GameInterface.h>
#include <ContinuumEngine3D/Engine/Camera/Camera.h>

class Game : public ContinuumEngine3D::GameInterface
{
public:
	Game();
	virtual ~Game();

	virtual bool Initialize();
	virtual void Update(const float deltaTime_);
	virtual void Render();
	void moveObjects();
	void checkKeymap();
	void updateState();
	void spawnPlanet();
	virtual void onCollision();

	float score = 0.0f;
	float k = 0.3f;
	float moveSpeed = 0.15f;
	bool projectileAlive = false;
	float projectileShot = 0.0f;
	float delta = 0.0f;
	float spawnTimer = 0.0f;
	std::vector<ContinuumEngine3D::GameObject*> objects;
	ContinuumEngine3D::PlanetSpawner* planetSpawnerObject;

private:
	ContinuumEngine3D::Model * model;
	ContinuumEngine3D::Model * projectileModel;
	ContinuumEngine3D::Model * Land1;
	ContinuumEngine3D::Model * spawnerModel;
	ContinuumEngine3D::Model * Continuum_CollapseModel;
	ContinuumEngine3D::Model * ContinuumLogoModel;
	ContinuumEngine3D::Model * Game_OverModel;
	ContinuumEngine3D::Model * High_ScoresModel;
	std::vector<ContinuumEngine3D::Model*> models;
	ContinuumEngine3D::GameObject* projectileObj;
	ContinuumEngine3D::GameObject* character;
	ContinuumEngine3D::GameObject* Land1Obj;
	ContinuumEngine3D::GameObject* projectile;
	ContinuumEngine3D::GameObject* planetSpawner;
	ContinuumEngine3D::GameObject* ContinuumLogoObj;
	ContinuumEngine3D::GameObject* Continuum_CollapseObj;
	ContinuumEngine3D::GameObject* Game_OverObj;
	ContinuumEngine3D::GameObject* High_ScoresObj;



	bool characterAlive = true;

	std::vector<ContinuumEngine3D::GameObject*> projectileList;


	ContinuumEngine3D::AudioHandler* audioHandler;

};
