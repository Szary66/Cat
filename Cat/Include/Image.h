#ifndef IMAGE_H
#define IMAGE_H
#include <string>
#include <cstdlib>
//#include <cinttypes>
namespace SDL
{
	template <typename T>
	class Image
	{
	public:
		Image (const Image&) = delete;
		Image ()
		{_image = nullptr;}

		bool virtual load (const std::string&) = 0;
		void virtual destroy () = 0;

		T* image ()const
		{return _image;}
				
	protected:
		T* _image;
	};
}
#endif