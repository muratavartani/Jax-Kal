#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"

namespace JAX {
	class Window {
	public:
		Window();
		~Window();

		///kill any default constructor or operator that the compiler might create
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator = (const Window&) = delete;
		Window& operator = (Window&&) = delete;

		bool OnCreate();
		void OnDestroy();
		void SetWindowSize(const int Width_, const int Height_);
		void ToggleFullScreen();
		int GetWidth() const;
		int GetHeight() const;
		inline SDL_Window* getSDLWindow() { return windowPtr; }

	protected:
		void GetInstalledOpenGLInfo();
	private:
		SDL_Window * windowPtr;
		SDL_GLContext glContext;
		SDL_Rect winRect;
		bool isInitialized;
		bool isFullScreen;


	};
}
#endif
