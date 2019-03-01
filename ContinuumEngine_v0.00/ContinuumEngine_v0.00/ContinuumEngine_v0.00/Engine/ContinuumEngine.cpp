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
	//"colourShader"
	ShaderHandler::GetInstance()->CreateProgram("colourShader", "Engine/Renderer/Graphics/Shaders/ColourVertexShader.glsl", "Engine/Renderer/Graphics/Shaders/ColourFragmentShader.glsl");
	//"baseShader"
	ShaderHandler::GetInstance()->CreateProgram("baseShader", "Engine/Renderer/Graphics/Shaders/VertexShader.glsl", "Engine/Renderer/Graphics/Shaders/FragmentShader.glsl");

	//Shaders for glow("glowShader")
	ShaderHandler::GetInstance()->CreateProgram("bloomShader", "Engine/Renderer/Graphics/Shaders/VertexShader.glsl", "Engine/Renderer/Graphics/Shaders/BloomFragmentShader.glsl");
	ShaderHandler::GetInstance()->CreateProgram("bloomLightShader", "Engine/Renderer/Graphics/Shaders/VertexShader.glsl", "Engine/Renderer/Graphics/Shaders/BloomLightFragmanetShader.glsl");
	ShaderHandler::GetInstance()->CreateProgram("blurShader", "Engine/Renderer/Graphics/Shaders/BlurVertexShader.glsl", "Engine/Renderer/Graphics/Shaders/BlurFragmentShader.glsl");
	ShaderHandler::GetInstance()->CreateProgram("bloomFinalShader", "Engine/Renderer/Graphics/Shaders/BlurVertexShader.glsl", "Engine/Renderer/Graphics/Shaders/BloomFinalFragmentShader.glsl");

	//"SkyboxShader"
	ShaderHandler::GetInstance()->CreateProgram("SkyboxShader", "Engine/Renderer/Graphics/Shaders/SkyboxVertexShader.glsl", "Engine/Renderer/Graphics/Shaders/SkyboxFragmentShader.glsl");

	if (gameInterface) {
		if (!gameInterface->Initialize()) {
			Debug::FatalError("GameInterface failed to initialize", __FILE__, __LINE__);
			return isRunning = false;
		}
	}

	glEnable(GL_DEPTH_TEST);

	
	glGenFramebuffers(1, &hdrFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
	// create 2 floating point color buffers (1 for normal rendering, other for brightness treshold values)
	
	glGenTextures(2, colorBuffers);
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 800, 600, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// attach texture to framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
	}
	// create and attach depth buffer (renderbuffer)
	
	glGenRenderbuffers(1, &rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 800, 600);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
	// tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 

	glDrawBuffers(2, attachments);
	// finally check if framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// ping-pong-framebuffer for blurring

	glGenFramebuffers(2, pingpongFBO);
	glGenTextures(2, pingpongColorbuffers);
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 800, 600, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);
		// also check if framebuffers are complete (no need for depth buffer)
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;
	}


	glUseProgram(ShaderHandler::GetInstance()->GetShader("bloomShader"));
	glUniform1i(glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("bloomShader"), "diffuseTexture"), 0);
	glUseProgram(ShaderHandler::GetInstance()->GetShader("blurShader"));
	glUniform1i(glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("blurShader"), "image"), 0);
	glUseProgram(ShaderHandler::GetInstance()->GetShader("bloomFinalShader"));
	glUniform1i(glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("bloomFinalShader"), "scene"), 0);
	glUniform1i(glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("bloomFinalShader"), "bloomBlur"), 1);

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
	
	glClearColor(0.160f, 0.048f, 0.320f, 1.0f);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (gameInterface) {
		gameInterface->Render();
	}

	SDL_GL_SwapWindow(window->GetWindow());
}


void ContinuumEngine::renderQuad()
{
	unsigned int quadVAO = 0;//!up
	unsigned int quadVBO;
	if (quadVAO == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);
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
	bloom = true;
}
void ContinuumEngine::NotifyOfMouseReleased(int x_, int y_, int buttonType_) {
	bloom = false;
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