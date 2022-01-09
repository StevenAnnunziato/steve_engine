#pragma once

#include "Trackable.h"
#include "Vector2D.h"
#include "Animation.h"

class Display;

enum class Direction
{
	None,
	Left,
	Right,
	Up,
	Down
};

class Unit :public Trackable
{
public:
	// continues animation
	void update(Display& display, const float& deltaTime);
	// draws current sprite
	void draw(Display& display);

	// accessors
	Vector2D getLocation()
	{
		return mLocation;
	}
	Animation& getAnimation()
	{
		return mAnimation;
	}
	// mutators
	void setLocation(const Vector2D& loc)
	{
		mLocation = loc;
	}
	void setAnimation(const Animation& anim)
	{
		mAnimation = anim;
	}
	void SetDirection(Direction dir)
	{
		mDirection = dir;
	}

	friend class UnitManager;

private:
	Unit();
	Unit(const Vector2D& location, const Animation& animation);
	~Unit();

	Vector2D mLocation;
	Animation mAnimation;
	Direction mDirection;
	bool mUsingAltAnimation;
};