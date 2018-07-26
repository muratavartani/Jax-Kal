#include "SceneManager.h"
#include "Debug.h"
#include "Timer.h"
#include "GameScene.h"
#include <cassert>

using namespace JAX;

std::unique_ptr<SceneManager> SceneManager::instance(nullptr);

SceneManager::SceneManager() : windowInstance(), currentScene(nullptr), isRunning(false) {
	frameRate = 60;
}

SceneManager::~SceneManager() {
	windowInstance.OnDestroy();
	isRunning = false;
}

SceneManager* SceneManager::getInstance() {
	if (instance.get() == nullptr) {
		/// I originally set the unique_ptr to be null in the constructor - 
		/// reset() sets the new address
		instance.reset(new SceneManager());
	}
	return instance.get();
}

void SceneManager::Run() {
	isRunning = Initialize();/// Initialize the window and setup OpenGL
	Timer timer;
	timer.Start();

	//MASTER LOOP OF THE GAME
	while (isRunning) {
		timer.UpdateFrameTicks();

		HandleEvents();
		Update(timer.GetDeltaTime());
		Render();


		/// Keeep the event loop running at a sane rate
		SDL_Delay(timer.GetSleepTime(frameRate));
		//std::cout << "main loop running at: " << (1.0f/timer.GetDeltaTime()) << " frames/sec" << std::endl;
	}
}

void SceneManager::HandleEvents() {
	SDL_Event SDLEvent;

	while (SDL_PollEvent(&SDLEvent)) {

		switch (SDLEvent.type) {
		case SDL_EventType::SDL_QUIT:
			isRunning = false;
			return;
		case SDL_EventType::SDL_MOUSEBUTTONDOWN:
		case SDL_EventType::SDL_MOUSEBUTTONUP:
		case SDL_EventType::SDL_MOUSEMOTION:

			assert(currentScene);
			currentScene->HandleEvents(SDLEvent);
			break;
		case SDL_EventType::SDL_KEYDOWN:
			switch (SDLEvent.key.keysym.sym) {
			case SDLK_F1:
				if (currentScene) delete currentScene;
				currentScene = new GameScene(windowInstance);
				currentScene->OnCreate();
				break;
			case SDLK_F2:



				break;

			case SDLK_ESCAPE:
				windowInstance.ToggleFullScreen();
				break;

			case SDLK_q:
				isRunning = false;
				return;
			default:
				currentScene->HandleEvents(SDLEvent);
				break;
			}

			break;
		case SDL_WINDOWEVENT:
			if (SDLEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				currentScene->OnResize(SDLEvent.window.data1, SDLEvent.window.data2);
			}
			break;
		default:
			break;
		}
	}
}

void SceneManager::Update(const float deltaTime) {
	assert(currentScene);
	currentScene->Update(deltaTime);
}

void SceneManager::Render() const {
	assert(currentScene);
	currentScene->Render();
}


bool SceneManager::Initialize() {
	Debug::Log(EMessageType::INFO, "Initializing the window and first scene", __FILE__, __LINE__);

	windowInstance.SetWindowSize(1024, 740);
	bool status = windowInstance.OnCreate();
	if (status == false) {
		Debug::Log(EMessageType::FATAL_ERROR, "Failed to initialize a Window and/or OpenGL", __FILE__, __LINE__);
		throw std::string("Failed to initialize a Window and/or OpenGL");
	}


	currentScene = new GameScene(windowInstance);

	if (currentScene == nullptr) {
		Debug::Log(EMessageType::FATAL_ERROR, "Failed to initialize the Scene", __FILE__, __LINE__);
		throw std::string("Failed to initialize the Scene");
	}
	if (currentScene->OnCreate() == false) return false;
	return true;
}