#ifndef BMP_H
#define BMP_H
#include "Image.h"
#include "SDL_image.h"
#include <iostream>
namespace SDL
{
	class BMP:public Image<SDL_Surface>
	{
	public:
		BMP (const Image& image) = delete;
		BMP ()
		:Image(){}
		~BMP ();
	
		bool virtual load (const std::string&);
		void virtual destroy ();
		
		bool TextureFomBMP (SDL_Renderer*);

		SDL_Texture* texture ()const
		{return _texture;}

		SDL_Rect rectangle;
	private:
		void colorKey ();

		SDL_Texture* _texture;
	};
}
#endif