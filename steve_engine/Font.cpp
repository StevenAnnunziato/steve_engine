#include "Font.h"

Font::Font(const std::string& path, const std::string& filename, const int& size)
{
	mSize = size;

	mpFont = al_load_ttf_font((path + filename).c_str(), mSize, 0);
	assert(mpFont);
}
Font::~Font()
{
	al_destroy_font(mpFont);
}