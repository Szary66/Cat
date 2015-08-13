#include "Text.h"

namespace SDL
{
	Text::Text (const std::string& text, const std::string& path)
		:text (text)
	{
		_font = nullptr;
		load (path);
	}

	Text::~Text ()
	{
		TTF_CloseFont (_font);
		SDL_DestroyTexture (_texture);
	}

	void Text::surfaceFromTTF (SDL_Color& color)
	{
		_image = TTF_RenderText_Blended (_font, text.c_str (), color);
	}

	void Text::textureFromSurface (SDL_Renderer* renderer)
	{
		_texture = SDL_CreateTextureFromSurface (renderer, _image);
	}

	void Text::destroy ()
	{
		SDL_FreeSurface (_image);
	}

	void Text::changeColor (SDL_Color& color, SDL_Renderer* renderer)
	{
		destroy ();
		surfaceFromTTF (color);

		SDL_DestroyTexture (_texture);
		textureFromSurface (renderer);
	}

	bool Text::load (const std::string& path)
	{
		if ( _font )
			TTF_CloseFont (_font);

		_font = TTF_OpenFont (path.c_str (), 20);

		return ( _font ) ? true : false;
	}

	void Text::update (const std::string& text, SDL_Color& color, SDL_Renderer* renderer)
	{
		this->text = text;
		SDL_FreeSurface (_image);
		surfaceFromTTF (color);

		SDL_DestroyTexture (_texture);
		textureFromSurface (renderer);
	}

	bool initText ()
	{
		return !TTF_Init ();
	}
}