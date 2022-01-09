#pragma once

#include <cassert>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <Trackable.h>

class Font : public Trackable
{

	friend class Display;

public:
	Font(const std::string& path, const std::string& filename, const int& size);
	~Font();

	int getSize()
	{
		return mSize;
	}

private:
	ALLEGRO_FONT* mpFont;
	int mSize;

};