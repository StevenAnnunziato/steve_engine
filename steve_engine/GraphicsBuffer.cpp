#include "GraphicsBuffer.h"

GraphicsBuffer::GraphicsBuffer(const std::string& path, const std::string& filename)
{
	mpBitmap = al_load_bitmap((path + filename).c_str());
	assert(mpBitmap);
	mOwnsBitmap = true;
}
GraphicsBuffer::GraphicsBuffer(int width, int height)
{
	mpBitmap = al_create_bitmap(width, height);
	assert(mpBitmap);
	mOwnsBitmap = true;
}
GraphicsBuffer::GraphicsBuffer(ALLEGRO_DISPLAY* pDisplay)
{
	mpBitmap = al_get_backbuffer(pDisplay);
	mOwnsBitmap = false;
}

GraphicsBuffer::GraphicsBuffer::~GraphicsBuffer()
{
	if (mOwnsBitmap)
		al_destroy_bitmap(mpBitmap);
}