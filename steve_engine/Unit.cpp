#include "Unit.h"
#include "Display.h"
#include "Game.h"

Unit::Unit()
{
	mLocation = Vector2D(0, 0);
}
Unit::Unit(const Vector2D& location, const Animation& animation)
{
	mLocation = location;
	mAnimation = animation;
}
Unit::~Unit()
{
	// no dynamic allocations,
	// nothing needed here
}

// continues animation
void Unit::update(Display& display, const float& deltaTime)
{
	// update sprite
	mAnimation.update();
	
	// update position
	Vector2D offset;
	const float SPEED = 0.02f;
	if (mDirection == Direction::Left)
	{
		offset += Vector2D(-1, 0);
	}
	else if (mDirection == Direction::Right)
	{
		offset += Vector2D(1, 0);
	}
	else if (mDirection == Direction::Up)
	{
		offset += Vector2D(0, -1);
	}
	else if (mDirection == Direction::Down)
	{
		offset += Vector2D(0, 1);
	}
	//mLocation += offset * deltaTime * SPEED;

	// ensure unit is on the screen
	// width
	/*if (mLocation.getX() >= display.getWindowSize().getX())
		mLocation.setX(fmod(mLocation.getX(), display.getWindowSize().getX()));
	else if (mLocation.getX() < 0)
		mLocation.setX(float(display.getWindowSize().getX() + mLocation.getX() - 1));
	// height
	int y = (int)mLocation.getY();
	if (mLocation.getY() >= display.getWindowSize().getY())
		mLocation.setY(fmod(mLocation.getY(), display.getWindowSize().getY()));
	else if (mLocation.getY() < 0)
		mLocation.setY(float(display.getWindowSize().getY() + mLocation.getY() - 1));*/
}
// draws current sprite
void Unit::draw(Display& display)
{
	display.draw(mLocation, mAnimation.getCurrentSprite(), 1.0);
}