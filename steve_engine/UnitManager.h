#pragma once

#include <vector>

#include "Trackable.h"
#include "Unit.h"

class GraphicsBufferManager;

class UnitManager :public Trackable
{
public:
	UnitManager();
	~UnitManager();

	void initUnitManager(const int& maxUnits, GraphicsBufferManager* pGBM);
	void cleanupUnitManager();

	void update(Display& display, float& deltaTime);
	void draw(Display& display);
	void addUnit(const Vector2D& loc);
	void removeUnit();
	void pauseAllAnimations(const bool& paused);
	void setLastAnimation();
	void removeAtPosition(const Vector2D& pos);

	// accessors
	vector<Unit*> getUnits()
	{
		return mUnits;
	}
	bool& getPaused()
	{
		return mUnitsPaused;
	}

private:
	Animation mAnimation;
	Animation mAltAnimation;

	vector<Unit*> mUnits;
	int mMaxUnits;
	bool mUnitsPaused;

	void removeAllUnits();

};