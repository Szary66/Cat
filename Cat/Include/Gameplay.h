#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include "Manager.h"
#include "Event.h"
#include <ctime>
#include <array>

namespace Game
{
	class Gameplay
	{
	public:
		Gameplay (SDL_Renderer*, Game::Manager&);

		void loop (SDL_Renderer*, SDL::Event&);

	private:
		void clear (SDL_Renderer*);
		void update (SDL::Event&, SDL_Renderer*);
		void draw (SDL_Renderer*);
		void handingEvent (SDL::Event&);
		
		void restartDroped (SDL_Renderer*);
		//only for dropeds
		void move ();
		

		Game::Manager& _manager;

		bool _quit;

		std::array<std::weak_ptr<SDL::BMP>, 2> _background;
		std::vector<std::weak_ptr<SDL::BMP>> _dropeds;

		std::weak_ptr<SDL::BMP> _cat;

		SDL::Text _showedScore;


		size_t _speedDrop;
		size_t _score;
		size_t _timedrop;
	};
}
#endif