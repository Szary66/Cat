#ifndef MENU_H
#define MENU_H
#include <vector>
#include <memory>
#include <cstdint>
#include "Event.h"
#include "Gameplay.h"
#include "Text.h"
#include "Manager.h"
namespace Game
{
	class Menu
	{
	public:
		Menu (std::vector<std::weak_ptr<SDL::Text>>, Game::Manager&, SDL_Renderer*, bool, size_t);

		void loop (SDL::Event&, SDL_Renderer*);
	private:
		void draw (SDL_Renderer*);
		void update (SDL::Event&, SDL_Renderer*);
		void clear (SDL_Renderer*);
		void run (SDL::Event&, SDL_Renderer*);
		void gameplay (SDL::Event&, SDL_Renderer*);
		void instruction (SDL::Event&, SDL_Renderer*);


		std::vector<std::weak_ptr<SDL::Text>> _messages;

		std::weak_ptr<SDL::BMP> _background;
		std::vector<std::weak_ptr<SDL::Text>>::iterator _selected;
		Game::Manager& _manager;

		bool _quit;
		bool _onlyShow;
	};
}

#endif