#include "Menu.h"


namespace Game
{
	Menu::Menu (std::vector<std::weak_ptr<SDL::Text>> mesage, Game::Manager& manager, SDL_Renderer* renderer, bool onlyShow, size_t bg)
		:_messages (mesage), _manager (manager), _onlyShow (onlyShow)
	{
		_background = _manager.BMP (bg);

		_background._Get ()->rectangle = { 0, 0, 800, 600 };

		if ( !_onlyShow )
		{
			_selected = _messages.begin ();
			( *_selected )._Get ()->changeColor (SDL_Color { 255, 255, 255, 0 }, renderer);
		}
	}

	void Menu::draw (SDL_Renderer* renderer)
	{
		SDL_RenderCopy (renderer, _background._Get ()->texture (), nullptr, &_background._Get ()->rectangle);

		for ( auto i = _messages.begin (); i != _messages.end (); i++ )
			SDL_RenderCopy (renderer, ( *i )._Get ()->texture (), nullptr, &( *i )._Get ()->rectangle);

		SDL_RenderPresent (renderer);
	}

	void Menu::loop (SDL::Event& ev, SDL_Renderer* renderer)
	{
		_quit = false;
		while ( ev.type () != SDL_QUIT && !_quit )
		{
			clear (renderer);
			update (ev, renderer);
			draw (renderer);
		}
	}

	void Menu::clear (SDL_Renderer* renderer)
	{
		SDL_RenderClear (renderer);
	}

	void Menu::update (SDL::Event& ev, SDL_Renderer* renderer)
	{
		if ( ev.poll () )
		{
			if ( ev.type () == SDL_KEYDOWN )
			{
				if ( !_onlyShow )
				{
					switch ( ev.key () )
					{
					case SDLK_RETURN:
						run (ev, renderer);
						break;
					case SDLK_UP:
					case SDLK_w:
						( *_selected )._Get ()->changeColor (SDL_Color { 0, 0, 0, 0 }, renderer);
						if ( _selected == _messages.begin () )
							_selected = _messages.end () - 1;
						else
							--_selected;
						( *_selected )._Get ()->changeColor (SDL_Color { 255, 255, 255, 0 }, renderer);
						break;
					case SDLK_DOWN:
					case SDLK_s:
						( *_selected )._Get ()->changeColor (SDL_Color { 0, 0, 0, 0 }, renderer);
						if ( _selected == _messages.end () - 1 )
							_selected = _messages.begin ();
						else
							++_selected;
						( *_selected )._Get ()->changeColor (SDL_Color { 255, 255, 255, 0 }, renderer);
						break;
					default:
						break;
					}
				}
				else
				{
					switch ( ev.key () )
					{
					case SDLK_ESCAPE:
						_quit = true;
						break;
					default:
						break;
					}
				}
			}
		}
	}

	void Menu::run (SDL::Event& ev, SDL_Renderer* renderer)
	{
		if ( _selected == _messages.begin () )
			gameplay (ev, renderer);
		if ( _selected == _messages.begin () + 1 )
			instruction (ev, renderer);
		if ( _selected == _messages.begin () + 2 )
			_quit = true;
	}

	void Menu::gameplay (SDL::Event& ev, SDL_Renderer* renderer)
	{
		Game::Gameplay gameplay (renderer, _manager);
		gameplay.loop (renderer, ev);
	}

	void Menu::instruction (SDL::Event& ev, SDL_Renderer* renderer)
	{
		std::vector<std::shared_ptr<SDL::Text>> textHelped;

		textHelped.push_back (std::make_shared<SDL::Text> ("PRZESUN W LEWO - STRZALKA W LEWO", "../images/text.ttf"));
		textHelped.push_back (std::make_shared<SDL::Text> ("PRZESUN W PRAWO - STRZALKA W PRAWO", "../images/text.ttf"));
		textHelped.push_back (std::make_shared<SDL::Text> ("WYJSCIE - ESCAPE", "../images/text.ttf"));

		for ( auto i : textHelped )
		{
			( *i ).surfaceFromTTF (SDL_Color { 255, 255, 255, 0 });
			( *i ).textureFromSurface (renderer);
		}

		textHelped [0].get ()->rectangle = { 800 / 2 - 250, 100, 500, 80 };
		textHelped [1].get ()->rectangle = { 800 / 2 - 250, 200, 500, 80 };
		textHelped [2].get ()->rectangle = { 800 / 2 - 200, 300, 400, 80 };

		std::vector<std::weak_ptr<SDL::Text>> weak;
		for ( auto i = textHelped.begin (); i != textHelped.end (); i++ )
			weak.push_back (( *i ));

		Menu menuInstruction (weak, _manager, renderer, true, 15);
		menuInstruction.loop (ev, renderer);
	}
}