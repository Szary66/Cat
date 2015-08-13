#include "Manager.h"


namespace Game
{

	Manager::Manager (SDL_Renderer* renderer)
	{
		for ( Uint32 i = 0; i < 16; i++ )
		{
			std::string path = "../images/images_";
			_textures.push_back (std::make_shared< SDL::BMP> ());
			path += std::to_string (i);
			path += ".bmp";
			_textures [i].get ()->load (path);
			_textures [i].get ()->TextureFomBMP (renderer);
		}
	}


	std::shared_ptr<SDL::BMP> Manager::BMP (size_t ID)const
	{
		return _textures [ID];
	}

	//Funtion for test, this fution it is not important to main game
	void drawAll (SDL_Renderer* renderer)
	{
		Manager m(renderer);
		for ( size_t i = 0; i < 16; i++ )
		{
			m.BMP (i).get ()->rectangle.x = 45 * i;
			m.BMP (i).get ()->rectangle.y = 50;
			m.BMP (i).get ()->rectangle.w = 40;
			m.BMP (i).get ()->rectangle.h = 50;
			SDL_RenderCopy (renderer, m.BMP (i).get ()->texture (), nullptr, &m.BMP (i)->rectangle);
		}

		SDL_RenderPresent (renderer);
	}
}