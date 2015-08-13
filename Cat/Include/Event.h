#ifndef EVENT_H
#define EVENT_H
#include <SDL.h>

namespace SDL
{
	class Event
	{
	public:
		Event ();
		~Event ();
		bool poll ();

		SDL_Keycode& key ()const;
		Uint32& type ()const;

		const SDL_Event* event ()const;
	private:
		SDL_Event* _event;
	};
}
#endif