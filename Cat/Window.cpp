#include "Window.h"

namespace SDL
{
	Window::Window (char* name, size_t x, size_t y, size_t w, size_t h, SDL_WindowFlags f)
		:x (x), y (y), width (w), height (h)
	{
		_window = SDL_CreateWindow (name, x, y, w, h, f);
	}

	Window::~Window ()
	{
		SDL_DestroyWindow (_window);
	}
	
	bool initMultimedia () 
	{
		return !SDL_Init (SDL_INIT_EVERYTHING);
	}
}