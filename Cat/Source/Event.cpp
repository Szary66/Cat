#include "Event.h"

namespace SDL
{
	Event::Event ()
	{
		_event = new SDL_Event;
	}


	Event::~Event ()
	{
		delete _event;
	}

	bool Event::poll ()
	{
		return (bool)SDL_PollEvent (_event);
	}

	SDL_Keycode& Event::key ()const
	{
		return _event->key.keysym.sym;
	}

	Uint32& Event::type ()const
	{
		return _event->type;
	}

	const SDL_Event* Event::event ()const
	{
		return _event;
	}
}