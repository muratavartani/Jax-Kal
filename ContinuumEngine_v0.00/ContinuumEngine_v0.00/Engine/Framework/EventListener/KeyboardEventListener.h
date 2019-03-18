#ifndef KEYBOARDEVENTHANDLER_H
#define KEYBOARDEVENTHANDLER_H
#include <SDL.h>
#include <string>

using namespace std;

class KeyboardEventListener
{
public:
	KeyboardEventListener() = delete;
	KeyboardEventListener(const KeyboardEventListener&) = delete;
	KeyboardEventListener(KeyboardEventListener&&) = delete;
	KeyboardEventListener& operator=(const KeyboardEventListener&) = delete;
	KeyboardEventListener& operator=(KeyboardEventListener&&) = delete;

	static void onKeyDown(SDL_Event e_);
	static void onKeyHold(SDL_Event e_);
	static void Update(SDL_Event e_);
	static void onKeyReleased(SDL_Event e_);

private:

};

#endif