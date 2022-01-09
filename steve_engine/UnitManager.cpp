#include <random>

#include "UnitManager.h"
#include "Display.h"
#include "GraphicsBufferManager.h"

UnitManager::UnitManager()
{
	mMaxUnits = 0;
	mUnitsPaused = false;
}
UnitManager::~UnitManager()
{
	cleanupUnitManager();
}

void UnitManager::initUnitManager(const int& maxUnits, GraphicsBufferManager* pGBM)
{
	mMaxUnits = maxUnits;

	// determine which graphics buffers to reference
	GraphicsBuffer* smurph = pGBM->getGraphicsBuffer("smurph");
	GraphicsBuffer* dean = pGBM->getGraphicsBuffer("dean_smurph");

	// unit animations
	Sprite f1(smurph, Vector2D(0, 0), 60, 60);
	Sprite f2(smurph, Vector2D(60, 0), 60, 60);
	Sprite f3(smurph, Vector2D(120, 0), 60, 60);
	Sprite f4(smurph, Vector2D(180, 0), 60, 60);
	Sprite f5(smurph, Vector2D(0, 60), 60, 60);
	Sprite f6(smurph, Vector2D(60, 60), 60, 60);
	Sprite f7(smurph, Vector2D(120, 60), 60, 60);
	Sprite f8(smurph, Vector2D(180, 60), 60, 60);
	Sprite f9(smurph, Vector2D(0, 120), 60, 60);
	Sprite f10(smurph, Vector2D(60, 120), 60, 60);
	Sprite f11(smurph, Vector2D(120, 120), 60, 60);
	Sprite f12(smurph, Vector2D(180, 120), 60, 60);
	Sprite f13(smurph, Vector2D(0, 180), 60, 60);
	Sprite f14(smurph, Vector2D(60, 180), 60, 60);
	Sprite f15(smurph, Vector2D(120, 180), 60, 60);
	Sprite f16(smurph, Vector2D(180, 180), 60, 60);
	vector<Sprite> frames1;
	frames1.push_back(f1);
	frames1.push_back(f2);
	frames1.push_back(f3);
	frames1.push_back(f4);
	frames1.push_back(f5);
	frames1.push_back(f6);
	frames1.push_back(f7);
	frames1.push_back(f8);
	frames1.push_back(f9);
	frames1.push_back(f10);
	frames1.push_back(f11);
	frames1.push_back(f12);
	frames1.push_back(f13);
	frames1.push_back(f14);
	frames1.push_back(f15);
	frames1.push_back(f16);
	Animation anim(frames1, true, 16);
	mAnimation = anim;
	// alternate
	Sprite a1(dean, Vector2D(0, 0), 60, 60);
	Sprite a2(dean, Vector2D(60, 0), 60, 60);
	Sprite a3(dean, Vector2D(120, 0), 60, 60);
	Sprite a4(dean, Vector2D(180, 0), 60, 60);
	Sprite a5(dean, Vector2D(0, 60), 60, 60);
	Sprite a6(dean, Vector2D(60, 60), 60, 60);
	Sprite a7(dean, Vector2D(120, 60), 60, 60);
	Sprite a8(dean, Vector2D(180, 60), 60, 60);
	Sprite a9(dean, Vector2D(0, 120), 60, 60);
	Sprite a10(dean, Vector2D(60, 120), 60, 60);
	Sprite a11(dean, Vector2D(120, 120), 60, 60);
	Sprite a12(dean, Vector2D(180, 120), 60, 60);
	Sprite a13(dean, Vector2D(0, 180), 60, 60);
	Sprite a14(dean, Vector2D(60, 180), 60, 60);
	Sprite a15(dean, Vector2D(120, 180), 60, 60);
	Sprite a16(dean, Vector2D(180, 180), 60, 60);
	vector<Sprite> frames2;
	frames2.push_back(a1);
	frames2.push_back(a2);
	frames2.push_back(a3);
	frames2.push_back(a4);
	frames2.push_back(a5);
	frames2.push_back(a6);
	frames2.push_back(a7);
	frames2.push_back(a8);
	frames2.push_back(a9);
	frames2.push_back(a10);
	frames2.push_back(a11);
	frames2.push_back(a12);
	frames2.push_back(a13);
	frames2.push_back(a14);
	frames2.push_back(a15);
	frames2.push_back(a16);
	Animation anim2(frames2, true, 16);
	mAltAnimation = anim2;

}
void UnitManager::cleanupUnitManager()
{
	removeAllUnits();
	mMaxUnits = 0;
}

void UnitManager::update(Display& display, float& deltaTime)
{
	// update all units in the vector
	for (vector<Unit*>::iterator it = mUnits.begin(); it != mUnits.end(); ++it)
	{
		(*it)->update(display, deltaTime);
	}

}
void UnitManager::draw(Display& display)
{
	// draw all units in the vector
	for (vector<Unit*>::iterator it = mUnits.begin(); it != mUnits.end(); ++it)
	{
		(*it)->draw(display);
	}
}
void UnitManager::addUnit(const Vector2D& loc)
{
	// don't add/create unit if we are already at the maximum
	if ((int)mUnits.size() >= mMaxUnits)
		return;

	// create unit
	mUnits.push_back(new Unit(loc, mAnimation));
}

// Note: used solution from Stack Overflow forum here:
// https://stackoverflow.com/questions/991335/how-to-erase-delete-pointers-to-objects-stored-in-a-vector
void UnitManager::removeUnit()
{
	// end here if there are no units to destroy
	if ((int)mUnits.size() == 0)
		return;

	// initialize randomizer
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, mUnits.size() - 1);
	
	// iterate through vector a random number of times
	vector<Unit*>::iterator it = mUnits.begin() + dist(rng);
	delete* it;
	it = mUnits.erase(it);
}

void UnitManager::removeAllUnits()
{
	// end here if there are no units to destroy
	if ((int)mUnits.size() == 0)
		return;

	// remove a random unit mUnits.size() times
	int length = mUnits.size();
	for (int i = 0; i < length; i++)
	{
		removeUnit();
	}
}

void UnitManager::pauseAllAnimations(const bool& paused)
{
	// determine if units should be paused or not
	mUnitsPaused = !mUnitsPaused;

	// pause each unit's animation
	for (vector<Unit*>::iterator it = mUnits.begin(); it != mUnits.end(); ++it)
	{
		(*it)->getAnimation().setPaused(mUnitsPaused);
	}
}

void UnitManager::setLastAnimation()
{
	if (mUnits.back()->mUsingAltAnimation)
	{
		mUnits.back()->setAnimation(mAnimation);
		mUnits.back()->mUsingAltAnimation = false;
	}
	else
	{
		mUnits.back()->setAnimation(mAltAnimation);
		mUnits.back()->mUsingAltAnimation = true;
	}
}

void UnitManager::removeAtPosition(const Vector2D& pos)
{
	// check if there are any units here
	for (vector<Unit*>::iterator it = mUnits.begin(); it != mUnits.end(); ++it)
	{
		const int UNIT_X = (*it)->getLocation().getX();
		const int UNIT_Y = (*it)->getLocation().getY();
		const int WIDTH = (*it)->getAnimation().getCurrentSprite().getWidth();
		const int HEIGHT = (*it)->getAnimation().getCurrentSprite().getHeight();
		// if this unit overlaps with the mouse
		if (pos.getX() < UNIT_X + WIDTH && pos.getX() > UNIT_X && pos.getY() < UNIT_Y + HEIGHT && pos.getY() > UNIT_Y)
		{
			// remove this unit
			delete (*it);
			mUnits.erase(it);
			return;
		}
		
	}
}