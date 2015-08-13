#ifndef MANAGER_H
#define MANAGER_H
#include "BMP.h"
#include "Text.h"
#include <vector>
#include <memory>

namespace Game
{
	void drawAll (SDL_Renderer*);
	class Manager
	{
	public:
		Manager (SDL_Renderer* );

		std::shared_ptr<SDL::BMP> BMP (size_t)const;
	private:
		std::vector < std::shared_ptr<SDL::BMP>> _textures;
	};
}
#endif