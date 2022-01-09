#pragma once

#include "Trackable.h"
#include "Display.h"
#include "UnitManager.h"
#include "InputSystem.h"
#include "Event.h"
#include "EventListener.h"
#include "GraphicsBufferManager.h"

class Vector2D;

class Game :public EventListener
{
public:
	Game();
	~Game();

	void initializeGame(const float& framesPerSecond, const Vector2D& size, const int& maxUnits);
	void cleanupGame();

	void doLoop();

	// instance management
	static Game* getInstance();
	static void initInstance();
	static void cleanupInstance();

	// events
	void handleEvent(const Event& theEvent);

	// accessors
	Display& getDisplay()
	{
		return mDisplay;
	}
	float getMSPerFrame()
	{
		return mMSPerFrame;
	}
	InputSystem& getInputSystem()
	{
		return mInputSystem;
	}
	UnitManager& getUnitManager()
	{
		return mUnitManager;
	}
	// mutators
	void setDisplay(const Display& display)
	{
		mDisplay = display;
	}

private:
	static Game* mpsTheGame;
	InputSystem mInputSystem;
	UnitManager mUnitManager;

	Display mDisplay;
	bool mGameLooping = true;

	// GraphicsBuffers
	GraphicsBufferManager mGraphicsBufferManager;

	// timing info
	Timer mTimer;
	float mMSPerFrame;

	// helper functions for game loop
	void processInput();
	void updateGameState();
	void render();
};