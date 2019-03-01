#include "ContinuumEngine.h"

std::unique_ptr<ContinuumEngine> ContinuumEngine::engineInstance = nullptr;

ContinuumEngine::ContinuumEngine() : window(nullptr), isRunning(false), fps(120) {
}


ContinuumEngine::~ContinuumEngine() {
	Shutdown();
}

ContinuumEngine* ContinuumEngine::GetInstance() {
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new ContinuumEngine);
	}
	return engineInstance.get();
}

bool ContinuumEngine::Initialize(std::string name_, int width_, int height_) {
	Debug::DebugInit();
	Debug::SetSeverity(MessageType::TYPE_INFO);

	window = new Window();

	if (!window->Initialize(name_, width_, height_)) {
		Debug::FatalError("Window failed to initialize", __FILE__, __LINE__);
		//Shutdown();
		return isRunning = false;
	}

	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);
	MouseEventListener::RegisterEngineObject(this);

	ShaderHandler::GetInstance()->CreateProgram("colourShader", "Engine/Renderer/Graphics/Shaders/ColourVertexShader.glsl", "Engine/Renderer/Graphics/Shaders/ColourFragmentShader.glsl");

	ShaderHandler::GetInstance()->CreateProgram("baseShader", "Engine/Renderer/Graphics/Shaders/VertexShader.glsl", "Engine/Renderer/Graphics/Shaders/FragmentShader.glsl");
	if (gameInterface) {
		if (!gameInterface->Initialize()) {
			Debug::FatalError("GameInterface failed to initialize", __FILE__, __LINE__);
			return isRunning = false;
		}
	}
	Debug::Info("initied", __FILE__, __LINE__);
	timer.Start();
	return isRunning = true;
}

void ContinuumEngine::Run() {
	while (isRunning) {
		EventListener::Update();
		timer.UpdateFrameTicks();
		Update(timer.getDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}
	if (!isRunning) {
		Shutdown();
	}
}

bool ContinuumEngine::GetIsRunning() {
	return isRunning;
}

void ContinuumEngine::Update(const float deltaTime_) {
	if (gameInterface) {
		gameInterface->Update(deltaTime_);
	}
}

void ContinuumEngine::Render() {
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (gameInterface) {
		gameInterface->Render();
	}

	SDL_GL_SwapWindow(window->GetWindow());
}

void ContinuumEngine::Shutdown() {

	delete window;
	window = nullptr;

	delete gameInterface;
	gameInterface = nullptr;

	SDL_Quit();
	exit(0);
}

void ContinuumEngine::SetGameInterface(GameInterface* gameInterface_) {
	gameInterface = gameInterface_;
}

glm::vec2 ContinuumEngine::GetScreenSize() const {
	return glm::vec2(window->GetWidth(), window->GetHeight());
}


void ContinuumEngine::NotifyOfMousePressed(int x_, int y_) {

}
void ContinuumEngine::NotifyOfMouseReleased(int x_, int y_, int buttonType_) {

}
void ContinuumEngine::NotifyOfMouseMove(int x_, int y_) {
	Camera::GetInstance()->ProcessMouseMovement(MouseEventListener::GetMouseOffset().x, MouseEventListener::GetMouseOffset().y);

}
void ContinuumEngine::NotifyOfMouseScroll(int y_) {
	Camera::GetInstance()->ProcessMouseZoom(y_);
}
void ContinuumEngine::ExitGame() {
	isRunning = false;
}