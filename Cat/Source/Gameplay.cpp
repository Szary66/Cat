#include "Gameplay.h"

namespace Game
{
	Gameplay::Gameplay (SDL_Renderer* renderer, Game::Manager& manager)
		:_manager (manager), _score (0), _showedScore ("0", "../images/text.ttf"), _timedrop (0), _speedDrop (20)
	{
		_background [0] = _manager.BMP (13);
		_background [0]._Get ()->rectangle = { 0, 100, 800, 500 };

		_background [1] = _manager.BMP (12);
		_background [1]._Get ()->rectangle = { 0, 0, 800, 100 };

		_cat = _manager.BMP (11);
		_cat._Get ()->rectangle = { 375, 550, 50, 50 };

		_showedScore.surfaceFromTTF (SDL_Color { 255, 0, 0, 0 });
		_showedScore.textureFromSurface (renderer);
		_showedScore.rectangle = { 550, 70, 40, 20 };

		for ( size_t i = 0; i < 10; i++ )
			_dropeds.push_back (_manager.BMP (i));

		srand (time (nullptr));
	}



	void Gameplay::move ()
	{
		if ( _timedrop < SDL_GetTicks () )
		{
			for ( auto i : _dropeds )
				i._Get ()->rectangle.y += 1;

			_timedrop = SDL_GetTicks () + _speedDrop;
		}
	}

	void Gameplay::loop (SDL_Renderer* renderer, SDL::Event& event)
	{
		_quit = false;
		//first position dropeds
		size_t h = 0;
		for ( auto i : _dropeds )
		{
			i._Get ()->rectangle.x = rand () % 650;
			i._Get ()->rectangle.y = -600 + h*60;
			i._Get ()->rectangle.w = 50;
			i._Get ()->rectangle.h = 50;
			h++;
		}

		while ( !_quit && event.type () != SDL_QUIT )
		{
			clear (renderer);
			update (event, renderer);
			draw (renderer);
		}
	}

	void Gameplay::clear (SDL_Renderer* renderer)
	{
		SDL_RenderClear (renderer);
	}

	void Gameplay::update (SDL::Event& event, SDL_Renderer* renderer)
	{
		size_t k = 0, n = 0;

		move ();
		restartDroped (renderer);
		handingEvent (event);
	}

	void Gameplay::handingEvent (SDL::Event& event)
	{
		if ( event.poll () )
		{
			if ( event.type () == SDL_KEYDOWN )
			{
				switch ( event.key () )
				{
				case SDLK_a:
				case SDLK_LEFT:
					if ( _cat._Get ()->rectangle.x > 0 )
						_cat._Get ()->rectangle.x -= 5;
					break;
				case SDLK_d:
				case SDLK_RIGHT:
					if ( _cat._Get ()->rectangle.x < 800 - _cat._Get ()->rectangle.w )
						_cat._Get ()->rectangle.x += 10;
					break;
				case SDLK_ESCAPE:
					_quit = true;
					break;
				default:
					break;
				}
			}
		}
	}

	void Gameplay::draw (SDL_Renderer* renderer)
	{
		SDL_RenderCopy (renderer, _background [0]._Get ()->texture (), nullptr, &_background [0]._Get ()->rectangle);

		for ( auto i : _dropeds )
			SDL_RenderCopy (renderer, i._Get ()->texture (), nullptr, &i._Get ()->rectangle);

		SDL_RenderCopy (renderer, _cat._Get ()->texture (), nullptr, &_cat._Get ()->rectangle);

		SDL_RenderCopy (renderer, _background [1]._Get ()->texture (), nullptr, &_background [1]._Get ()->rectangle);

		SDL_RenderCopy (renderer, _showedScore.texture (), nullptr, &_showedScore.rectangle);


		SDL_RenderPresent (renderer);
	}

	void Gameplay::restartDroped (SDL_Renderer* renderer)
	{
		size_t image = 0;
		for ( auto i = _dropeds.begin (); i != _dropeds.end (); i++ )
		{
			if ( SDL_HasIntersection (&( *i )._Get ()->rectangle, &_cat._Get ()->rectangle) )// || 
			{
				if ( image < 5 )
					_quit = true;
				else
				{
					_score += 20;
					_showedScore.update (std::to_string (_score), SDL_Color { 255, 0, 0, 0 }, renderer);
				}

				
				( *i )._Get ()->rectangle.y = 0;
				( *i )._Get ()->rectangle.x = rand () % 750;


				break;
			}
			else if ( ( *i )._Get ()->rectangle.y > 600 )
			{
				( *i )._Get ()->rectangle.y = 0;
				( *i )._Get ()->rectangle.x = rand () % 750;
			}
			image++ ;
		}
	}
}