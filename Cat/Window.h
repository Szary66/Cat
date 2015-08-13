#ifndef WINDOW_H
#define WiNDOW_H
#include <cstdint>
#include <SDL.h>
namespace SDL
{
	bool initMultimedia ();
	


	class Window
	{
	public:
		Window (char*, size_t x, size_t y, size_t w, size_t h, SDL_WindowFlags f);
		~Window ();

		const size_t width;
		const size_t height;
		const size_t x;
		const size_t y;

		SDL_Window* window ()const
		{return _window;}
	private:
		SDL_Window* _window;
	};
}

#endif