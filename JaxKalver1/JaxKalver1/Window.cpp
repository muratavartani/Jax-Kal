#include <iostream>
#include "GL/glew.h"
#include <GL/gl.h>
#include "SDL.h"
#include <cassert>
#include "Debug.h"
#include "Window.h"

using namespace JAX;

Window::Window() :windowPtr(nullptr), winRect(), glContext(nullptr), isInitialized(false), isFullScreen(false) {

}

Window::~Window() {
	OnDestroy();

}

bool Window::OnCreate() {
	isInitialized = false;

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); ///Enable Dept Cueing (Z-buffer)
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); //Turn on double buffering with 24bit Z buffer. We need to decide how much depth we need later.
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	//Im not sure what the following is, neither do scott so we better look what these are.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		Debug::Log(EMessageType::FATAL_ERROR, std::string(SDL_GetError()), __FILE__, __LINE__);
		return isInitialized;
	}

	///Create SDL Window
	windowPtr = SDL_CreateWindow("JAX & KAL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winRect.w, winRect.h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (windowPtr == nullptr) {
		Debug::Log(EMessageType::FATAL_ERROR, SDL_GetError(), __FILE__, __LINE__);
		return false;
	}

	///Attach OpenGL to the new Window
	glContext = SDL_GL_CreateContext(windowPtr);
	if (glContext == nullptr) {
		Debug::Log(EMessageType::FATAL_ERROR, SDL_GetError(), __FILE__, __LINE__);
		return false;
	}

	/// Fire up the GL Extension Wrangler<Im not sure what is this
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		Debug::Log(EMessageType::FATAL_ERROR, (char*)glewGetErrorString(glewError), __FILE__, __LINE__);
		assert(0);
	}

	/// This makes the buffer swap syncronize with the monitor's vertical refresh<donno
	if (SDL_GL_SetSwapInterval(1) < 0) {
		Debug::Log(EMessageType::WARNING, SDL_GetError(), __FILE__, __LINE__);
	}

	Debug::Log(EMessageType::INFO, (char*)glewGetString(GLEW_VERSION), __FILE__, __LINE__);

	GetInstalledOpenGLInfo();

	isInitialized = true;
	return true;
}



void Window::GetInstalledOpenGLInfo() {
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

	std::cout << "GL Version " << version << std::endl;
	std::cout << "Graphics card vendor " << vendor << std::endl;
	std::cout << "Graphics card name " << renderer << std::endl;
	std::cout << "GLSL Version " << glslVersion << std::endl;
}

void Window::OnDestroy() {
	SDL_DestroyWindow(windowPtr);
	SDL_Quit();
	SDL_GL_DeleteContext(glContext);
	windowPtr = nullptr;
	glContext = nullptr;
	isInitialized = false;
}

void Window::SetWindowSize(const int width_, const int height_) {
	winRect.w = width_;
	winRect.h = height_;
}

void Window::ToggleFullScreen() {
	isFullScreen = !isFullScreen;
	SDL_SetWindowFullscreen(windowPtr, (isFullScreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_SHOWN));
}

int Window::GetHeight() const {
	return winRect.w;
}

int Window::GetWidth() const {
	return winRect.h;
}