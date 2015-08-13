#include "BMP.h"

namespace SDL
{
	bool BMP::load (const std::string& path)
	{
		_texture = nullptr;

		_image = SDL_LoadBMP (path.c_str ());

		if ( _image == nullptr )
		{
			std::cout << "Error: " << SDL_GetError () << std::endl;
			return false;
		}
		else
		{
			std::cout << "OK"<<std::endl;
			colorKey ();
			return true;
		}
	}

	void BMP::destroy ()
	{
		SDL_FreeSurface (_image);
	}

	bool BMP::TextureFomBMP (SDL_Renderer* renderer)
	{
		_texture = SDL_CreateTextureFromSurface (renderer, _image);
		return ( _texture != nullptr ) ? true : false;
	}

	BMP::~BMP ()
	{
		if ( _image != nullptr )
			destroy ();
		if ( _texture != nullptr )
			SDL_DestroyTexture (_texture);
	}

	void BMP::colorKey ()
	{
		size_t key = SDL_MapRGB (_image->format, 255, 0, 255);

		SDL_SetColorKey (_image, true, key);
	}
}