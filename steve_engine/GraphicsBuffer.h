#pragma once

#include <Trackable.h>
#include <allegro5/allegro.h>

class GraphicsBuffer :public Trackable
{

	friend class Display;

public:
	GraphicsBuffer(const std::string& path, const std::string& filename);
	GraphicsBuffer(int width, int height);
	~GraphicsBuffer();

	int getWidth()
	{
		return al_get_bitmap_width(mpBitmap);
	}
	int getHeight()
	{
		return al_get_bitmap_height(mpBitmap);
	}

private:
	ALLEGRO_BITMAP* mpBitmap;
	bool mOwnsBitmap;

	GraphicsBuffer(ALLEGRO_DISPLAY* pDisplay);
	GraphicsBuffer(GraphicsBuffer&) = delete;

};