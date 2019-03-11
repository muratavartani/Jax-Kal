#include "EventListener.h"
#include "../../ContinuumEngine.h"


void EventListener::Update()
{
	SDL_Event SDLEvent;
	while (SDL_PollEvent(&SDLEvent)) {
		switch (SDLEvent.type)
		{
		case SDL_QUIT:
			ContinuumEngine::GetInstance()->ExitGame();
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEWHEEL:
			MouseEventListener::Update(SDLEvent);
			break;
		case SDL_KEYDOWN:
			KeyboardEventListener::Update(SDLEvent);
			break;
		case SDL_KEYUP:
			KeyboardEventListener::Update(SDLEvent);
			break;
		default:
			break;

		}
	}
}


