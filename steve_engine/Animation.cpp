#include "Animation.h"

Animation::Animation()
{
	mLooping = false;
	mPaused = false;
	mCurrentFrame = 0;
	mMSPerFrame = 0;
	mTimeOnFrameStart = 0;
	mTimer.start();
}
Animation::Animation(vector<Sprite> frames, const bool& loop, const float& fps)
{
	mFrames = frames;
	mLooping = loop;
	mTimeOnFrameStart = 0;
	mPaused = false;

	// convert frames per second to milliseconds per frame
	mMSPerFrame = 1 / fps * 1000;

	// start timer
	mTimer.start();
}
Animation::~Animation()
{
	// no dynamic allocations,
	// nothing to do here
}

Sprite& Animation::getCurrentSprite()
{
	return mFrames[mCurrentFrame];
}
// advance animation
void Animation::update()
{
	// if paused, do nothing
	if (mPaused)
		return;

	// find time elapsed since the animation frame started
	double elapsedTime = mTimer.getElapsedTime() - mTimeOnFrameStart;

	// if elapsed time is greater than ms per frame
	if (elapsedTime > mMSPerFrame)
	{
		// if you don't loop, sit on last frame
		if (!mLooping && mCurrentFrame == mFrames.size() - 1)
			return;

		// advance one frame
		mCurrentFrame = (mCurrentFrame + 1) % mFrames.size();

		// this frame starts now
		mTimeOnFrameStart = mTimer.getElapsedTime();
	}
}