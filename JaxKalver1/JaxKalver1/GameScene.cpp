
#include <GL/glew.h>
#include <SDL.h>
#include <iostream>
#include "MMath.h"
#include "Window.h"
#include "Shader.h"
#include "GameScene.h"
#include "SceneEnvironment.h"
//#include "Trackball.h"
#include "Model.h"

#include "ObjLoader.h"

using namespace JAX;
using namespace MATH;

//Trackball* trackball;
bool mouseMoving;
GameScene::GameScene(Window& windowRef) :Scene(windowRef) {

}


bool GameScene::OnCreate() {

	camera = nullptr;
	OnResize(windowPtr->GetWidth(), windowPtr->GetHeight());


	/// Load Assets: as needed 
	if (addModel("sphere.obj") == false) {
		return false;
	}

	/// Create a shader with attributes
	SceneEnvironment::getInstance()->setLight(Vec3(0.0f, 3.0f, 7.0f));
	models[models.size() - 1]->Rotate(Vec3(30.0f, 0.0f, 0.0f));

	//trackball = new Trackball();
	return true;
}


bool JAX::GameScene::addModel(const char* filename)
{
	models.push_back(new Model(Vec3(0.0f, 0.0f, 1.0f), Vec3(1.0f, 1.0f, 1.0f)));
	models[models.size() - 1]->OnCreate();

	if (models[models.size() - 1]->LoadMesh(filename) == false) {
		return false;
	}
	return true;
}

void GameScene::OnResize(int w_, int h_) {
	windowPtr->SetWindowSize(w_, h_);
	glViewport(0, 0, windowPtr->GetWidth(), windowPtr->GetHeight());
	if (camera) delete camera;
	camera = new Camera(w_, h_, Vec3(0.0f, 0.0f, 10.0f));
	Camera::currentCamera = camera;
}

void GameScene::Update(const float deltaTime) {
	for (Model* model : models) {
		model->Update(deltaTime);

	}
/*
	if (mouseMoving) {
		Matrix4 rotMatrix = trackball->GetMatrix4();
		//models[models.size()-1]->Rotate(Vec3(120.0f * deltaTime, 120.0f * deltaTime, 120.0f * deltaTime));
		Vec4 ori = models[models.size() - 1]->getModelOrientation();

		//rotMatrix.print();

		//printf("ori %f %f %f  \n", ori.x, ori.y, ori.z);
		models[models.size() - 1]->setRotationMatrix(rotMatrix);
		//
		//models[models.size() - 1]->Rotate(Vec3(90.0f * deltaTime, 90.0f * deltaTime, 0.0f * deltaTime));
	}*/
}

void GameScene::Render() const {

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/// Draw your scene here
	for (Model* model : models) {
		model->Render();
	}

	SDL_GL_SwapWindow(windowPtr->getSDLWindow());

}

void GameScene::HandleEvents(const SDL_Event& SDLEvent) {
	/*if(SDLEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN){

	}
	if (SDLEvent.type == SDL_EventType::SDL_MOUSEMOTION &&
	SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {

	}*/


	if (SDLEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
		Matrix4 m = MMath::inverse(MMath::viewportNDC(windowPtr->GetWidth(), windowPtr->GetHeight()));

		Vec3 v1((float)SDLEvent.button.x, (float)SDLEvent.button.y, 0.0f);
		//Vec3 pos = m * v1;
		//pos.z = sqrt(1.0f - (pos.x * pos.x) - (pos.y * pos.y));

		//trackball.OnLeftMouseDown(v1.x, v1.y);
										//trackball->OnLeftMouseDown(SDLEvent.button.x, SDLEvent.button.y);

		//angle = acos(VMath::dot(v, pos));
		//angle = angle * 180.0f / M_PI;
		//Vec3 axisOfRotation = VMath::cross(v, pos);
		//printf("%f \n", angle);

		//printf("mousedown %f %f %f  \n", v1.x, v1.y, v1.z);

	}
	if (SDLEvent.type == SDL_EventType::SDL_MOUSEMOTION &&
		SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		mouseMoving = true;
		Matrix4 m = MMath::inverse(MMath::viewportNDC(windowPtr->GetWidth(), windowPtr->GetHeight()));

		Vec3 v2((float)SDLEvent.button.x, (float)SDLEvent.button.y, 0.0f);
		//Vec3 pos = m * v2;
		//pos.z = sqrt(1.0f - (pos.x * pos.x) - (pos.y * pos.y));
		//trackball.OnMouseMove(v2.x, v2.y);
										//trackball->OnMouseMove(SDLEvent.button.x, SDLEvent.button.y);

		//angle = acos(VMath::dot(v, pos));
		//angle = angle * 180.0f / M_PI;
		//Vec3 axisOfRotation = VMath::cross(v, pos);

		//printf("%f \n", angle);
		//printf("mousedown %f %f %f  \n", v2.x, v2.y, v2.z);


	}
	if (SDLEvent.type == SDL_EventType::SDL_MOUSEBUTTONUP) {
		mouseMoving = false;

	}

}

GameScene::~GameScene() {
	OnDestroy();
}

void GameScene::OnDestroy() {
	/// Cleanup Assets
	if (camera) delete camera;
	for (Model* model : models) {
		if (model) delete model;
	}
	//delete trackball;
}
