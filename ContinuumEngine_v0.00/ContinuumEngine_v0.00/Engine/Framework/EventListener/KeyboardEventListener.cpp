#include "KeyboardEventListener.h"
#include <stdio.h>

void KeyboardEventListener::Update(SDL_Event e_)
{
	if (e_.key.repeat)
	{
		onKeyHold(e_);
	}
	else
	{
		onKeyDown(e_);
	}

	if (e_.key.state == SDL_RELEASED) //When state is at 0
	{
		onKeyReleased(e_);
	}
}

void KeyboardEventListener::onKeyDown(SDL_Event e_)
{
	switch (e_.key.keysym.sym)
	{
	case SDLK_a:
		printf("a key pressed");
		break;
	case SDLK_s:
		printf("s key pressed");
		break;
	case SDLK_d:
		printf("d key pressed");
		break;
	case SDLK_w:
		printf("w key pressed");
		break;
	case SDLK_SPACE:
		printf("Space key pressed");
		break;
	}
}
void KeyboardEventListener::onKeyHold(SDL_Event e_)
{
	switch (e_.key.keysym.sym)
	{
	case SDLK_a:
		printf("a is being held down");
		break;
	case SDLK_s:
		printf("s is being held down");
		break;
	case SDLK_d:
		printf("d is being held down");
		break;
	case SDLK_w:
		printf("w is being held down");
		break;
	case SDLK_SPACE:
		printf("Space is being held down");
		break;
	}

}

void KeyboardEventListener::onKeyReleased(SDL_Event e_)
{
	switch (e_.key.keysym.sym)
	{
	case SDLK_a:
		printf("a has been released");
		break;
	case SDLK_s:
		printf("s has been released");
		break;
	case SDLK_d:
		printf("d has been released");
		break;
	case SDLK_w:
		printf("w has been released");
		break;
	case SDLK_SPACE:
		printf("Space has been released");
		break;
	}
}



