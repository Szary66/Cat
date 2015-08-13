#include "Window.h"
#include "Event.h"
#include "BMP.h"
#include "Text.h"
#include "Menu.h"
#include "Manager.h"
#undef main



int main ()
{
	SDL::initMultimedia ();
	SDL::initText ();

	SDL::Window window ("CAT", 200, 200, 800, 600, SDL_WINDOW_SHOWN);
	SDL::Event event;

	SDL_Renderer* renderer = SDL_CreateRenderer (window.window (), 0, SDL_RENDERER_ACCELERATED);

	Game::Manager m (renderer);


	std::vector < std::shared_ptr<SDL::Text>> messages;


	messages.push_back (std::make_shared<SDL::Text> ("START", "../images/text.ttf"));
	messages.push_back (std::make_shared<SDL::Text> ("POMOC", "../images/text.ttf"));
	messages.push_back (std::make_shared<SDL::Text> ("WYJSCIE", "../images/text.ttf"));

	for ( auto i = messages.begin (); i != messages.end (); i++ )
	{
		( *i ).get ()->surfaceFromTTF (SDL_Color { 0, 0, 0, 0 });
		( *i ).get ()->textureFromSurface (renderer);
	}

	messages [0].get ()->rectangle = { 800 / 2 - 150, 80, 300, 80 };
	messages [1].get ()->rectangle = { 800 / 2 - 150, 200, 300, 80 };
	messages [2].get ()->rectangle = { 800 / 2 - 150, 320, 300, 80 };

	std::vector<std::weak_ptr<SDL::Text>> weak;
	weak.push_back (messages [0]);
	weak.push_back (messages [1]);
	weak.push_back (messages [2]);

	Game::Menu menu (weak, m, renderer, false,15);

	menu.loop (event, renderer);

	return 0;
}

