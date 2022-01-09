#include "Sprite.h"

Sprite::Sprite(GraphicsBuffer* buffer, const Vector2D& sourceLoc, const int& width, const int& height)
{
	mpBuffer = buffer;
	mSourceLoc = sourceLoc;
	mWidth = width;
	mHeight = height;
}
Sprite::~Sprite()
{
	
}
