#ifndef TEXT_H
#define TEXT_H
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "Image.h"
#include "BMP.h"

namespace SDL
{
	bool initText ();

	class Text:public Image<SDL_Surface> 
	{
	public:
		Text (Text&) = delete;
		Text (const std::string&, const std::string& );
		~Text ();

		bool load (const std::string&);
		void virtual destroy ();

		void surfaceFromTTF (SDL_Color&);
		void textureFromSurface (SDL_Renderer*);
		void changeColor (SDL_Color&, SDL_Renderer*);
		void update (const std::string&, SDL_Color&, SDL_Renderer*);

		const TTF_Font* font ()const
		{return _font;}

		SDL_Texture* texture ()const
		{return _texture;}

		SDL_Rect rectangle;

		std::string text;
		
	private:
		TTF_Font* _font;
		SDL_Texture* _texture;
	};
}
#endif