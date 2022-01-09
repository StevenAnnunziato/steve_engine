#pragma once

#include <vector>
#include "Trackable.h"
#include <Timer.h>
#include "Sprite.h"

using namespace std;

class Animation :public Trackable
{
	public:
		Animation();
		Animation(vector<Sprite> frames, const bool& loop, const float& fps);
		~Animation();

		Sprite& getCurrentSprite();
		// advance animation
		void update();

		// accessors/mutators
		float getMSPerFrame()
		{
			return mMSPerFrame;
		}
		void setFPS(const float& fps)
		{
			mMSPerFrame = 1 / fps * 1000;
		}
		bool getPaused()
		{
			return mPaused;
		}
		void togglePaused()
		{
			mPaused = !mPaused;
		}
		void setPaused(const bool& paused)
		{
			mPaused = paused;
		}

	private:
		vector<Sprite> mFrames;
		bool mLooping;
		int mCurrentFrame;
		bool mPaused;

		// timing info
		Timer mTimer;
		double mTimeOnFrameStart;
		float mMSPerFrame;
};