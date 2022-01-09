#pragma once

#include <Trackable.h>
#include <Vector2D.h>
#include "GraphicsBuffer.h"

class Sprite :public Trackable
{

	public:
		Sprite(GraphicsBuffer* buffer, const Vector2D& sourceLoc, const int& width, const int& height);
		~Sprite();

		// accessors
		GraphicsBuffer* getBuffer()
		{
			return mpBuffer;
		}
		Vector2D& getSourceLoc()
		{
			return mSourceLoc;
		}
		int& getWidth()
		{
			return mWidth;
		}
		int& getHeight()
		{
			return mHeight;
		}

	private:
		GraphicsBuffer* mpBuffer;
		Vector2D mSourceLoc; // top left corner of where the sprite begins
		int mWidth;
		int mHeight;

};