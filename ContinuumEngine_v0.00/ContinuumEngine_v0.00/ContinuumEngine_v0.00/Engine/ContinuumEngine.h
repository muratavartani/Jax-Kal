#ifndef CONTINUUMENGINE_H
#define CONTINUUMENGINE_H

#include "Framework/Window/Window.h"
#include "GlobalElements/Timer.h"
#include "GameInterface.h"
//#include "../Rendering/3D/Triangle.h"
//#include "../Rendering/3D/Square.h"
//#include "../Rendering/3D/Cube.h"
#include "Renderer/Graphics/ShaderHandler.h"
#include "Renderer/Graphics/TextureHandler.h"
#include "Camera/Camera.h"
#include "Renderer/GameObject/GameObject.h"
#include "Framework/EventListener/EventListener.h"
#include "Renderer/Graphics/Skybox.h"

#include <memory>

class ContinuumEngine {
public:
	ContinuumEngine(const ContinuumEngine&) = delete;
	ContinuumEngine(ContinuumEngine&&) = delete;
	ContinuumEngine& operator=(const ContinuumEngine&) = delete;
	ContinuumEngine& operator=(ContinuumEngine&&) = delete;



	bool Initialize(std::string name_, int width_, int height_);
	void Run();
	bool GetIsRunning();
	void SetGameInterface(GameInterface* gameInterface_);

	static ContinuumEngine* GetInstance();
	glm::vec2 GetScreenSize() const;
	Timer timer;
	unsigned int hdrFBO;
	unsigned int colorBuffers[2];
	unsigned int rboDepth;
	unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	unsigned int pingpongFBO[2];
	unsigned int pingpongColorbuffers[2];
	bool bloom = false;
	float exposure = 1.1f;

	void renderQuad();

	void NotifyOfMousePressed(int x_, int y_);
	void NotifyOfMouseReleased(int x_, int y_, int buttonType_);
	void NotifyOfMouseMove(int x_, int y_);
	void NotifyOfMouseScroll(int y_);
	void ExitGame();
private:
	ContinuumEngine();
	~ContinuumEngine();

	static std::unique_ptr<ContinuumEngine> engineInstance;
	friend std::default_delete<ContinuumEngine>;

	void Update(const float deltaTime_);
	void Render();
	void Shutdown();

	Window* window;
	
	GameInterface* gameInterface;
	bool isRunning;
	unsigned int fps;
};

#endif 